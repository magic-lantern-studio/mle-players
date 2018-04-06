/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file main.cxx
 * @ingroup MlePlayer
 *
 * This file implements the program entry points for a standalone player.
 *
 * @author Mark S. Millard
 * @date May 5, 2003
 */

// COPYRIGHT_BEGIN
//
//  Copyright (C) 2000-2018  Wizzer Works
//
//  Wizzer Works makes available all content in this file ("Content").
//  Unless otherwise indicated below, the Content is provided to you
//  under the terms and conditions of the Common Public License Version 1.0
//  ("CPL"). A copy of the CPL is available at
//
//      http://opensource.org/licenses/cpl1.0.php
//
//  For purposes of the CPL, "Program" will mean the Content.
//
//  For information concerning this Makefile, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END


// Include Magic Lantern header files.
// #include "mle/mlTypes.h"
#include "mle/mlMalloc.h"
#include "mle/mlAssert.h"
#include "mle/mlDebug.h"
#include "mle/MleDirector.h"


// Declare external references.
extern MlBoolean InitEnv(int, char **);
extern int MainLoop(void);
extern MlBoolean CleanupEnv(void);

// Global reference to Magic Lantern Debug Manager
MleDebugMgrP *g_mlDebugMgr;


// Inventor Workprint Player.

int
main(int argc, char *argv[])
{
    // Parse arguments.
    if ( argc < 2 )
    {
        fprintf(stderr, "Usage: %s workprint\n", argv[0]);
        exit(1);
    }

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

    return(0);
}
