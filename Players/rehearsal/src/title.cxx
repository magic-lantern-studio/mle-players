/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file title.cxx
 * @ingroup MlePlayer
 *
 * This file implements functionality for reading a Digital Workprint
 * and playing it in a standalone player.
 *
 * @author Mark S. Millard
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2003-2020 Wizzer Works
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  For information concerning this header file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

// Include system header files.
#include <stdio.h>
#if defined(__linux__)
#include <unistd.h>
//#include <bstring.h>
#include <sys/time.h>
#include <time.h>
#ifdef MLE_SOQT
#include <QtGlobal>
#include <QWidget>
#endif
#endif /* __linux__ */
#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <process.h>

#include <Inventor/Win/SoWin.h>
#endif /** WIN32 */

// Include Magic Lantern Runtime Engine header files.
#include <mle/mlTypes.h>
#include <mle/mlErrno.h>
#include <mle/MleDirector.h>
#include <mle/MleLoad.h>
#include <mle/MleScheduler.h>
#include <mle/MleStage.h>
#include <mle/MleStageClass.h>
#include <mle/MleEventDispatcher.h>
#include <mle/MleScene.h>
#include <mle/MleGroup.h>

// Inlucde Digital Workprint header files.
#include <mle/Dwp.h>
#include <mle/DwpItem.h>
#include <mle/DwpGroup.h>
#include <mle/DwpFinder.h>
#include <mle/DwpBoot.h>
#include <mle/DwpTagDiscriminator.h>
#include <mle/DwpTagAllDiscriminator.h>
#include <mle/DwpStage.h>
#include <mle/DwpLoad.h>

// Include Magic Lantern Player header files.
#include <mle/MlePlayer.h>
#include <mle/MleIvStage.h>


// Environment variable used for parent app telling us how to run.
#define MLEPLAY_EXEC_MODE    "__MLE_PLAY_MODE__"

// Define globals.
//   This player may be used either standalone or from the tools.  If
//   standalone, there is a local workprint that is referred to from
//   the global _mlWorkprint.  If the tools are active, workprint information
//   (and other interaction) is accessed through a communications object
//   referenced by the global _mlPlayer.
extern MLE_RUNTIME_API MlePlayer *_mlPlayer;
//extern MLE_DWP_API MleDwpItem *_mlWorkprint;
MleDwpItem *_mlWorkprint;

// XXX this is somewhat of a hack.  Basically, this flag determines when
// it is safe to go into stage edit mode if you are using a player.  Another
// way to do this is to have the player send a message when it is finished
// sending over group info.
static int g_fToolsInitFinished = 0;

// Declare forward references.
static void
selectStage(MleDwpItem *top, char **callerStageName, char **callerStageClass);
static void frameAdvance(void *);
static void toolsInitFinished(void *);


#if defined(WIN32)
// Todo: determine if tz parameter can be struct timezone * to match linux.
// Timezone is not used, so it is not important that it matches for Windows
// platform.
int gettimeofday (struct timeval *tv, void *tz)
{
	union { 
		LONGLONG ns100; /* Time since 1 Jan 1601 in 100ns units. */ 
		FILETIME ft; 
	} now; 

	GetSystemTimeAsFileTime (&now.ft);
	tv->tv_usec = (long) ((now.ns100 / 10L) % 1000000L);
	tv->tv_sec = (long) ((now.ns100 - 116444736000000000L) / 10000000L);

	return(0);
}
#endif /* WIN32 */

MlBoolean 
InitEnv(int argc,char **argv)
{
	// Start a debugger.
#if defined(__linux__)
	char *dbxenv = getenv("MLE_DBX");
	if ( dbxenv && strstr(dbxenv,argv[0]) )
	{
		char cmd[128];
        // Todo: Find a replacement for winterm and dbx.
		sprintf(cmd,"winterm -c dbx -p %d",getpid());
		system(cmd);
		sleep(20);
	}
#endif /* __linux__ */

#if defined(MLE_DEBUG)
	// The following interrupt is very useful for debugging the player.
	// Don't remove, just comment out when not debugging.

#if defined(WIN32)
	//__asm int 3h; Note that this is not compliant with x64 architecture.
	__debugbreak();
#endif /* WIN32 */
#endif /* MLE_DEBUG */

	// Workprint initialization.
	mleDwpInit();
	MleScene::initClass();
	MleGroup::initClass();

	// Note that scheduler and stage are created before we attach
	//   to the tools.  This is because the tools may immediately
	//   request a group load.

	// Scheduler initialization.
	g_theTitle->m_theScheduler = new MleScheduler;

	// Now set it up to know the standard 4 Magic Lanter phases for
	// actors, roles, sets, and stages.  The user
	// can override this by inserting and deleting phases
	// at will.
	g_theTitle->m_theScheduler->init();

#if defined(WIN32)
	g_theTitle->m_theEventMgr = new MleEventDispatcher();
#endif /* WIN32 */

	_mlPlayer = NULL;

	// Decide on the mode we're being run in, by checking an
	// obscure env var set only by mlplay and Magic Lantern before
	// starting or restarting mlplay. The modes are:
	//	- standalone reh. player
	//	- standalone reh. player, restarted (after envvar setting)
	//	- from Magic Lantern (authoring tools)
	char *mlPlayMode = getenv(MLEPLAY_EXEC_MODE);
	if (!mlPlayMode)
	{
	    // Being run as standalone player, since our obscure envvar
	    // isn't set --- we decide on the stage,
	    // add our stage to the path, and restart ourselves, so that
	    // we have the stage's DLL dir included in our library path.
	    // Too bad this env var isn't interpreted dynamically...
	    // Note: we have to exec to get LD_LIBRARY_PATH interpreted, 
	    // can't fork.
	    
	    // Load a local workprint.
	    _mlWorkprint = mlLoadWorkprint(argv[1]);

	    if ( _mlWorkprint == NULL )
	    {
			printf("%s: ERROR: %s is not a valid workprint file.\n",
				argv[0], argv[1]);
			exit(-1);
	    }

	    // Select a rehearsal stage.
	    char *stageName, *stageClass;
	    selectStage(_mlWorkprint, &stageName, &stageClass);

#if defined(__linux__)
	    // Stage name is used to set LD_LIBRARY_PATH for 
	    // mlplay processes, so they select correct roles, 
	    // property roles, sets, etc.
        // Todo: use rld root or ld lib path?
	    char *currPath = getenv("LD_LIBRARY_PATH");
	    if (!currPath)
			currPath = (char *)"";
	    char addPath[100];
	    sprintf(addPath, "/usr/local/lib");
        // Todo: need a better policy for finding the rehearsal player components.
	    // It use to be
	    //   sprintf(addPath, "/usr/mle/%s/rehearsal", stageName);
	    // But we should use a linux standard, like
	    //   sprintf(addPath, "/usr/local/mle/%s/rehearsal", stageName);
	
	    // Append addition to existing library path.
        // Todo: maybe should prepend ours
	    char *newPath = new char[strlen(currPath)+strlen(addPath) + 50];
	    sprintf(newPath, "LD_LIBRARY_PATH=%s;%s", currPath, addPath);
	    putenv(newPath);
#endif /* __linux__ */
#if defined(WIN32)
		char *currPath = getenv("PATH");
	    if (! currPath)
			currPath = "";
		char addPath[256];
		char *mleHomePath = getenv("MLE_HOME");
		if (! mleHomePath)
        {
			sprintf(addPath, "C:\\Program Files\\WizzerWorks\\MagicLantern\\bin\\rehearsal", stageName);
		} else
		{
#if _WIN64
			sprintf(addPath, "%s\\bin64\\rehearsal", mleHomePath);
#else
			sprintf(addPath, "%s\\bin\\rehearsal", mleHomePath);
#endif /* _WIN64 */
		}

		char *newPath = new char[strlen(currPath)+strlen(addPath) + 50];
	    sprintf(newPath, "PATH=%s;%s", currPath, addPath);
		//fprintf (stdout, "%s\n", newPath);
	    putenv(newPath);
#endif /* WIN32 */
	    // Now we re-exec ourselves, so that the
	    // augmented LD_LIBRARY_PATH gets used...
	    // Set env var telling ourselves how to run on next exec
	    char s[200];
	    sprintf(s, "%s=mlplay", MLEPLAY_EXEC_MODE);
	    putenv(s);

#if defined(__linux__)
	    execvp(argv[0], argv);
#endif /* __linux__ */
#if defined(WIN32)
		_execvp(argv[0], argv);
#endif /* WIN32 */
	    
	    // If we reach here, the exec failed.
	    printf("ERROR mlplay: failed to re-exec\n");
	    exit(-1);
	}
	else if (strcmp(mlPlayMode, "mlplay") == 0)
	{
	    // Restarted mlplay standalone with augmented ld lib path.

	    // mvo 3/25/96: load dwp before creating stage and
	    // load a local workprint.
	    _mlWorkprint = mlLoadWorkprint(argv[1]);

	    if ( _mlWorkprint == NULL )
	    {
		    printf("ERROR: %s is not a valid workprint "
			   "file (on restart).\n", argv[1]);
		    exit(-1);
	    }

	    char *stageName, *stageClass;
	    selectStage(_mlWorkprint, &stageName, &stageClass);

	    // Look up the stage class.
	    const MleStageClass *sc = MleStageClass::find(stageClass);
	    if(! sc)
		{
			printf("ERROR mlplay: failed to load stage '%s'\n",
				   stageClass);
			exit(-1);
	    }

	    // Create the stage.
	    sc->createInstance();
	    if (!MleStage::g_theStage)
	    {
			printf("ERROR mlplay: failed to create stage '%s'\n",
				   stageClass);
			exit(-1);
	    }
	    
	    // Set a discriminator for entire session, 
	    // so we only deal with items
	    // from this class of stage (e.g., "brender")
	    MleDwpTagAllDiscriminator *allDiscrim = 
			    new MleDwpTagAllDiscriminator;
	    allDiscrim->addTag("rehearsal");
	    allDiscrim->addTag(stageName);
	    _mlWorkprint->setDiscriminator(allDiscrim);

	    free(stageName);
	    free(stageClass);

	    // Finish initializing the stage.
	    MleStage::g_theStage->init();
	}
	else if (strcmp(mlPlayMode, "magiclantern") == 0)
	{
	    // Being run as secondary process from authoring tools
	    // (scene ed, etc)

	    // create the player.
	    _mlPlayer = MlePlayer::create(argc,argv);
	    if ( !_mlPlayer )
	    {
			printf("ERROR mlplay: can't create MlePlayer\n");
			exit(-1);
	    }

        // Todo: We probably really want to take this out of here.
	    // Stage initialization
	    char stageClass[100];
	    strcpy(stageClass, 
			getenv("MLESTAGE") ? getenv("MLE_STAGE") : "MleIvStage");

	    // Look up the stage class.
	    const MleStageClass *sc = MleStageClass::find(stageClass);
	    if (! sc)
		{
			printf("ERROR mlplay: failed to load stage '%s'\n",
				   stageClass);
			exit(-1);
	    }

	    // Create the stage.
	    sc->createInstance();
	    if (!MleStage::g_theStage)
	    {
			printf("ERROR mlplay: failed to create stage '%s'\n",
				   stageClass);
			exit(-1);
	    }

	    // Put the stage offscreen.
	    MleStage::g_theStage->setOffscreen(TRUE);
	    MleStage::g_theStage->init();
	    MleStage::g_theStage->setEditing(0);

#if defined(__linux__)
#ifdef Q_OS_UNIX
        QWidget *window = MleStage::g_theStage->getWindow();
        if ( window )
            _mlPlayer->sendWindow(window->winId());
#else
	    Window window = MleStage::g_theStage->getWindow();
        if ( window )
            _mlPlayer->sendWindow(window);
#endif
#endif /* __linux__ */
#if defined(WIN32)
		HWND window = MleStage::g_theStage->getWindow();
	    if ( window )
            _mlPlayer->sendWindow(window->winId());
#endif /* WIN32 */

	    // Register player with stage.
	    _mlPlayer->registerWithStage();

	    // Configure player object with callbacks.
	    void frameAdvance(void *);
	    _mlPlayer->setFrameAdvanceCB(frameAdvance);
	    void toolsInitFinished(void *);
	    _mlPlayer->setToolsInitFinishedCB(toolsInitFinished);
	}

#if defined(__linux__)
#ifdef Q_OS_UNIX
    // Qt on Linux platform.
    // Todo: manage close button event here.
#else
	Display* display = MleStage::g_theStage->getDisplay();

	// Initialize event message for window close button 'x'.
	Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(display, MleStage::g_theStage->getWindow(), &wmDeleteMessage, 1);
#endif /* Q_OS_UNIX */
#endif /* __linux__ */

	if ( _mlPlayer == NULL )
	{
		// Load only the boot scene for stand alone rehearsal
		// player.
		(void) mlLoadBootScene( _mlWorkprint );
	}

	// Initialize quit flag.
	g_theTitle->m_quit = FALSE;

	return TRUE;
}

// Assumes no discriminator is currently set.

static void
selectStage(MleDwpItem *top, 
	    char **callerStageName, 
	    char **callerStageClass)
{
    // Create stage based on wp's first rehearsal stage.
    MleDwpTagDiscriminator *discrim = 
		new MleDwpTagDiscriminator;
    discrim->addTag("rehearsal");	// XXX - should become a constant.
    top->setDiscriminator(discrim);
    MleDwpFinder stageFinder(MleDwpStage::typeId);
    MleDwpStage *stage = 
		(MleDwpStage*) stageFinder.find(top);
    top->setDiscriminator(NULL);
    delete discrim;

    if (stage == NULL)
    {
		printf("WARN: no stage in this wp; during grace period, assuming "
			"an Inventor rehearsal stage.\n");
		*callerStageName = strdup("inventor");
		*callerStageClass = strdup("MleIvStage");
    }
    else
    {
		*callerStageName = strdup(stage->getName());
		*callerStageClass = strdup(stage->getStageClass());
    }
}

static int cycleTime = 0;

void 
Cycle(void)
{
	struct timeval startFrameTime, endFrameTime;
	if (_mlPlayer && _mlPlayer->getSendStats())
	{
	    gettimeofday(&startFrameTime, NULL);
	}

	// Run all the scheduled phases.  This will even work if
	// the title author has inserted his own phases.
	g_theTitle->m_theScheduler->goAll();

	if (_mlPlayer && _mlPlayer->getSendStats())
	{

	    // Find out time for frame.
	    gettimeofday(&endFrameTime, NULL);
	    long totalTime = ((endFrameTime.tv_sec-startFrameTime.tv_sec)*1000)+
			 ((endFrameTime.tv_usec - startFrameTime.tv_usec)/1000);

	    // Send off stat.
	    _mlPlayer->sendStats(totalTime);
	}

	if (cycleTime++ == 10)
	{
	    if (_mlPlayer)
			_mlPlayer->notifyPropChanged();
	    cycleTime = 0;
	}
}

int 
MainLoop(void)
{
#if defined(__linux__)
    // Loop forever.
    for(;;)
	{
		// Set up select.
		fd_set fdset;
		FD_ZERO(&fdset);

		// First listen for messages from the Player.
		if ( _mlPlayer )
		{
			// Create the select arguments.
			FD_SET(_mlPlayer->getFD(),&fdset);
		}

		// Next listen for Stage events.
		FD_SET(MleStage::g_theStage->getFD(), &fdset);
		static timeval timeout = { 0, 0 };

		// If the player has pending messages or we are cycling through
		// the title, set the timeout to infinite
		// otherwise set it to 0 seconds
		timeval *tt = NULL;
		if ((_mlPlayer && _mlPlayer->pendingMsgs()) || 
			 !MleStage::g_theStage->getEditing())
		{
			tt = &timeout;
		}

		// Test select.
		while ((_mlPlayer && _mlPlayer->pendingMsgs()) ||
			MleStage::g_theStage->doSelect(FD_SETSIZE, &fdset,NULL,NULL,tt) > 0 ) 
		{
			// First check to see if a player communication ready.
			if (_mlPlayer && (_mlPlayer->pendingMsgs() 
			    || FD_ISSET(_mlPlayer->getFD(), &fdset)))
			{
				// Make sure no errors occured on read.
				if (!(_mlPlayer->recvAndDeliverMsg()))
				{
					// Check to see if we have lost connection.
					if (mlGetErrno() == MLE_E_ATKLIB_CONNECTION_LOST)
					{
						// We have lost connection - for right
						// now, quit out of the main loop.
						return(-1);
					}

				}

				// Check for quit.
				if (_mlPlayer->hasQuit()) break;
			}

			// mvo 1/28/96: subverts crash where you hit play/pause
			// back and forth a lot. For some reason this causes
			// edit mode to go on...
			// stage asserts due to calling edit() when not
			// in edit mode -- added this 'if' clause
			// JR 1/29/96:  will not go into stage edit mode until
			// player is finished sending groups.
			if (MleStage::g_theStage->getEditing() &&
				(_mlPlayer == 0 || g_fToolsInitFinished))
			{
				// Next, check stage events and
				// switch on editing mode.
				if (FD_ISSET(MleStage::g_theStage->getFD(), &fdset))
				{
					MleStage::g_theStage->edit();
				}
			}
			
			// Reset the timeout and FDs to zero for next time through loop.
			tt = &timeout;
			FD_ZERO(&fdset);
			if (MleStage::g_theStage->getEditing())
			{
			    FD_SET(MleStage::g_theStage->getFD(), &fdset);
			}
			if (_mlPlayer) FD_SET(_mlPlayer->getFD(), &fdset);
		}

		// Cycle if stage is not in edit mode.
		if (!MleStage::g_theStage->getEditing())
		{

		    Cycle();
		  
		    // Quit on title request.
		    if (g_theTitle->m_quit)
			    break;
		}
    }
#endif /* __linux__ */
#if defined(WIN32)
	// Loop forever.
    for(;;)
	{
		// Set up select.
		fd_set fdset;
		FD_ZERO(&fdset);

		// First listen for messages from the Player.
		if ( _mlPlayer )
		{
			// Create the select arguments.
			FD_SET(_mlPlayer->getFD(),&fdset);
		}

		static timeval timeout = { 0, 0 };

		// If the player has pending messages or we are cycling through
		// the title, set the timeout to infinite;
		// otherwise, set it to 0 seconds
		timeval *tt = NULL;
		if ((_mlPlayer && _mlPlayer->pendingMsgs()) || 
			 !MleStage::g_theStage->getEditing())
		{
			tt = &timeout;
		}

		// Process messages on the wire.
		while ((_mlPlayer && _mlPlayer->pendingMsgs()) ||
			select(FD_SETSIZE, &fdset,NULL,NULL,tt) > 0 ) 
		{
			// First check to see if a player communication ready.
			if (_mlPlayer && (_mlPlayer->pendingMsgs() 
			    || FD_ISSET(_mlPlayer->getFD(), &fdset)))
			{
				// Make sure no errors occured on read.
				if (!(_mlPlayer->recvAndDeliverMsg()))
				{
					// Check to see if we have lost connection.
					if (mlGetErrno() == MLE_E_ATKLIB_CONNECTION_LOST)
					{
						// We have lost connection - for right
						// now, quit out of the main loop.
						return(-1);
					}

				}

				// Check for quit.
				if (_mlPlayer->hasQuit()) goto quit;
			}

			// mvo 1/28/96: subverts crash where you hit play/pause
			// back and forth a lot. For some reason this causes
			// edit mode to go on...
			// stage asserts due to calling edit() when not
			// in edit mode -- added this 'if' clause
			// JR 1/29/96:  will not go into stage edit mode until
			// player is finished sending groups.
			if (MleStage::g_theStage->getEditing() &&
				(_mlPlayer == 0 || g_fToolsInitFinished))
			{
				// Next, check stage events and
				// switch on editing mode.
				if (FD_ISSET(MleStage::g_theStage->getFD(), &fdset))
				{
					MleStage::g_theStage->edit();
				}
			}
			
			// Reset the timeout and FDs to zero for next time through loop.
			tt = &timeout;
			FD_ZERO(&fdset);
			if (_mlPlayer) FD_SET(_mlPlayer->getFD(), &fdset);
		}

		// Process messages on the Stage.
		MSG msg;
		while ((PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) != 0))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{ // if msg != WM_QUIT
				TranslateMessage(& msg);
				DispatchMessage(& msg);
			}
			else goto quit; // msg == WM_QUIT
		}

		// Process idle tasks that have been queued.
		if (SoWin::haveIdleTasks())
			SoWin::doIdleTasks();

		// Cycle if stage is not in edit mode.
		if (!MleStage::g_theStage->getEditing())
		{

		    Cycle();
		  
		    // Quit on title request.
		    if (g_theTitle->m_quit)
			    goto quit;
		}
	}

quit:

    SoWin::done();
#endif /* WIN32 */
    return 0;
}

MlBoolean CleanupEnv(void)
{
	return TRUE;
}

static void frameAdvance(void *)
{
	int mode = MleStage::g_theStage->getEditing();

	MleStage::g_theStage->setEditing(FALSE);

	g_theTitle->m_theScheduler->goAll();

	MleStage::g_theStage->setEditing(mode ? mode : 1);

	cycleTime = 0;

	//fprintf(stderr, "this is a test\n");
}

static void toolsInitFinished(void *)
{
	// Player finished sending groups.
	g_fToolsInitFinished = 1;
	//fprintf(stdout, "Another test\n");
	//fprintf(stderr, "Another test2\n");

	// Kluge so that it reloads camera data in stage.
	MleStage::g_theStage->setEditing(0);
	MleStage::g_theStage->setEditing(1);

	// Flush an initialization error messages out to status window.
	fflush(stdout);
}

#if defined(__linux__)
extern "C" {
// The following Iris gl stub functions are needed because
// we are using IL version 2.x which is based on the Iris gl library.
// This will prevent IL activate the Iris gl and keep our current
// executable based on OpenGL.  I put the stub function here because
// this is always loaded in before any dsos.

void
foreground(void)
{
}


long
gversion(char[12])
{
    return 0;
}
} /* extern "C" */
#endif /* __linux__ */
