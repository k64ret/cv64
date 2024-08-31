/**
 * @file title_demo.c
 *
 * This file contains the code that handles the demo gameplay seen after
 * waiting long enough in the title screen.
 *
 * More specifically, this code sets up the demo and plays back pre-recorded
 * controller inputs to make the character move. Everything else runs using the objects
 * and functions used for the gameplay state.
 */

#include <ultra64.h>
#include "cv64.h"
#include "objects/engine/title_demo.h"
#include "objects/engine/DMAMgr.h"
#include "gamestate.h"
#include "random.h"
#include "sound.h"
#include "system_work.h"

titleDemo_controller controller_data_REINHARDT[] = {
    {62, 0, -1, 0, 0},
    {0, 0, -2, 0, 0},
    {0, -1, -3, 0, 0},
    {0, -1, -5, 0, 0},
    {0, -1, -9, 0, 0},
    {0, -3, -12, 0, 0},
    {0, -8, -16, 0, 0},
    {0, -13, -22, 0, 0},
    {0, -17, -28, 0, 0},
    {0, -20, -34, 0, 0},
    {0, -22, -38, 0, 0},
    {7, -23, -39, 0, 0},
    {0, -25, -39, 0, 0},
    {0, -26, -39, 0, 0},
    {1, -28, -39, 0, 0},
    {0, -29, -39, 0, 0},
    {0, -33, -39, 0, 0},
    {0, -37, -37, 0, 0},
    {0, -37, -34, 0, 0},
    {0, -38, -34, 0, 0},
    {0, -41, -32, 0, 0},
    {0, -47, -27, 0, 0},
    {0, -51, -22, 0, 0},
    {0, -58, -18, 0, 0},
    {0, -68, -13, 0, 0},
    {0, -81, -8, 0, 0},
    {0, -82, -6, 0, 0},
    {0, -82, -5, 0, 0},
    {0, -82, -4, 0, 0},
    {0, -81, -3, 0, 0},
    {0, -81, 0, 0, 0},
    {0, -80, 5, 0, 0},
    {0, -79, 10, 0, 0},
    {0, -78, 16, 0, 0},
    {0, -76, 23, 0, 0},
    {0, -73, 35, 0, 0},
    {0, -68, 54, 0, 0},
    {0, -64, 70, 0, 0},
    {0, -61, 69, 0, 0},
    {1, -59, 69, 0, 0},
    {0, -56, 69, 0, 0},
    {0, -51, 69, 0, 0},
    {9, -51, 70, 0, 0},
    {0, -49, 70, 0, 0},
    {0, -45, 71, 0, 0},
    {0, -36, 73, 0, 0},
    {0, -23, 76, 0, 0},
    {5, -11, 78, 0, 0},
    {0, -12, 79, 0, 0},
    {1, -13, 79, 0, 0},
    {0, -12, 79, 0, 0},
    {1, -13, 79, 0, 0},
    {0, -16, 79, 0, 0},
    {0, -20, 79, 0, 0},
    {0, -24, 79, 0, 0},
    {11, -25, 79, 0, 0},
    {1, -26, 79, 0, 0},
    {0, -26, 78, 0, 0},
    {0, -25, 77, 0, 0},
    {1, -26, 77, 0, 0},
    {0, -25, 77, 0, 0},
    {0, -22, 77, 0, 0},
    {11, -21, 77, 0, 0},
    {0, -17, 69, 0, 0},
    {0, 1, 48, 0, 0},
    {0, 2, 30, 0, 0},
    {0, 1, 10, 0, 0},
    {0, 1, 7, 0, 0},
    {5, 1, 5, 0, 0},
    {1, 1, 4, 0, 0},
    {0, 1, 3, 0, 0},
    {5, 0, 0, 0, 0},
    {1, 1, 0, 0, 0},
    {0, 16, 2, 0, 0},
    {0, 37, 1, 0, 0},
    {0, 44, -6, 0, 0},
    {0, 47, -23, 0, 0},
    {0, 44, -28, 0, 0},
    {0, 46, -34, 0, 0},
    {0, 50, -44, 0, 0},
    {0, 51, -47, 0, 0},
    {1, 51, -48, 0, 0},
    {0, 57, -47, 0, 0},
    {0, 63, -42, 0, 0},
    {0, 68, -37, 0, 0},
    {1, 72, -36, 0, 0},
    {0, 73, -37, 0, 0},
    {0, 72, -39, 0, 0},
    {0, 72, -42, 0, 0},
    {0, 70, -49, 0, 0},
    {0, 66, -65, 0, 0},
    {31, 65, -71, 0, 0},
    {0, 65, -69, 0, 0},
    {0, 65, -66, 0, 0},
    {4, 66, -63, 0, 0},
    {0, 66, -62, 0, 0},
    {0, 66, -61, 0, 0},
    {1, 67, -60, 0, 0},
    {2, 67, -59, 0, 0},
    {0, 55, -49, 0, 0},
    {0, 19, -26, 0, 0},
    {1, 14, -18, 0, 0},
    {0, 13, -18, 0, 0},
    {0, 2, -10, 0, 0},
    {0, 1, -6, 0, 0},
    {0, 1, -5, 0, 0},
    {0, 1, -4, 0, 0},
    {1, 1, -2, 0, 0},
    {0, 1, -5, 0, 0},
    {0, 8, -12, 0, 0},
    {0, 55, -32, 0, 0},
    {8, 72, -40, 0, 0},
    {0, 72, -41, 0, 0},
    {13, 72, -43, 0, 0},
    {0, 71, -43, 0, 0},
    {0, 48, -41, 0, 0},
    {0, 1, -11, 0, 0},
    {0, 1, -7, 0, 0},
    {6, 0, -1, 0, 0},
    {4, 1, -1, 0, 0},
    {0, 1, -2, 0, 0},
    {0, 1, -9, 0, 0},
    {0, 2, -12, 0, 0},
    {0, 3, -13, 0, 0},
    {0, 29, -34, 0, 0},
    {2, 65, -65, 0, 0},
    {0, 65, -65, A_BUTTON, A_BUTTON},
    {0, 65, -65, A_BUTTON, 0},
    {0, 66, -65, A_BUTTON, 0},
    {0, 66, -65, A_BUTTON, 0},
    {0, 66, -65, A_BUTTON, 0},
    {0, 66, -65, A_BUTTON, 0},
    {0, 66, -64, A_BUTTON, 0},
    {0, 66, -64, A_BUTTON, 0},
    {0, 66, -64, A_BUTTON, 0},
    {0, 66, -61, A_BUTTON, 0},
    {0, 67, -58, A_BUTTON, 0},
    {0, 67, -57, A_BUTTON, 0},
    {0, 67, -57, A_BUTTON, 0},
    {0, 67, -57, A_BUTTON, 0},
    {0, 67, -57, A_BUTTON, 0},
    {0, 67, -57, A_BUTTON, 0},
    {0, 67, -57, A_BUTTON, 0},
    {0, 68, -56, A_BUTTON, 0},
    {0, 68, -56, A_BUTTON, 0},
    {0, 68, -56, A_BUTTON, 0},
    {0, 68, -56, A_BUTTON, 0},
    {0, 68, -56, A_BUTTON, 0},
    {0, 68, -56, A_BUTTON, 0},
    {0, 69, -54, 0, 0},
    {0, 69, -50, 0, 0},
    {0, 71, -43, 0, 0},
    {0, 73, -38, 0, 0},
    {0, 74, -33, 0, 0},
    {0, 75, -30, 0, 0},
    {0, 77, -21, 0, 0},
    {0, 78, -16, 0, 0},
    {0, 79, -15, 0, 0},
    {0, 79, -15, A_BUTTON, A_BUTTON},
    {0, 79, -15, A_BUTTON, 0},
    {0, 79, -15, A_BUTTON, 0},
    {0, 79, -15, A_BUTTON, 0},
    {0, 79, -14, A_BUTTON, 0},
    {0, 79, -13, A_BUTTON, 0},
    {0, 80, -12, A_BUTTON, 0},
    {0, 80, -11, A_BUTTON, 0},
    {0, 80, -10, A_BUTTON, 0},
    {0, 80, -8, A_BUTTON, 0},
    {0, 81, -5, A_BUTTON, 0},
    {0, 81, -3, A_BUTTON, 0},
    {0, 81, -3, A_BUTTON, 0},
    {0, 81, -3, A_BUTTON, 0},
    {0, 81, -2, A_BUTTON, 0},
    {0, 77, 14, 0, 0},
    {0, 73, 31, 0, 0},
    {0, 66, 55, 0, 0},
    {0, 63, 68, 0, 0},
    {0, 57, 68, 0, 0},
    {1, 54, 68, 0, 0},
    {0, 53, 68, 0, 0},
    {0, 41, 71, 0, 0},
    {0, 15, 77, 0, 0},
    {0, 1, 80, 0, 0},
    {10, 0, 80, 0, 0},
    {5, -1, 80, 0, 0},
    {6, 4, 80, 0, 0},
    {4, 2, 80, 0, 0},
    {7, 3, 80, 0, 0},
    {0, 9, 79, 0, 0},
    {0, 23, 77, 0, 0},
    {4, 37, 74, 0, 0},
    {0, 32, 74, 0, 0},
    {0, 31, 74, 0, 0},
    {0, 30, 74, 0, 0},
    {11, 28, 74, 0, 0},
    {0, 27, 74, 0, 0},
    {0, 24, 75, 0, 0},
    {0, 19, 76, 0, 0},
    {1, 18, 77, 0, 0},
    {0, 11, 78, 0, 0},
    {53, 5, 79, 0, 0},
    {28, 4, 79, 0, 0},
    {0, 3, 79, 0, 0},
    {1, 2, 79, 0, 0},
    {44, 1, 80, 0, 0},
    {0, 1, 65, 0, 0},
    {0, 0, 1, 0, 0},
    {50, 0, -2, 0, 0},
    {0, 0, -2, A_BUTTON, A_BUTTON},
    {0, 0, -2, A_BUTTON, 0},
    {4, 0, -2, 0, 0},
    {0, 0, -1, B_BUTTON, B_BUTTON},
    {1, 0, -1, B_BUTTON, 0},
    {0, 0, -1, 0, 0},
    {0, 0, -3, B_BUTTON, B_BUTTON},
    {0, 0, -3, B_BUTTON, 0},
    {0, 2, -21, B_BUTTON, 0},
    {0, 5, -39, 0, 0},
    {0, 5, -82, 0, 0},
    {0, -17, -82, 0, 0},
    {0, -23, -80, B_BUTTON, B_BUTTON},
    {2, -23, -80, 0, 0},
    {5, -27, -79, 0, 0},
    {0, -30, -79, 0, 0},
    {0, -34, -79, 0, 0},
    {0, -35, -78, 0, 0},
    {0, -39, -78, 0, 0},
    {0, -43, -78, 0, 0},
    {0, -43, -77, 0, 0},
    {0, -44, -77, 0, 0},
    {0, -44, -76, 0, 0},
    {0, -43, -76, 0, 0},
    {0, -36, -77, 0, 0},
    {4, -35, -77, 0, 0},
    {0, -31, -78, 0, 0},
    {0, -15, -79, 0, 0},
    {0, 6, -55, 0, 0},
    {0, 6, -25, 0, 0},
    {0, 1, -11, 0, 0},
    {0, 0, -3, 0, 0},
    {10, 0, -1, 0, 0},
    {0, 0, -3, 0, 0},
    {0, -2, -11, 0, 0},
    {0, 4, -41, 0, 0},
    {0, 20, -83, 0, 0},
    {0, 6, -85, 0, 0},
    {0, 5, -85, 0, 0},
    {4, 4, -84, 0, 0},
    {1, 13, -84, 0, 0},
    {0, 5, -84, 0, 0},
    {0, -38, -78, 0, 0},
    {2, -57, -75, 0, 0},
    {0, -63, -74, 0, 0},
    {2, -65, -74, 0, 0},
    {0, -66, -73, 0, 0},
    {0, -68, -65, 0, 0},
    {0, -72, -51, 0, 0},
    {0, -75, -33, 0, 0},
    {0, -79, -19, 0, 0},
    {0, -81, -7, 0, 0},
    {0, -81, -6, 0, 0},
    {0, -81, -3, 0, 0},
    {0, -81, 1, 0, 0},
    {2, -80, 3, 0, 0},
    {1, -80, 5, 0, 0},
    {0, -79, 10, 0, 0},
    {0, -76, 22, 0, 0},
    {0, -47, 40, 0, 0},
    {0, 6, 24, 0, 0},
    {0, 26, 33, 0, 0},
    {0, 72, 41, 0, 0},
    {0, 76, 27, 0, 0},
    {1, 77, 18, 0, 0},
    {0, 77, 17, 0, 0},
    {0, 81, -4, 0, 0},
    {0, 77, -25, 0, 0},
    {0, 70, -44, 0, 0},
    {0, 13, -37, 0, 0},
    {0, 0, -3, B_BUTTON, B_BUTTON},
    {0, 0, -1, B_BUTTON, 0},
    {9, 0, -1, 0, 0},
    {0, 0, -5, 0, 0},
    {0, 2, -20, 0, 0},
    {0, 6, -38, 0, 0},
    {0, 6, -45, 0, 0},
    {0, 7, -52, 0, 0},
    {0, 16, -79, 0, 0},
    {4, 20, -81, 0, 0},
    {0, 39, -78, 0, 0},
    {0, 64, -70, 0, 0},
    {0, 70, -48, 0, 0},
    {0, 74, -35, 0, 0},
    {0, 76, -28, 0, 0},
    {0, 78, -16, 0, 0},
    {0, 77, 14, 0, 0},
    {0, 65, 63, 0, 0},
    {0, 63, 67, 0, 0},
    {0, 59, 69, 0, 0},
    {0, 52, 69, 0, 0},
    {2, 49, 70, 0, 0},
    {0, 54, 70, 0, 0},
    {0, 58, 70, 0, 0},
    {0, 60, 70, 0, 0},
    {18, 63, 69, 0, 0},
    {0, 62, 69, 0, 0},
    {0, 60, 69, 0, 0},
    {0, 57, 69, 0, 0},
    {11, 56, 69, 0, 0},
    {0, 55, 69, 0, 0},
    {3, 54, 69, 0, 0},
    {1, 53, 69, 0, 0},
    {0, 52, 69, 0, 0},
    {0, 49, 69, 0, 0},
    {0, 40, 72, 0, 0},
    {0, 25, 75, 0, 0},
    {0, 13, 78, 0, 0},
    {0, 8, 78, 0, 0},
    {22, 7, 79, 0, 0},
    {20, 6, 79, 0, 0},
    {0, 5, 79, 0, 0},
    {0, 3, 79, 0, 0},
    {2, 2, 79, 0, 0},
    {9, 2, 80, 0, 0},
    {0, 2, 78, 0, 0},
    {0, 2, 69, 0, 0},
    {0, 2, 54, 0, 0},
    {0, 2, 37, 0, 0},
    {0, 1, 7, 0, 0},
    {29, 0, -2, 0, 0},
    {0, 0, -2, L_CBUTTONS, L_CBUTTONS},
    {2, 0, -2, L_CBUTTONS, 0},
    {0, 0, -2, 0, 0},
    {1, 0, -1, 0, 0},
    {15, 0, -2, 0, 0},
    {0, 0, -1, L_CBUTTONS, L_CBUTTONS},
    {2, 0, -1, L_CBUTTONS, 0},
    {1, 0, -1, 0, 0},
    {0, 0, -1, L_CBUTTONS, L_CBUTTONS},
    {2, 0, -1, L_CBUTTONS, 0},
    {13, 0, -1, 0, 0},
    {0, 0, -3, 0, 0},
    {0, -1, -11, 0, 0},
    {0, -2, -22, L_CBUTTONS, L_CBUTTONS},
    {0, -2, -34, L_CBUTTONS, 0},
    {0, -10, -57, 0, 0},
    {0, -26, -69, 0, 0},
    {0, -35, -72, 0, 0},
    {0, -30, -50, 0, 0},
    {0, -9, -29, 0, 0},
    {0, -21, -54, 0, 0},
    {0, -41, -74, 0, 0},
    {0, -46, -76, 0, 0},
    {0, -36, -54, 0, 0},
    {0, 0, -2, 0, 0},
    {0, 0, -6, 0, 0},
    {0, -38, -49, 0, 0},
    {0, -65, -72, 0, 0},
    {0, -65, -72, L_CBUTTONS, L_CBUTTONS},
    {0, -41, -48, L_CBUTTONS, 0},
    {0, 0, -3, L_CBUTTONS, 0},
    {0, -19, -38, 0, 0},
    {0, -59, -74, 0, 0},
    {0, -65, -74, 0, 0},
    {0, -65, -74, L_CBUTTONS, L_CBUTTONS},
    {0, -34, -43, L_CBUTTONS, 0},
    {0, -28, -43, L_CBUTTONS, 0},
    {0, -48, -74, L_CBUTTONS, 0},
    {0, -52, -75, 0, 0},
    {0, -51, -75, 0, 0},
    {0, -1, 0, 0, 0},
    {0, 0, -3, 0, 0},
    {1, 0, -2, 0, 0},
    {0, -2, -7, 0, 0},
    {0, -13, -22, 0, 0},
    {0, -14, -23, 0, 0},
    {0, -2, -14, 0, 0},
    {14, 0, -1, 0, 0},
    {0, 0, -2, 0, 0},
    {1, 0, -3, 0, 0},
    {0, 1, 18, 0, 0},
    {0, -13, 61, 0, 0},
    {0, -22, 76, 0, 0},
    {0, -22, 77, 0, 0},
    {0, -13, 78, 0, 0},
    {0, -3, 79, 0, 0},
    {15, -1, 80, 0, 0},
    {0, -4, 80, 0, 0},
    {0, -10, 80, 0, 0},
    {0, -15, 80, 0, 0},
    {3, -17, 80, 0, 0},
    {0, -21, 79, 0, 0},
    {3, -25, 79, 0, 0},
    {0, -25, 78, 0, 0},
    {3, -25, 77, 0, 0},
    {0, -24, 77, 0, 0},
    {0, -14, 77, 0, 0},
    {0, -3, 79, 0, 0},
    {9, -1, 80, 0, 0},
    {9, 2, 80, 0, 0},
    {0, 4, 80, 0, 0},
    {0, 14, 78, 0, 0},
    {2, 21, 77, 0, 0},
    {2, 15, 77, 0, 0},
    {0, 20, 77, 0, 0},
    {0, 21, 77, A_BUTTON, A_BUTTON},
    {0, 21, 77, A_BUTTON, 0},
    {0, 10, 78, A_BUTTON, 0},
    {0, 2, 79, A_BUTTON, 0},
    {0, 2, 80, A_BUTTON, 0},
    {0, 0, 80, 0, 0},
    {0, -5, 80, 0, 0},
    {4, -7, 80, 0, 0},
    {0, -9, 77, 0, 0},
    {0, -1, 50, 0, 0},
    {0, 1, 6, 0, 0},
    {57, 0, -2, 0, 0},
    {5, 1, 0, 0, 0},
    {2, 1, -1, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, -1, 0, 0},
    {0, 0, -1, 0, 0}
};

titleDemo_controller controller_data_CARRIE[] = {
    {67, 0, 0, 0, 0},
    {0, 0, -3, 0, 0},
    {0, 0, -6, 0, 0},
    {1, 0, -7, 0, 0},
    {1, 0, -2, 0, 0},
    {0, 0, -9, 0, 0},
    {0, -13, -44, 0, 0},
    {0, -16, -66, 0, 0},
    {0, -16, -79, 0, 0},
    {0, -8, -82, 0, 0},
    {7, -6, -82, 0, 0},
    {0, 0, -83, 0, 0},
    {0, 4, -83, 0, 0},
    {30, 5, -83, 0, 0},
    {0, 5, -83, B_BUTTON, B_BUTTON},
    {14, 5, -83, B_BUTTON, 0},
    {1, 6, -83, B_BUTTON, 0},
    {1, 7, -83, B_BUTTON, 0},
    {7, 9, -83, B_BUTTON, 0},
    {0, 10, -83, B_BUTTON, 0},
    {0, 20, -83, B_BUTTON, 0},
    {0, 29, -81, B_BUTTON, 0},
    {7, 31, -80, B_BUTTON, 0},
    {3, 30, -80, B_BUTTON, 0},
    {0, 26, -80, B_BUTTON, 0},
    {0, 19, -81, B_BUTTON, 0},
    {0, 12, -82, B_BUTTON, 0},
    {0, 10, -82, B_BUTTON, 0},
    {0, 8, -82, B_BUTTON, 0},
    {19, 7, -82, B_BUTTON, 0},
    {17, 8, -82, B_BUTTON, 0},
    {0, 10, -82, B_BUTTON, 0},
    {0, 21, -61, B_BUTTON, 0},
    {0, 2, -16, 0, 0},
    {7, 0, -2, 0, 0},
    {0, 1, -4, 0, 0},
    {2, 1, -6, 0, 0},
    {0, 1, -7, 0, 0},
    {0, 7, -19, 0, 0},
    {0, 20, -33, 0, 0},
    {0, 47, -70, 0, 0},
    {0, 49, -74, 0, 0},
    {0, 49, -75, 0, 0},
    {9, 47, -75, 0, 0},
    {0, 47, -75, B_BUTTON, B_BUTTON},
    {0, 49, -75, B_BUTTON, 0},
    {0, 54, -75, B_BUTTON, 0},
    {0, 55, -75, B_BUTTON, 0},
    {0, 56, -74, B_BUTTON, 0},
    {0, 58, -74, B_BUTTON, 0},
    {1, 59, -74, B_BUTTON, 0},
    {0, 63, -73, B_BUTTON, 0},
    {3, 64, -72, B_BUTTON, 0},
    {0, 65, -69, B_BUTTON, 0},
    {0, 65, -65, B_BUTTON, 0},
    {1, 66, -65, B_BUTTON, 0},
    {0, 65, -62, B_BUTTON, 0},
    {0, 34, -36, B_BUTTON, 0},
    {3, 0, -2, B_BUTTON, 0},
    {0, 1, 0, B_BUTTON, 0},
    {0, -6, 21, B_BUTTON, 0},
    {0, -37, 47, B_BUTTON, 0},
    {0, -47, 55, B_BUTTON, 0},
    {0, -51, 61, B_BUTTON, 0},
    {0, -54, 71, B_BUTTON, 0},
    {0, -62, 71, B_BUTTON, 0},
    {3, -65, 71, B_BUTTON, 0},
    {0, -66, 68, B_BUTTON, 0},
    {0, -66, 66, B_BUTTON, 0},
    {0, -49, 59, B_BUTTON, 0},
    {0, 0, 0, B_BUTTON, 0},
    {3, 0, -1, 0, 0},
    {0, 1, -3, 0, 0},
    {0, 13, -19, 0, 0},
    {0, 66, -61, 0, 0},
    {0, 66, -62, 0, 0},
    {0, 72, -42, 0, 0},
    {0, 0, -2, 0, 0},
    {2, 0, -1, 0, 0},
    {0, 0, -5, B_BUTTON, B_BUTTON},
    {0, 1, -6, B_BUTTON, 0},
    {0, 1, 0, B_BUTTON, 0},
    {4, 0, -1, B_BUTTON, 0},
    {0, -1, -1, B_BUTTON, 0},
    {0, -6, 19, 0, 0},
    {0, -32, 51, 0, 0},
    {2, -54, 70, 0, 0},
    {2, -51, 70, 0, 0},
    {0, -52, 70, 0, 0},
    {0, -44, 72, 0, 0},
    {0, -9, 78, 0, 0},
    {1, -1, 81, 0, 0},
    {0, 1, 83, 0, 0},
    {0, 1, 82, 0, 0},
    {4, 1, 81, 0, 0},
    {0, -2, 81, 0, 0},
    {1, -8, 81, 0, 0},
    {0, -21, 78, L_CBUTTONS, L_CBUTTONS},
    {0, -58, 73, L_CBUTTONS, 0},
    {0, -66, 66, L_CBUTTONS, 0},
    {0, -14, 32, 0, 0},
    {0, 0, -1, 0, 0},
    {0, 0, -1, L_CBUTTONS, L_CBUTTONS},
    {0, 0, -1, L_CBUTTONS, 0},
    {0, 0, -3, L_CBUTTONS, 0},
    {0, 0, 5, 0, 0},
    {0, -5, 19, 0, 0},
    {0, -59, 32, 0, 0},
    {0, -75, 32, 0, 0},
    {0, -75, 29, 0, 0},
    {1, -75, 27, 0, 0},
    {0, -75, 25, 0, 0},
    {2, -76, 23, 0, 0},
    {0, -77, 19, 0, 0},
    {0, -79, 11, 0, 0},
    {0, -79, 9, 0, 0},
    {0, -79, 12, 0, 0},
    {1, -78, 19, 0, 0},
    {1, -78, 18, 0, 0},
    {0, -77, 23, 0, 0},
    {0, -77, 21, 0, 0},
    {0, -79, 12, 0, 0},
    {0, -78, 3, 0, 0},
    {0, -28, -34, 0, 0},
    {0, -20, -57, B_BUTTON, B_BUTTON},
    {0, -20, -67, B_BUTTON, 0},
    {0, -20, -60, B_BUTTON, 0},
    {0, 0, -2, B_BUTTON, 0},
    {1, 0, -1, B_BUTTON, 0},
    {0, 1, -9, B_BUTTON, 0},
    {2, 1, -13, B_BUTTON, 0},
    {0, 1, -11, B_BUTTON, 0},
    {1, 1, -8, B_BUTTON, 0},
    {0, 6, -2, B_BUTTON, 0},
    {0, 46, -18, B_BUTTON, 0},
    {0, 71, -45, B_BUTTON, 0},
    {0, 60, -46, B_BUTTON, 0},
    {0, 0, -5, B_BUTTON, 0},
    {1, 0, 0, B_BUTTON, 0},
    {1, 0, -1, 0, 0},
    {0, 1, -4, 0, 0},
    {0, 16, -39, 0, 0},
    {1, 48, -74, 0, 0},
    {0, 44, -75, 0, 0},
    {1, 43, -76, 0, 0},
    {0, 44, -76, 0, 0},
    {2, 45, -76, 0, 0},
    {0, 56, -74, 0, 0},
    {0, 61, -73, 0, 0},
    {0, 64, -72, 0, 0},
    {0, 65, -68, 0, 0},
    {0, 68, -57, 0, 0},
    {0, 69, -53, 0, 0},
    {0, 70, -47, 0, 0},
    {0, 73, -35, 0, 0},
    {0, 74, -35, 0, 0},
    {0, 69, -56, 0, 0},
    {0, 65, -70, 0, 0},
    {0, 65, -71, 0, 0},
    {1, 61, -71, 0, 0},
    {0, 59, -71, 0, 0},
    {0, 42, -76, 0, 0},
    {3, 3, -84, 0, 0},
    {0, -10, -82, 0, 0},
    {0, -13, -26, 0, 0},
    {0, 0, -1, 0, 0},
    {0, 1, 10, 0, 0},
    {0, 1, 14, 0, 0},
    {0, 0, 14, B_BUTTON, B_BUTTON},
    {0, 0, 0, B_BUTTON, 0},
    {4, 0, -1, B_BUTTON, 0},
    {0, 0, 6, B_BUTTON, 0},
    {0, 0, 11, B_BUTTON, 0},
    {0, -53, 38, B_BUTTON, 0},
    {1, -71, 44, B_BUTTON, 0},
    {0, -64, 44, B_BUTTON, 0},
    {0, -19, 35, B_BUTTON, 0},
    {4, 0, 0, B_BUTTON, 0},
    {0, -1, 7, B_BUTTON, 0},
    {0, -53, 33, B_BUTTON, 0},
    {1, -71, 43, B_BUTTON, 0},
    {0, -70, 45, B_BUTTON, 0},
    {0, -29, 41, B_BUTTON, 0},
    {5, 0, -2, 0, 0},
    {0, -37, -5, 0, 0},
    {0, -70, -3, 0, 0},
    {0, -72, 1, 0, 0},
    {0, -44, 17, 0, 0},
    {3, 0, 0, 0, 0},
    {0, -1, 0, 0, 0},
    {0, -5, 3, 0, 0},
    {0, -6, 17, 0, 0},
    {0, 5, 22, 0, 0},
    {0, 10, 22, 0, 0},
    {0, 7, 22, 0, 0},
    {0, -21, 37, 0, 0},
    {0, -66, 63, 0, 0},
    {1, -66, 62, 0, 0},
    {0, -66, 65, 0, 0},
    {0, -47, 71, 0, 0},
    {0, -6, 79, 0, 0},
    {0, 26, 78, 0, 0},
    {0, 46, 73, 0, 0},
    {0, 40, 72, 0, 0},
    {2, 2, 81, 0, 0},
    {0, 37, 75, 0, 0},
    {0, 43, 72, 0, 0},
    {0, 38, 72, 0, 0},
    {0, 37, 72, 0, 0},
    {0, 37, 73, 0, 0},
    {0, -4, 81, 0, 0},
    {0, -48, 74, 0, 0},
    {0, -50, 73, 0, 0},
    {0, -42, 72, 0, 0},
    {0, -32, 74, 0, 0},
    {0, -56, 72, 0, 0},
    {0, -67, 60, 0, 0},
    {0, -73, 36, 0, 0},
    {0, -81, -7, 0, 0},
    {2, -79, -20, 0, 0},
    {0, -69, -51, 0, 0},
    {0, -43, -76, 0, 0},
    {0, -13, -82, 0, 0},
    {0, 0, -85, 0, 0},
    {0, 6, -85, 0, 0},
    {0, 33, -80, 0, 0},
    {0, 66, -62, 0, 0},
    {0, 76, -28, 0, 0},
    {0, 81, -6, 0, 0},
    {0, 77, 14, 0, 0},
    {0, 75, 27, 0, 0},
    {0, 73, 41, L_CBUTTONS, L_CBUTTONS},
    {0, 65, 72, L_CBUTTONS, 0},
    {0, 56, 71, L_CBUTTONS, 0},
    {0, -15, 79, 0, 0},
    {0, -24, 77, 0, 0},
    {0, -24, 77, L_CBUTTONS, L_CBUTTONS},
    {0, -24, 77, L_CBUTTONS, 0},
    {0, -23, 77, L_CBUTTONS, 0},
    {0, -51, 72, L_CBUTTONS, 0},
    {0, -57, 72, 0, 0},
    {0, -59, 70, 0, 0},
    {0, -67, 57, L_CBUTTONS, L_CBUTTONS},
    {0, -70, 50, L_CBUTTONS, 0},
    {0, -72, 41, L_CBUTTONS, 0},
    {1, -72, 41, 0, 0},
    {0, -60, 41, 0, 0},
    {0, -38, 41, 0, 0},
    {0, -21, 39, 0, 0},
    {0, 1, 11, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, -2, 0, 0},
    {0, 0, -2, L_CBUTTONS, L_CBUTTONS},
    {0, 0, -2, L_CBUTTONS, 0},
    {0, -2, -2, L_CBUTTONS, 0},
    {0, -46, -9, L_CBUTTONS, 0},
    {0, -79, -18, 0, 0},
    {0, -76, -26, 0, 0},
    {0, -66, -72, L_CBUTTONS, L_CBUTTONS},
    {1, -54, -74, L_CBUTTONS, 0},
    {0, -14, -23, L_CBUTTONS, 0},
    {1, 0, -2, 0, 0},
    {0, 0, -2, L_CBUTTONS, L_CBUTTONS},
    {0, -3, -16, L_CBUTTONS, 0},
    {0, -4, -31, L_CBUTTONS, 0},
    {0, -4, -33, L_CBUTTONS, 0},
    {0, 1, -4, 0, 0},
    {0, 0, -1, 0, 0},
    {0, 0, -1, L_CBUTTONS, L_CBUTTONS},
    {0, 0, -1, L_CBUTTONS, 0},
    {0, 0, -2, L_CBUTTONS, 0},
    {0, -11, -19, L_CBUTTONS, 0},
    {0, -21, -32, 0, 0},
    {0, -22, -33, 0, 0},
    {0, -9, -15, 0, 0},
    {0, -17, -22, L_CBUTTONS, L_CBUTTONS},
    {0, -71, -50, L_CBUTTONS, 0},
    {0, -71, -50, 0, 0},
    {0, -71, -49, 0, 0},
    {0, -74, -35, 0, 0},
    {0, -74, -37, 0, 0},
    {0, -71, -50, L_CBUTTONS, L_CBUTTONS},
    {0, -70, -55, L_CBUTTONS, 0},
    {0, -55, -29, L_CBUTTONS, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 4, 0, 0},
    {0, 0, -1, L_CBUTTONS, L_CBUTTONS},
    {2, 0, -1, L_CBUTTONS, 0},
    {2, 0, -1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 9, 0, 0},
    {0, 1, 17, 0, 0},
    {0, 3, 33, 0, 0},
    {0, 10, 50, 0, 0},
    {0, 23, 62, 0, 0},
    {0, 40, 63, 0, 0},
    {0, 43, 63, 0, 0},
    {0, 30, 63, 0, 0},
    {0, 1, 60, 0, 0},
    {0, -3, 38, 0, 0},
    {0, 1, 6, 0, 0},
    {2, 0, -2, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 12, 0, 0},
    {0, 4, 17, 0, 0},
    {0, 10, 19, 0, 0},
    {0, 14, 22, 0, 0},
    {0, 15, 26, 0, 0},
    {0, 15, 29, 0, 0},
    {0, 11, 29, 0, 0},
    {0, 3, 18, 0, 0},
    {11, 0, 0, 0, 0},
    {23, 1, 0, 0, 0},
    {0, 1, -3, 0, 0},
    {0, 1, -7, 0, 0},
    {6, 1, -8, 0, 0},
    {0, 1, -10, 0, 0},
    {0, 4, -24, 0, 0},
    {0, 5, -34, 0, 0},
    {2, 5, -36, 0, 0},
    {0, 5, -31, 0, 0},
    {0, 5, -24, 0, 0},
    {0, 1, -14, 0, 0},
    {0, 1, -6, 0, 0},
    {1, 0, -3, 0, 0},
    {7, 0, -2, 0, 0},
    {0, 0, -3, 0, 0},
    {0, 0, -4, 0, 0},
    {0, 1, -10, 0, 0},
    {0, 1, -15, 0, 0},
    {1, 1, -16, 0, 0},
    {0, 1, -15, 0, 0},
    {0, 1, -11, 0, 0},
    {4, 1, -10, 0, 0},
    {26, 1, -9, 0, 0},
    {32, 1, -10, 0, 0},
    {0, 0, -2, 0, 0},
    {34, 0, -1, 0, 0},
    {4, 0, -2, 0, 0},
    {0, 0, 0, 0, 0},
    {2, 0, -1, 0, 0}
};

// clang-format off

titleDemo_func_t titleDemo_functions[] = {
    titleDemo_init,
    titleDemo_loop,
    titleDemo_exit
};

// clang-format on

void titleDemo_entrypoint(titleDemo* self) {
    ENTER(self, titleDemo_functions);
}

void titleDemo_init(titleDemo* self) {
    u8 i;

    // Make sure not to proceed if the game is fading or if it's loading a file
    if ((*fade_isFading)() || (sys.file_load_array_ID != 0) || ptr_DMAMgr->DMAChunkMgr == NULL)
        return;

    // Reset much of the save variables before entering the game
    sys.current_opened_menu            = MENU_ID_NOT_ON_MENU;
    sys.SaveStruct_gameplay.life       = 100;
    sys.SaveStruct_gameplay.field_0x5C = 100;
    sys.entrance_cutscene_ID = sys.cutscene_flags = 0;
    sys.cutscene_ID                               = CUTSCENE_ID_NONE;
    sys.SaveStruct_gameplay.gold                  = 0;
    sys.NOT_ON_MENU                               = sys.current_opened_menu;

    // Remove inventory items
    // clang-format off
    for (i = 0; i < SIZE_ITEMS_ARRAY; i++) sys.SaveStruct_gameplay.items.array[i] = ITEM_ID_NOTHING;
    // clang-format on

    // Clear event flags
    // clang-format off
    for (i = 0; i < NUM_EVENT_FLAGS; i++) sys.SaveStruct_gameplay.event_flags[i] = 0;
    // clang-format on

    sys.SaveStruct_gameplay.player_status                        = 0;
    sys.SaveStruct_gameplay.subweapon                            = SUBWEAPON_NONE;
    sys.current_PowerUp_level                                    = 0;
    sys.SaveStruct_gameplay.health_depletion_rate_while_poisoned = 0;
    sys.SaveStruct_gameplay.current_hour_VAMP                    = 0;
    sys.SaveStruct_gameplay.week                                 = 0;
    sys.SaveStruct_gameplay.day                                  = 0;
    sys.SaveStruct_gameplay.hour                                 = 0;
    sys.SaveStruct_gameplay.minute                               = 0;
    sys.SaveStruct_gameplay.seconds                              = 0;
    sys.SaveStruct_gameplay.milliseconds                         = 0;

    (*atari_work_table_init)();

    for (i = 0; i < OBJ_NUM_ALLOC_DATA; i++)
        ((cv64_object_t*) self)->alloc_data[i] = NULL;

    // Prepare character scenarios
    if (sys.title_demo_character == REINHARDT) {
        // clang-format off
        sys.map = CHIKA_KODO,
        // clang-format on
            sys.spawn                      = 2;
        sys.map_fade_out_time              = 30;
        sys.map_fade_in_time               = 30;
        sys.map_fade_in_color.r            = 0;
        sys.map_fade_in_color.g            = 0;
        sys.map_fade_in_color.b            = 0;
        sys.SaveStruct_gameplay.character  = REINHARDT;
        self->controller_data_max_keyframe = ARRAY_COUNT(controller_data_REINHARDT);
    } else {
        // clang-format off
        sys.map = CHIKA_SUIRO,
        // clang-format on
            sys.spawn                      = 2;
        sys.map_fade_in_color.r            = 0;
        sys.map_fade_in_color.g            = 0;
        sys.map_fade_in_color.b            = 0;
        sys.map_fade_out_time              = 30;
        sys.map_fade_in_time               = 30;
        sys.SaveStruct_gameplay.character  = CARRIE;
        self->controller_data_max_keyframe = ARRAY_COUNT(controller_data_CARRIE);
    }

    sys.field89_0x2644c = 0;

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

// Note: u8 field24_0x242be[6]; ----> is actually a s16
void titleDemo_loop(titleDemo* self) {
    actorVisualData* playerVisualdata;

    // Log the time it takes until the map is ready,
    // and thus we can begin playing the controller inputs back
    if ((sys.MENU_IS_CLOSED == FALSE) || (sys.map_is_setup == FALSE)) {
        self->wait_cont++;
        (*osSyncPrintf)("wait cont = %d", self->wait_cont);
        sys.controllers[CONT_0].joystick_x      = 0;
        sys.controllers[CONT_0].joystick_y      = 0;
        sys.controllers[CONT_0].buttons_held    = 0;
        sys.controllers[CONT_0].buttons_pressed = 0;
        sys.global_timer_capped                 = 0;
        return;
    }

    sys.field24_0x242be = 0;

    // Reset the most commonly-used random seeds to ensure that randomized events
    // behave the same every time the demo is played
    (*srand)(0);
    (*random_initSeed)();

    // Begin the demo
    if (self->state == TITLE_DEMO_STATE_INIT) {
        self->controller_data_current_keyframe = 0;
        if (sys.title_demo_character == REINHARDT) {
            self->controller_data_current_keyframe_duration =
                controller_data_REINHARDT[self->controller_data_current_keyframe].keyframe_duration;
        } else {
            self->controller_data_current_keyframe_duration =
                controller_data_CARRIE[self->controller_data_current_keyframe].keyframe_duration;
        }
        self->state = TITLE_DEMO_STATE_RUNNING;
    }

    // Skip the demo when pressing the Start of A buttons
    if (CONT_BTNS_PRESSED(CONT_0, (START_BUTTON | RECENTER_BUTTON)) ||
        CONT_BTNS_PRESSED(CONT_0, A_BUTTON)) {
        self->state = TITLE_DEMO_STATE_SKIP;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }

    // Copy the input data into player 1's controller to move the character
    if (sys.title_demo_character == REINHARDT) {
        // Copy inputs
        sys.controllers[CONT_0].joystick_x =
            controller_data_REINHARDT[self->controller_data_current_keyframe].stick_X;
        sys.controllers[CONT_0].joystick_y =
            controller_data_REINHARDT[self->controller_data_current_keyframe].stick_Y;
        sys.controllers[CONT_0].buttons_held =
            controller_data_REINHARDT[self->controller_data_current_keyframe].buttons_held;
        sys.controllers[CONT_0].buttons_pressed =
            controller_data_REINHARDT[self->controller_data_current_keyframe].buttons_pressed;
        // Advance keyframes
        if (self->controller_data_current_keyframe_duration == 0) {
            self->controller_data_current_keyframe++;
            self->controller_data_current_keyframe_duration =
                controller_data_REINHARDT[self->controller_data_current_keyframe].keyframe_duration;
        } else {
            self->controller_data_current_keyframe_duration--;
        }
    } else {
        // Copy inputs
        sys.controllers[CONT_0].joystick_x =
            controller_data_CARRIE[self->controller_data_current_keyframe].stick_X;
        sys.controllers[CONT_0].joystick_y =
            controller_data_CARRIE[self->controller_data_current_keyframe].stick_Y;
        sys.controllers[CONT_0].buttons_held =
            controller_data_CARRIE[self->controller_data_current_keyframe].buttons_held;
        sys.controllers[CONT_0].buttons_pressed =
            controller_data_CARRIE[self->controller_data_current_keyframe].buttons_pressed;
        // Advance keyframes
        if (self->controller_data_current_keyframe_duration == 0) {
            self->controller_data_current_keyframe++;
            self->controller_data_current_keyframe_duration =
                controller_data_CARRIE[self->controller_data_current_keyframe].keyframe_duration;
        } else {
            self->controller_data_current_keyframe_duration--;
        }
    }

    // End the demo when all inputs have been played back
    if (self->controller_data_current_keyframe >= self->controller_data_max_keyframe) {
        self->state = TITLE_DEMO_STATE_END;
    }

    // End the demo if the character dies
    if (ptr_PlayerData != NULL) {
        playerVisualdata = &ptr_PlayerData->visualData;
        if ((ptr_PlayerData->visualData.model != NULL) && (playerVisualdata->flags & DEAD)) {
            self->state = TITLE_DEMO_STATE_END;
        }
    }

    // Exit the demo
    if (self->state == TITLE_DEMO_STATE_END) {
        D_80185F7C_10916C            = TRUE;
        sys.background_color.integer = RGBA(0, 0, 0, 255);
        if (1) {
        }
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void titleDemo_exit(titleDemo* self) {
    u32 character;

    // Fade out and stop the music
    (*play_sound)(SD_CTRL_FADE_OUT_AUDIO_00A);
    (*setPreviousBGMAndStopBGM)();

    // Remove event flags that could have been set when both demos played
    character = sys.title_demo_character;
    if (character == REINHARDT) {
        // Strangely enough, a flag meant for the Villa foyer is unset,
        // even though Reinhardt's demo takes place in Tunnel
        REMOVE_EVENT_FLAGS(
            EVENT_FLAG_ID_VILLA_INSIDE, EVENT_FLAG_VILLA_INSIDE_VAMPIRE_CUTSCENE_WATCHED
        );
    } else {
        REMOVE_EVENT_FLAGS(
            EVENT_FLAG_ID_WATERWAY_AND_CASTLE_CENTER_5F, EVENT_FLAG_WATERWAY_POISON_CUTSCENE_WATCHED
        );
        REMOVE_EVENT_FLAGS(
            EVENT_FLAG_ID_WATERWAY_AND_CASTLE_CENTER_5F,
            EVENT_FLAG_WATERWAY_LIZARDMEN_CUTSCENE_WATCHED
        );
    }

    // Reset cutscene and menu variables
    sys.current_opened_menu = MENU_ID_NOT_ON_MENU;
    sys.cutscene_flags      = 0;
    sys.cutscene_ID         = CUTSCENE_ID_NONE;
    sys.NOT_ON_MENU         = sys.current_opened_menu;

    // When the demo is skipped manually, return back to the title screen
    if (self->state == TITLE_DEMO_STATE_SKIP) {
        (*gamestate_change)(GAMESTATE_TITLE_SCREEN);
    }
    // Go to the Konami logo, and set the demo to the next character
    // to play if the user decides to watch the title demo again
    else if (sys.title_demo_character == REINHARDT) {
        sys.title_demo_character = CARRIE;
        (*gamestate_change)(GAMESTATE_KONAMI_LOGO);
    } else {
        sys.title_demo_character = REINHARDT;
        (*gamestate_change)(GAMESTATE_KONAMI_LOGO);
    }
}
