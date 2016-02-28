/**
 * @file synthesizer.h
 *
 * @brief シンセサイザー
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
 * @mainpage はじめに
 *
 * @section abstract この文書について
 * この文書は、シンセサイザーの内部構造を記述した詳細設計仕様書である。@n
 * 文書は大きくデータ構造の解説セクションと、ファイルモジュール別の
 * インタフェース解説セクションに分かれており、それぞれのセクションは
 * 冒頭で解説項目を概略説明付きで列挙した後、項目の詳細説明が続くという
 * 構成になっている。
 *
 * @section target 対象
 * シンセサイザーの解析者を対象とした文書であり、システムの基本仕様と
 * H8-BASE2のプラットフォームを理解していることが前提である。@n
 * また、このアプリケーションはH8SDKを使用して設計されている。
 *
 * @see H8SDK詳細設計仕様書
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

/** キーボードバンクの数 */
#define NUM_OF_BANK_ 2
/** バンク当たりの鍵盤数。2オクターブ分 */
#define KEY_OF_BANK_ 29

/**
 * @brief 鍵盤パラメータ型
 */
typedef struct
{
    _UBYTE key;
    /**< PS/2キーコード */
    _UBYTE freq;
    /**< 音階 */
    _UBYTE freq_other;
    /**< freqに対する半音上の音階 */
    KEY_IMG_Type break_ch;
    /**< 鍵盤を離しているときのLCD文字コード */
    KEY_IMG_Type make_ch;
    /**< 鍵盤を押しているときのLCD文字コード */
    KEY_IMG_Type make_other_ch;
    /**< freq_otherの鍵盤を押しているときのLCD文字コード */
    _SINT lcd_x;
    /**< 鍵盤キャラクタのLCD表示位置。横 */
    _SINT lcd_y;
    /**< 鍵盤キャラクタのLCD表示位置。縦 */
} KeyParam_;

/**
 * @brief 静的キーパラメータテーブル
 *
 * 内部はあらかじめKeyParam_::keyをキーとしたハッシュ値を配列のインデッ
 * クスとした配置で固定されている。これは48個(4オクターブ分)のキー検索
 * の時間を常に単位時間で終わらせるためである。1バンクの配列サイズが2
 * オクターブ分の24ではなく29になっているのは、配列サイズを素数にする
 * ことでハッシュ値の重複を最小値にするためである。
 */
static const KeyParam_ key_table_[NUM_OF_BANK_][KEY_OF_BANK_];

/**
 * @brief 発音テーブル
 *
 * 現在再生中の音階データが登録される。
 */
static _UBYTE pronounce_table_[SOUND_MAX_PRONOUNCE];

/**
 * @brief 録音テーブル
 *
 * 現在録音中のリクエストIDが登録される。
 *
 * @see music.h
 */
static MUSIC_RecordReqId rec_table_[SOUND_MAX_PRONOUNCE];

/** 再生中のLCD文字データ */
static const _UBYTE play_char_[LCD_CG_ROWS];
/** 再生中のLCD文字コード */
static const _UBYTE play_ch_;
/** 録音中のLCD文字データ */
static const _UBYTE rec_char_[LCD_CG_ROWS];
/** 録音中のLCD文字コード */
static const _UBYTE rec_ch_;

/**
 * @brief 現在再生中の音を検索
 *
 * @param[in] freq 検索する音の音階
 *
 * @retval 0以上 pronounce_table_のインデックス
 * @retval 0未満 指定の音階は再生されていない
 */
static _SINT findPronounce_(_UBYTE freq);

/**
 * @brief 再生中として音を登録
 *
 * @param[in] freq 登録する音の音階
 *
 * @retval 0以上 pronounce_table_のインデックス
 * @retval 0未満 テーブルサイズオーバー
 */
static _SINT setPronounce_(_UBYTE freq);

/**
 * @brief キーパラメータを検索
 *
 * @param[in] bank 検索するキーのバンク
 * @param[in] key 検索するキーコード
 *
 * @return 見つかったキーパラメータへのポインタ
 * @retval NULL 指定のキーは登録されていない
 */
static KeyParam_* findParam_(_UBYTE bank, _UBYTE key);

/**
 * @brief 定期A/Dコンバータ処理
 *
 * ツマミの値を読み、音量とエンベロープレベルの設定を更新する。
 */
static void execADC_();

#ifdef __cplusplus
}
#endif

#endif /* SYNTH_H_ */
