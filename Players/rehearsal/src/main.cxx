/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file main.cxx
 * @ingroup MlePlayer
 *
 * This file implements the program entry points for a standalone player.
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
