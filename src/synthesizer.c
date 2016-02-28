/**
 * @file synthesizer.c
 *
 * @version $Id: synthesizer.c 140 2009-03-10 07:06:43Z Administrator $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * Synthesizer.
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#ifdef __cplusplus
extern "C" {
void abort(void);
#endif
void main(void);
#ifdef __cplusplus
}
#endif

#include <h8sdk/stdio.h>
#include "synthesizer.h"

/*
    01234
   0*
   1***
   2****
   3*****
   4*****
   5****
   6***
   7*
*/
static const _UBYTE play_char_[LCD_CG_ROWS] = {
    0x10, 0x1c, 0x1e, 0x1f, 0x1f, 0x1e, 0x1c, 0x10
};
static const _UBYTE play_ch_ = 6;
/*
    01234
   0  *
   1 ***
   2*****
   3*****
   4*****
   5*****
   6 ***
   7  *
*/
static const _UBYTE rec_char_[LCD_CG_ROWS] = {
    0x04, 0x0e, 0x1f, 0x1f, 0x1f, 0x1f, 0x0e, 0x04
};
static const _UBYTE rec_ch_ = 7;

static const KeyParam_ key_table_[NUM_OF_BANK_][KEY_OF_BANK_] = {
    {
        { KBD_JP106_W, SOUND_D0, SOUND_Db0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 1, 1 },
        { KBD_JP106_2, SOUND_Cb0, SOUND_C0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 0, 1 },
        { KBD_JP106_U, SOUND_H0, SOUND_NA,
          KEY_IMG_T_WHITE, KEY_IMG_T_FULL, KEY_IMG_T_WHITE, 6, 1},
        { KBD_JP106_7, SOUND_Ab0, SOUND_A0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 5, 1 },
        { KBD_JP106_M, SOUND_E1, SOUND_NA,
          KEY_IMG_T_WHITE, KEY_IMG_T_FULL, KEY_IMG_T_WHITE, 9, 1},
        { KBD_JP106_J, SOUND_Db1, SOUND_D1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 8, 1 },
        { KBD_JP106_COLON, SOUND_Ab1, SOUND_A1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 12, 1 },
        { KBD_JP106_E, SOUND_E0, SOUND_NA,
          KEY_IMG_T_WHITE, KEY_IMG_T_FULL, KEY_IMG_T_WHITE, 2, 1 },
        { KBD_JP106_COMMA, SOUND_F1, SOUND_Fb1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 10, 1 },
        { KBD_JP106_3, SOUND_Db0, SOUND_D0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 1, 1 },

        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_T, SOUND_G0, SOUND_Gb0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 4, 1 },
        { KBD_JP106_R, SOUND_F0, SOUND_Fb0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 3, 1 },
        { KBD_JP106_5, SOUND_Fb0, SOUND_F0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 3, 1 },
        { KBD_JP106_PERIOD, SOUND_G1, SOUND_Gb1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 11, 1 },
        { KBD_JP106_SLASH, SOUND_A1, SOUND_Ab1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 12, 1 },

        { KBD_JP106_L, SOUND_Fb1, SOUND_F1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 10, 1 },
        { KBD_JP106_Q, SOUND_C0, SOUND_Cb0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 0, 1 },
        { KBD_JP106_B, SOUND_C1, SOUND_Cb1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 7, 1 },
        { KBD_JP106_N, SOUND_D1, SOUND_Db1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 8, 1 },
        { KBD_JP106_Y, SOUND_A0, SOUND_Ab0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 5, 1 },
        { KBD_JP106_6, SOUND_Gb0, SOUND_G0,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 4, 1 },
        { KBD_JP106_BACKSLASH, SOUND_H1, SOUND_NA,
          KEY_IMG_T_WHITE, KEY_IMG_T_FULL, KEY_IMG_T_WHITE, 13, 1 },
        { KBD_JP106_H, SOUND_Cb1, SOUND_C1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 7, 1 },
        { KBD_JP106_SEMICOLON, SOUND_Gb1, SOUND_G1,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 11, 1 }
    },
    {
        { KBD_JP106_W, SOUND_D2, SOUND_Db2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 1, 0 },
        { KBD_JP106_2, SOUND_Cb2, SOUND_C2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 0, 0 },
        { KBD_JP106_U, SOUND_H2, SOUND_NA,
          KEY_IMG_T_WHITE, KEY_IMG_T_FULL, KEY_IMG_T_WHITE, 6, 0},
        { KBD_JP106_7, SOUND_Ab2, SOUND_A2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 5, 0 },
        { KBD_JP106_M, SOUND_E3, SOUND_NA,
          KEY_IMG_T_WHITE, KEY_IMG_T_FULL, KEY_IMG_T_WHITE, 9, 0},
        { KBD_JP106_J, SOUND_Db3, SOUND_D3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 8, 0 },
        { KBD_JP106_COLON, SOUND_Ab3, SOUND_A3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 12, 0 },
        { KBD_JP106_E, SOUND_E2, SOUND_NA,
          KEY_IMG_T_WHITE, KEY_IMG_T_FULL, KEY_IMG_T_WHITE, 2, 0 },
        { KBD_JP106_COMMA, SOUND_F3, SOUND_Fb3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 10, 0 },
        { KBD_JP106_3, SOUND_Db2, SOUND_D2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 1, 0 },

        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_NA, SOUND_NA, SOUND_NA,
          KEY_IMG_T_FULL, KEY_IMG_T_FULL, KEY_IMG_T_FULL, 0, 0 },
        { KBD_JP106_T, SOUND_G2, SOUND_Gb2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 4, 0 },
        { KBD_JP106_R, SOUND_F2, SOUND_Fb2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 3, 0 },
        { KBD_JP106_5, SOUND_Fb2, SOUND_F2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 3, 0 },
        { KBD_JP106_PERIOD, SOUND_G3, SOUND_Gb3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 11, 0 },
        { KBD_JP106_SLASH, SOUND_A3, SOUND_Ab3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 12, 0 },

        { KBD_JP106_L, SOUND_Fb3, SOUND_F3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 10, 0 },
        { KBD_JP106_Q, SOUND_C2, SOUND_Cb2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 0, 0 },
        { KBD_JP106_B, SOUND_C3, SOUND_Cb3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 7, 0 },
        { KBD_JP106_N, SOUND_D3, SOUND_Db3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 8, 0 },
        { KBD_JP106_Y, SOUND_A2, SOUND_Ab2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEW, KEY_IMG_T_BLACK_MAKEB, 5, 0 },
        { KBD_JP106_6, SOUND_Gb2, SOUND_G2,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 4, 0 },
        { KBD_JP106_BACKSLASH, SOUND_H3, SOUND_NA,
          KEY_IMG_T_WHITE, KEY_IMG_T_FULL, KEY_IMG_T_WHITE, 13, 0 },
        { KBD_JP106_H, SOUND_Cb3, SOUND_C3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 7, 0 },
        { KBD_JP106_SEMICOLON, SOUND_Gb3, SOUND_G3,
          KEY_IMG_T_BLACK, KEY_IMG_T_BLACK_MAKEB, KEY_IMG_T_BLACK_MAKEW, 11, 0 }
    }
};

static _UBYTE pronounce_table_[SOUND_MAX_PRONOUNCE] = { SOUND_NA };
static MUSIC_RecordReqId rec_table_[SOUND_MAX_PRONOUNCE] = {
    MUSIC_RECREQID_INVALID
};

static _SINT findPronounce_(_UBYTE freq)
{
    _UBYTE size = _sizeof_array(pronounce_table_);
    _SINT idx;

    if (freq == SOUND_NA) return -1;

    idx = _hash(freq, size);
    while (size--)
    {
        if (pronounce_table_[idx] == freq)
        {
            return idx;
        }
        idx = _next_ring(idx, _sizeof_array(pronounce_table_) - 1);
    }

    return -1;
}

static _SINT setPronounce_(_UBYTE freq)
{
    _UBYTE size = _sizeof_array(pronounce_table_);
    _SINT idx;

    if (freq == SOUND_NA) return -1;

    idx = _hash(freq, size);
    while (size--)
    {
        if (pronounce_table_[idx] == freq)
        {
            break;
        }
        if (pronounce_table_[idx] == SOUND_NA)
        {
            pronounce_table_[idx] = freq;
            return idx;
        }
        idx = _next_ring(idx, _sizeof_array(pronounce_table_) - 1);
    }

    return -1;
}

static KeyParam_* findParam_(_UBYTE bank, _UBYTE key)
{
    _UBYTE size = _sizeof_array(key_table_[bank]);
    _UBYTE idx;

    if (key == KBD_JP106_NA) return NULL;

    idx = _hash(key, size);
    while ((key_table_[bank][idx].freq != SOUND_NA) && size--)
    {
        if (key_table_[bank][idx].key == key)
        {
            return &key_table_[bank][idx];
        }
        idx = _next_ring(idx, _sizeof_array(key_table_[bank]) - 1);
    }

    return NULL;
}

static void execADC_()
{
    _SDWORD adcdata = -1;

    adcdata = ADC_get(ADC_AN0, _FALSE);
    if (adcdata >= 0)
    {
        SOUND_setVolume(adcdata >> 2);
    }

    adcdata = ADC_get(ADC_AN1, _TRUE);
    if (adcdata >= 0)
    {
        SOUND_setEvlpCycle(adcdata);
    }
}

void main(void)
{
    SOUND_Tone tone = { SOUND_NA, &ENVELOPE_piano, &ENVELOPE_piano_reverb,
                        _FALSE };
    KeyParam_* param = NULL;
    _SINT idx = 0;
    _UBYTE bank = 0;
    _UBYTE key = 0;
    _BOOL kbd_break = _FALSE;
    _UBYTE lcd_ch;
    _SINT i, j;
    _BOOL record = _FALSE;

    IOCTL_init();
    LED_INIT;
    LCD_init();
    PS2_init();
    MUSIC_init();
#ifndef NDEBUG
    SCI_init();
#endif /* NDEBUG */
    ADC_init(ADC_SCAN, _FALSE);
    ADC_enable(ADC_AN1);

    LCD_setChar(play_ch_, play_char_);
    LCD_setChar(rec_ch_, rec_char_);

    for (i = 0; i < _sizeof_array(KEY_IMG_char); i++)
    {
        LCD_setChar(i, KEY_IMG_char[i]);
    }
    LCD_write(KEY_IMG_initial_frame, _sizeof_array(KEY_IMG_initial_frame));
    LCD_write(KEY_IMG_initial_frame, _sizeof_array(KEY_IMG_initial_frame));
    LCD_puts(" P");
    LCD_write(KEY_IMG_initial_frame, _sizeof_array(KEY_IMG_initial_frame));
    LCD_write(KEY_IMG_initial_frame, _sizeof_array(KEY_IMG_initial_frame));

    ADC_start();
    SOUND_play();

    while (_TRUE)
    {
        execADC_();

        key = 0;
        if (PS2_read(&key, 1, _FALSE, -1) <= 0) continue;

        _dprintf(("%x", key));

        switch (key)
        {
        case KBD_JP106_BREAK:
            kbd_break = _TRUE;
            continue;

        case KBD_JP106_SPACE:
            if (!kbd_break)
            {
                bank = _next_ring(bank, NUM_OF_BANK_ - 1);
            }
            break;

        case KBD_JP106_ENTER:
            if (!kbd_break)
            {
                if (record)
                {
                    record = _FALSE;
                    MUSIC_stop();
                }
                LCD_setCursor(15, 1);
                LCD_write(&play_ch_, 1);
                MUSIC_play();
            }
            break;

        case KBD_JP106_HENKAN:
            if (!kbd_break && !record)
            {
                record = _TRUE;
                LCD_setCursor(15, 1);
                LCD_write(&rec_ch_, 1);
                MUSIC_record();
                SOUND_play();
            }
            break;

        case KBD_JP106_MUHENKAN:
            if (!kbd_break)
            {
                record = _FALSE;
                LCD_setCursor(15, 1);
                LCD_puts(" ");
                MUSIC_stop();
                SOUND_play();
            }
            break;

        case KBD_JP106_F1:
            if (!kbd_break)
            {
                tone.evlp = &ENVELOPE_piano;
                tone.reverb = &ENVELOPE_piano_reverb;
                tone.loop = _FALSE;
                LCD_setCursor(15, 0);
                LCD_puts("P");
            }
            break;

        case KBD_JP106_F2:
            if (!kbd_break)
            {
                tone.evlp = &ENVELOPE_flute;
                tone.reverb = &ENVELOPE_flute_reverb;
                tone.loop = _TRUE;
                LCD_setCursor(15, 0);
                LCD_puts("F");
            }
            break;

        case KBD_JP106_F3:
            if (!kbd_break)
            {
                tone.evlp = &ENVELOPE_drum;
                tone.reverb = NULL;
                tone.loop = _FALSE;
                LCD_setCursor(15, 0);
                LCD_puts("D");
            }
            break;

        case KBD_JP106_F4:
            if (!kbd_break)
            {
                tone.evlp = &ENVELOPE_trumpet;
                tone.reverb = &ENVELOPE_trumpet_reverb;
                tone.loop = _TRUE;
                LCD_setCursor(15, 0);
                LCD_puts("T");
            }
            break;

        case KBD_JP106_F5:
            if (!kbd_break)
            {
                tone.evlp = &ENVELOPE_harp;
                tone.reverb = &ENVELOPE_harp_reverb;
                tone.loop = _FALSE;
                LCD_setCursor(15, 0);
                LCD_puts("H");
            }
            break;

        case KBD_JP106_NA:
            break;

        default:
            param = findParam_(bank, key);
            if (param == NULL) break;

            idx = findPronounce_(param->freq);
            if (!kbd_break)
            {
                if (idx >= 0) break;

                idx = setPronounce_(param->freq);
                if (idx < 0) break;

                tone.freq = param->freq;
                if (record)
                {
                    rec_table_[idx] = MUSIC_recStart(&tone);
                    if (rec_table_[idx] == MUSIC_RECREQID_INVALID)
                    {
                        record = _FALSE;
                        LCD_setCursor(15, 1);
                        LCD_puts(" ");
                        MUSIC_stop();
                        SOUND_play();
                    }
                }
                SOUND_setTone(idx, &tone);

                LCD_setCursor(param->lcd_x, param->lcd_y);
                if (findPronounce_(param->freq_other) >= 0)
                {
                    lcd_ch = KEY_IMG_T_FULL;
                }
                else
                {
                    lcd_ch = param->make_ch;
                }
                LCD_write(&lcd_ch, 1);

                _dprintf(("(SET:%d)(M)\r\n", idx));
            }
            else
            {
                if (idx < 0) break;

                if (record)
                {
                    MUSIC_recStop(rec_table_[idx]);
                    rec_table_[idx] = MUSIC_RECREQID_INVALID;
                }
                SOUND_removeTone(idx);
                pronounce_table_[idx] = SOUND_NA;

                LCD_setCursor(param->lcd_x, param->lcd_y);
                if (findPronounce_(param->freq_other) >= 0)
                {
                    lcd_ch = param->make_other_ch;
                }
                else
                {
                    lcd_ch = param->break_ch;
                }
                LCD_write(&lcd_ch, 1);

                _dprintf(("(RMV:%d)(B)\r\n", idx));
            }
            break;
        }

        kbd_break = _FALSE;
    }
}

#ifdef __cplusplus
void abort(void)
{
	
}
#endif
