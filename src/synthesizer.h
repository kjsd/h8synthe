/**
 * @file synthesizer.h
 *
 * @brief �V���Z�T�C�U�[
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
/**
 * @mainpage �͂��߂�
 *
 * @section abstract ���̕����ɂ���
 * ���̕����́A�V���Z�T�C�U�[�̓����\�����L�q�����ڍא݌v�d�l���ł���B@n
 * �����͑傫���f�[�^�\���̉���Z�N�V�����ƁA�t�@�C�����W���[���ʂ�
 * �C���^�t�F�[�X����Z�N�V�����ɕ�����Ă���A���ꂼ��̃Z�N�V������
 * �`���ŉ�����ڂ��T�������t���ŗ񋓂�����A���ڂ̏ڍא����������Ƃ���
 * �\���ɂȂ��Ă���B
 *
 * @section target �Ώ�
 * �V���Z�T�C�U�[�̉�͎҂�ΏۂƂ��������ł���A�V�X�e���̊�{�d�l��
 * H8-BASE2�̃v���b�g�t�H�[���𗝉����Ă��邱�Ƃ��O��ł���B@n
 * �܂��A���̃A�v���P�[�V������H8SDK���g�p���Đ݌v����Ă���B
 *
 * @see H8SDK�ڍא݌v�d�l��
 *
 ***********************************************************************/
#ifndef SYNTH_H_
#define SYNTH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <h8sdk/stddef.h>
#include <h8sdk/ioctl.h>
#include <h8sdk/led.h>
#include <h8sdk/lcd.h>
#include <h8sdk/adc.h>
#include <h8sdk/ps2.h>
#include <h8sdk/kbd_jp106.h>
#include <h8sdk/sound.h>
#include <h8sdk/music.h>
#include <h8sdk/envelope.h>
#include "key_image.h"

/** �L�[�{�[�h�o���N�̐� */
#define NUM_OF_BANK_ 2
/** �o���N������̌��Ր��B2�I�N�^�[�u�� */
#define KEY_OF_BANK_ 29

/**
 * @brief ���Ճp�����[�^�^
 */
typedef struct
{
    _UBYTE key;
    /**< PS/2�L�[�R�[�h */
    _UBYTE freq;
    /**< ���K */
    _UBYTE freq_other;
    /**< freq�ɑ΂��锼����̉��K */
    KEY_IMG_Type break_ch;
    /**< ���Ղ𗣂��Ă���Ƃ���LCD�����R�[�h */
    KEY_IMG_Type make_ch;
    /**< ���Ղ������Ă���Ƃ���LCD�����R�[�h */
    KEY_IMG_Type make_other_ch;
    /**< freq_other�̌��Ղ������Ă���Ƃ���LCD�����R�[�h */
    _SINT lcd_x;
    /**< ���ՃL�����N�^��LCD�\���ʒu�B�� */
    _SINT lcd_y;
    /**< ���ՃL�����N�^��LCD�\���ʒu�B�c */
} KeyParam_;

/**
 * @brief �ÓI�L�[�p�����[�^�e�[�u��
 *
 * �����͂��炩����KeyParam_::key���L�[�Ƃ����n�b�V���l��z��̃C���f�b
 * �N�X�Ƃ����z�u�ŌŒ肳��Ă���B�����48��(4�I�N�^�[�u��)�̃L�[����
 * �̎��Ԃ���ɒP�ʎ��ԂŏI��点�邽�߂ł���B1�o���N�̔z��T�C�Y��2
 * �I�N�^�[�u����24�ł͂Ȃ�29�ɂȂ��Ă���̂́A�z��T�C�Y��f���ɂ���
 * ���ƂŃn�b�V���l�̏d�����ŏ��l�ɂ��邽�߂ł���B
 */
static const KeyParam_ key_table_[NUM_OF_BANK_][KEY_OF_BANK_];

/**
 * @brief �����e�[�u��
 *
 * ���ݍĐ����̉��K�f�[�^���o�^�����B
 */
static _UBYTE pronounce_table_[SOUND_MAX_PRONOUNCE];

/**
 * @brief �^���e�[�u��
 *
 * ���ݘ^�����̃��N�G�X�gID���o�^�����B
 *
 * @see music.h
 */
static MUSIC_RecordReqId rec_table_[SOUND_MAX_PRONOUNCE];

/** �Đ�����LCD�����f�[�^ */
static const _UBYTE play_char_[LCD_CG_ROWS];
/** �Đ�����LCD�����R�[�h */
static const _UBYTE play_ch_;
/** �^������LCD�����f�[�^ */
static const _UBYTE rec_char_[LCD_CG_ROWS];
/** �^������LCD�����R�[�h */
static const _UBYTE rec_ch_;

/**
 * @brief ���ݍĐ����̉�������
 *
 * @param[in] freq �������鉹�̉��K
 *
 * @retval 0�ȏ� pronounce_table_�̃C���f�b�N�X
 * @retval 0���� �w��̉��K�͍Đ�����Ă��Ȃ�
 */
static _SINT findPronounce_(_UBYTE freq);

/**
 * @brief �Đ����Ƃ��ĉ���o�^
 *
 * @param[in] freq �o�^���鉹�̉��K
 *
 * @retval 0�ȏ� pronounce_table_�̃C���f�b�N�X
 * @retval 0���� �e�[�u���T�C�Y�I�[�o�[
 */
static _SINT setPronounce_(_UBYTE freq);

/**
 * @brief �L�[�p�����[�^������
 *
 * @param[in] bank ��������L�[�̃o���N
 * @param[in] key ��������L�[�R�[�h
 *
 * @return ���������L�[�p�����[�^�ւ̃|�C���^
 * @retval NULL �w��̃L�[�͓o�^����Ă��Ȃ�
 */
static KeyParam_* findParam_(_UBYTE bank, _UBYTE key);

/**
 * @brief ���A/D�R���o�[�^����
 *
 * �c�}�~�̒l��ǂ݁A���ʂƃG���x���[�v���x���̐ݒ���X�V����B
 */
static void execADC_();

#ifdef __cplusplus
}
#endif

#endif /* SYNTH_H_ */
