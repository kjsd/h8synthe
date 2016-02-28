/**
 * @file key_image.h
 *
 * @brief 鍵盤画像データ
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
#ifndef KEY_IMG_H_
#define KEY_IMG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <h8sdk/stddef.h>
#include <h8sdk/lcd.h>

/** 1オクターブを表現するキー画像の数 */
#define KEY_IMG_NUM_OF_KEY 7

/** 
 * @brief キー画像の種類
 */
typedef enum
{
    KEY_IMG_T_BLACK = 0,
    /**< 黒鍵があるキー。通常 */
    KEY_IMG_T_BLACK_MAKEW,
    /**< 黒鍵があるキー。白鍵部が押下 */
    KEY_IMG_T_BLACK_MAKEB,
    /**< 黒鍵があるキー。黒鍵部が押下 */
    KEY_IMG_T_WHITE,
    /**< 白鍵のみのキー。通常 */
    
    KEY_IMG_NUM_OF_TYPE
} KEY_IMG_Type;

/** 黒塗り画像の文字コード */
#define KEY_IMG_T_FULL 0xff

/** 1オクターブ分のLCD文字コード列 */
extern const _UBYTE KEY_IMG_initial_frame[KEY_IMG_NUM_OF_KEY];

/** キー画像種別分のキャラクタ画像ビットマップ */
extern const _UBYTE KEY_IMG_char[KEY_IMG_NUM_OF_TYPE][LCD_CG_ROWS];

#ifdef __cplusplus
}
#endif

#endif /* KEY_IMG_H_ */
