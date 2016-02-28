/**
 * @file key_image.c
 *
 * @brief åÆî’âÊëúÉfÅ[É^
 *
 * @htmlonly
 * @version $Id:$
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 * @endhtmlonly
 *
 ***********************************************************************/
#include "key_image.h"


/*
    01234012340123401234012340123401234
   0* * ** * **   ** * ** * ** * **   *
   1* * ** * **   ** * ** * ** * **   *
   2* * ** * **   ** * ** * ** * **   *
   3* * ** * **   ** * ** * ** * **   *
   4* **** ****   ** **** **** ****   *
   5*   **   **   **   **   **   **   *
   6*   **   **   **   **   **   **   *
   7***********************************
*/
const _UBYTE KEY_IMG_initial_frame[KEY_IMG_NUM_OF_KEY] = {
    KEY_IMG_T_BLACK, KEY_IMG_T_BLACK, KEY_IMG_T_WHITE,
    KEY_IMG_T_BLACK, KEY_IMG_T_BLACK, KEY_IMG_T_BLACK,
    KEY_IMG_T_WHITE
};

const _UBYTE KEY_IMG_char[][LCD_CG_ROWS] = {
    { 0x15, 0x15, 0x15, 0x15, 0x17, 0x11, 0x11, 0x1f },
    { 0x1d, 0x1d, 0x1d, 0x1d, 0x1f, 0x1f, 0x1f, 0x1f },
    { 0x17, 0x17, 0x17, 0x17, 0x17, 0x11, 0x11, 0x1f },
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f }
};
