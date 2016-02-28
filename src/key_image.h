/**
 * @file key_image.h
 *
 * @brief ���Չ摜�f�[�^
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

/** 1�I�N�^�[�u��\������L�[�摜�̐� */
#define KEY_IMG_NUM_OF_KEY 7

/** 
 * @brief �L�[�摜�̎��
 */
typedef enum
{
    KEY_IMG_T_BLACK = 0,
    /**< ����������L�[�B�ʏ� */
    KEY_IMG_T_BLACK_MAKEW,
    /**< ����������L�[�B������������ */
    KEY_IMG_T_BLACK_MAKEB,
    /**< ����������L�[�B������������ */
    KEY_IMG_T_WHITE,
    /**< �����݂̂̃L�[�B�ʏ� */
    
    KEY_IMG_NUM_OF_TYPE
} KEY_IMG_Type;

/** ���h��摜�̕����R�[�h */
#define KEY_IMG_T_FULL 0xff

/** 1�I�N�^�[�u����LCD�����R�[�h�� */
extern const _UBYTE KEY_IMG_initial_frame[KEY_IMG_NUM_OF_KEY];

/** �L�[�摜��ʕ��̃L�����N�^�摜�r�b�g�}�b�v */
extern const _UBYTE KEY_IMG_char[KEY_IMG_NUM_OF_TYPE][LCD_CG_ROWS];

#ifdef __cplusplus
}
#endif

#endif /* KEY_IMG_H_ */
