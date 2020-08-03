/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "planck.h"
#include "action_layer.h"
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _SYMBOLS,
  _MOVEMENT,
  _NUMPAD,
  _BACKLIGHT,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBOLS,
  MOVEMENT,
  NUMPAD,
  BACKLIGHT,
};

enum macros {
  BKSP_DEL = 12,
  EMAIL = 13,
  SHAWMAIL = 14,
};

// Macro Definitions
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case BKSP_DEL: {
      uint8_t kc = KC_BSPC;
			if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
		    kc = KC_DEL;
			}
		  if (record->event.pressed) {
		    register_code(kc);
        return false;
      } else {
		    unregister_code(kc);
        return false;
      }
		}
    case EMAIL: {
        if (record->event.pressed) {
            SEND_STRING("josephjamesframpton@gmail.com");
            return false;
        }
    }
    case SHAWMAIL: {
        if (record->event.pressed) {
            SEND_STRING("joseph.frampton@sjrb.ca");
            return false;
        }
    }
  }
  return MACRO_NONE;
};

/* CUSTOM KEY DEFINITIONS */

/* Custom mod layers: */
#define KC_M1 MO(_SYMBOLS)
#define KC_M2 MO(_MOVEMENT)
#define KC_M3 MO(_NUMPAD)
#define KC_M4 LCTL(KC_B)
#define KC_M5 MO(_BACKLIGHT)
/* Mod layer shifters */
#define KC_SFTD KC_SPC
#define KC_SFTU KC_SPC

#define KC_CLPR LSFT(KC_9)
#define KC_CRPR LSFT(KC_0)
#define KC_CLCB LSFT(KC_LBRC)
#define KC_CRCB LSFT(KC_RBRC)
#define KC_CLSQ KC_LBRC
#define KC_CRSQ KC_RBRC
#define KC_CLAB LSFT(KC_COMM)
#define KC_CRAB LSFT(KC_DOT)

#define KC_UNSC LSFT(KC_MINS)
#define KC_TILD LSFT(KC_GRV)

/* back lighting */
#define KC_CTOG BL_TOGG
#define KC_CINC BL_INC
#define KC_CDEC BL_DEC
#define KC_CSTE BL_STEP
#define KC_CBRT BL_BRTG

/* layer on hold, space on tap */
#define KC_M2SP LT(KC_M2, KC_SPC)
/* layer on hold, underscore on tap  --  this does not work, the dash is registered but not the shift mod  */
#define KC_M1US LT(KC_M1, KC_UNSC)
/* macros */
#define KC_BKSP_DEL M(BKSP_DEL)
#define KC_EMAIL M(EMAIL)
#define KC_SHAWMAIL M(SHAWMAIL)

#undef TAPPING_TERM
#define TAPPING_TERM 200

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT_planck_grid(
// .-----------------------------------------------------------------------------------------------------------.
    KC_TAB  , KC_Q   , KC_W   , KC_E   ,  KC_R  , KC_T   , KC_Y   ,  KC_U  , KC_I   , KC_O   , KC_P   , KC_BKSP_DEL,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    KC_ESC  , KC_A   , KC_S   , KC_D   ,  KC_F  , KC_G   , KC_H   ,  KC_J  , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    KC_LSFT , KC_Z   , KC_X   , KC_C   ,  KC_V  , KC_B   , KC_N   ,  KC_M  , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    KC_LCTL , KC_LALT, KC_LGUI, KC_M2  ,  KC_M3 , KC_M1  , KC_M2SP,  KC_M4 , KC_M5  , KC_SFTD, KC_SFTU, KC_ENT
// '-----------------------------------------------------------------------------------------------------------'
 ),
 [_SYMBOLS] = LAYOUT_planck_grid(
// .-----------------------------------------------------------------------------------------------------------.
     KC_F1  , KC_F2  , KC_F3  , KC_F4  ,  KC_F5 ,  KC_F6 , KC_AMPR, KC_ASTR, KC_CLPR, KC_CRPR, KC_MINS, KC_EQL ,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_TILD, KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_EXLM, KC_AT  , KC_CLCB, KC_CRCB, KC_SCLN, KC_BSLS,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_F7  , KC_X   ,  KC_C  , MU_TOG , MU_MOD , KC_HASH, KC_DLR , KC_CLSQ, KC_CRSQ, KC_SLSH, KC_RSFT,
// |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_LALT, KC_LGUI,  KC_M2 ,  KC_M3 ,  KC_M1 , KC_PERC, KC_CIRC, KC_CLAB, KC_CRAB, KC_SFTU, KC_ENT
// .-----------------------------------------------------------------------------------------------------------.
// MU = music
// LCTRL = record (when in music mode)
// LALT = stop (when in music mode)
 ),
[_MOVEMENT] = LAYOUT_planck_grid(
//,----+----+----+----+----+----.    ,----+----+----+----+----+----.
   KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  ,      KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,KC_EQL ,
//|----+----+----+----+----+----|    |----+----+----+----+----+----|
  KC_TILD,KC_BTN1,KC_MS_L,KC_MS_U,KC_MS_D,KC_MS_R,     KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,KC_SCLN,KC_BSLS,
//|----+----+----+----+----+----|    |----+----+----+----+----+----|
  KC_LSFT,KC_BTN2,KC_WH_L,KC_WH_U,KC_WH_D,KC_WH_R,     KC_HOME,KC_PGDN,KC_PGUP,KC_END ,KC_SLSH,KC_RSFT,
//|----+----+----+----+----+----|    |----+----+----+----+----+----|
  KC_LCTL,KC_LALT,KC_LGUI, KC_M2 , KC_M3 , KC_M1 ,     KC_M2SP, KC_M4 , KC_M5 ,KC_SFTD,KC_SFTU,KC_ENT
//`----+----+----+----+----+----'    `----+----+----+----+----+----'
),

 [_NUMPAD] = LAYOUT_planck_grid(
 //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
    KC_TILD, KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,     KC_PSLS, KC_7  , KC_8  , KC_9  ,KC_MINS,KC_EQL ,
 //|----+----+----+----+----+----|    |----+----+----+----+----+----|
    KC_ESC , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,     KC_PAST, KC_4  , KC_5  , KC_6  ,KC_PPLS,KC_BSLS,
 //|----+----+----+----+----+----|    |----+----+----+----+----+----|
    KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,     KC_EQL , KC_1  , KC_2  , KC_3  ,KC_EQL ,KC_BSLS,
 //|----+----+----+----+----+----|    |----+----+----+----+----+----|
    KC_LCTL,KC_LALT,KC_LGUI, KC_M2 , KC_M3 , KC_M1 ,     KC_0   , KC_0  ,KC_COMM,KC_DOT ,KC_ENT ,KC_ENT
 //`----+----+----+----+----+----'    `----+----+----+----+----+----'
 ),

 [_BACKLIGHT] = LAYOUT_planck_grid(
 //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
    KC_CTOG,KC_CINC,KC_CDEC, KC_E  , KC_R  , KC_T  ,     KC_Y   ,KC_Y   ,KC_Y   , KC_O  , KC_P  ,KC_BSPC,
 //|----+----+----+----+----+----|    |----+----+----+----+----+----|
    KC_GRV , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,     KC_Y ,KC_EMAIL,KC_SHAWMAIL,KC_L,KC_SCLN,KC_QUOT,
 //|----+----+----+----+----+----|    |----+----+----+----+----+----|
    KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,      KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,
 //|----+----+----+----+----+----|    |----+----+----+----+----+----|
    KC_LCTL,KC_LALT,KC_LGUI, KC_M2 , KC_M3 , KC_M1 ,     KC_SPC , KC_M4 , KC_M5 ,KC_SFTD,KC_SFTU,KC_ENT
 //`----+----+----+----+----+----'    `----+----+----+----+----+----'
 )
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

// uint32_t layer_state_set_user(uint32_t state) {
//   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SYMBOLS:
      if (record->event.pressed) {
        layer_on(_SYMBOLS);
      } else {
        layer_off(_SYMBOLS);
      }
      return false;
      break;
    case MOVEMENT:
      if (record->event.pressed) {
        layer_on(_MOVEMENT);
      } else {
        layer_off(_MOVEMENT);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        layer_on(_NUMPAD);
      } else {
        layer_off(_NUMPAD);
      }
      return false;
      break;
    case BACKLIGHT:
      if (record->event.pressed) {
        layer_on(_BACKLIGHT);
      } else {
        layer_off(_BACKLIGHT);
      }
      return false;
      break;
  }
  return true;
}


bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

// void encoder_update(bool clockwise) {
//   if (muse_mode) {
//     if (IS_LAYER_ON(_RAISE)) {
//       if (clockwise) {
//         muse_offset++;
//       } else {
//         muse_offset--;
//       }
//     } else {
//       if (clockwise) {
//         muse_tempo+=1;
//       } else {
//         muse_tempo-=1;
//       }
//     }
//   } else {
//     if (clockwise) {
//       register_code(KC_PGDN);
//       unregister_code(KC_PGDN);
//     } else {
//       register_code(KC_PGUP);
//       unregister_code(KC_PGUP);
//     }
//   }
// }

// void dip_update(uint8_t index, bool active) {
//   switch (index) {
//     case 0:
//       if (active) {
//         #ifdef AUDIO_ENABLE
//           PLAY_SONG(plover_song);
//         #endif
//         layer_on(_ADJUST);
//       } else {
//         #ifdef AUDIO_ENABLE
//           PLAY_SONG(plover_gb_song);
//         #endif
//         layer_off(_ADJUST);
//       }
//       break;
//     case 1:
//       if (active) {
//         muse_mode = true;
//       } else {
//         muse_mode = false;
//         #ifdef AUDIO_ENABLE
//           stop_all_notes();
//         #endif
//       }
//    }
// }

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

// bool music_mask_user(uint16_t keycode) {
//   switch (keycode) {
//     case RAISE:
//     case LOWER:
//       return false;
//     default:
//       return true;
//   }
// }
