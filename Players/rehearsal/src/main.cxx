/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file main.cxx
 * @ingroup MlePlayer
 *
 * This file implements the program entry points for a standalone player.
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2003-2025 Wizzer Works
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
#ifdef _WINDOWS
#include <windows.h>
#endif
#include <stdio.h>
#include <string.h>

#ifdef MLE_SOQT
#include <QApplication>
#endif /* MLE_SOQT */

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"
#include "mle/mlAssert.h"
#include "mle/mlDebug.h"
#include "mle/mlTrace.h"
#include "mle/mlFileio.h"
#include <mle/MlePath.h>
#include "mle/MleDirector.h"
#ifdef _WINDOWS
#include "mle/mlGetOpt.h"
#include <mle/MleWin32Path.h>
#else
#include <unistd.h>
#include <mle/MleLinuxPath.h>
#endif /* _WINDOWS */


// Declare external references.
extern MlBoolean InitEnv(int, char **);
extern int MainLoop(void);
extern MlBoolean CleanupEnv(void);

// Global reference to Magic Lantern Debug Manager
MLE_UTIL_API MleDebugMgrP *g_mlDebugMgr;

#ifdef MLE_SOQT
QApplication *g_mlQApp;
#endif /* MLE_SOQT */


// Argument structures for parser.
typedef struct _pattern
{
	char            *str;
	struct _pattern *next;
} Pattern;

typedef struct _ArgStruct
{
	char       *commandName;  /* Name of command. */
	char       *workprint;    /* Name of workprint file to execute. */
	int        verbose;       /* Be verbose. */
} ArgStruct;

const char *usage_str = "\
Syntax:   player [-v] <workprint>\n\
\n\
          -v                   Be verbose\n\
          <workprint>          Digital Workprint\n\
\n\
Function: Play a Magic Lantern Digital Workprint.\n\
\n\
This application plays a Digital Workprint as defined by the specified workprint file.\n";

// File descriptor for trace macros.
FILE *g_traceFd;


#ifdef _WINDOWS
static char *getCanonicalPath(char *path)
{
	char *cpath = NULL;
	MleWin32Path *wpath = new MleWin32Path((MlChar *)path, true);
	//cpath = strdup((char *)wpath->getPath());
	cpath = _strdup((char *)wpath->getPath());
	delete wpath;
	return cpath;
}
#else
static char *getCanonicalPath(char *path)
{
	return strdup(path);
}
#endif /* _WINDOWS */

// Parse the input arguments
int parseArgs(int argc, char *argv[], ArgStruct *args)
{
	/* declare local variables */
	int c;
	int errflg;
	extern char *optarg;
	extern int optind;

	errflg = 0;
	while ((c = getopt(argc, argv, "v?")) != -1)
	{
		switch (c)
		{
		case 'v':
			args->verbose = TRUE;
			break;
		case '?':
			errflg++;
		}
	}

	if (errflg)
	{
		(void)fprintf(stderr, "%s\n", usage_str);
		return FALSE;
	}

	for (; optind < argc; optind++)
	{
		if (!args->workprint) {
			args->workprint = getCanonicalPath(argv[optind]);
		}
		else {
			fprintf(stderr, "%s\n", usage_str);
			return FALSE;
		}
	}

	/* If there is no specified workprint, complain. */
	if (args->workprint == NULL)
	{
		fprintf(stderr, "%s\n", usage_str);
		return FALSE;
	}

	/* Having made it to here implies that we have good arguments. */

	return TRUE;
}


// Main entry point for Magic Lantern player.
int
main(int argc, char *argv[])
{
	// Declare local variables.
	ArgStruct args;

	g_traceFd = mlFOpen("playerTrace.log", "a+");
	MLE_TRACE_INFO(g_traceFd, Before arg parsing);

	// Parse arguments.
	args.commandName = argv[0];
	args.workprint = NULL;
	args.verbose = FALSE;
	if (!parseArgs(argc, argv, &args))
	{
		MLE_TRACE_ERROR(g_traceFd, argument parsing error);
		exit(1);
	}
	MLE_TRACE_INFO(g_traceFd, Successful arg parsing);

	// TODO: Set verbosity levels.

#ifdef MLE_SOQT
    // Create an Qt application framework for player.
    g_mlQApp = new QApplication(argc, argv);
#endif /* MLE_SOQT */

    // Create a new title environment.
    g_theTitle = (MleDirector*)mlMalloc(sizeof(MleDirector));
    MLE_ASSERT(g_theTitle);

    // Initialize title environment.
	g_theTitle->m_platformData = NULL;
    InitEnv(argc,argv);

    // Main execution loop.
    MainLoop();

    // Clean up title environment.
    CleanupEnv();

#ifdef MLE_SOQT
    // Clean up Qt application framework.
    delete g_mlQApp;
#endif /* MLE_SOQT */

    return(0);
}
