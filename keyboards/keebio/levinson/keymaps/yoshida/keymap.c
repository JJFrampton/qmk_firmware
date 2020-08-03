#include "levinson.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _SYMBOLS 1
#define _MOVEMENT 2
#define _NUMPAD 3
#define _BACKLIGHT 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBOLS,
  MOVEMENT,
  NUMPAD,
  BACKLIGHT,
};

enum macros {
  BKSP_DEL = 12,
  email = 13,
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
      } else {
		    unregister_code(kc);
      }
		}
  }
  return MACRO_NONE;
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen

/* Custom mod layers: */
#define KC_M1 MO(_SYMBOLS)
#define KC_M2 MO(_MOVEMENT)
#define KC_M3 MO(_NUMPAD)
#define KC_M4 MO(_BACKLIGHT)
#define KC_M5 KC_SPC
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

#define KC_CTOG BL_TOGG
#define KC_CINC BL_INC
#define KC_CDEC BL_DEC
#define KC_CSTE BL_STEP
#define KC_CBRT BL_BRTG

#define KC_M1SP LT(KC_M2, KC_SPC)
#define KC_BKSP_DEL M(BKSP_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,BKSP_DEL,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M2 , M3 , M1 ,     M1SP, M4 , M5 ,SFTD,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYMBOLS] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
      F1 , F2 , F3 , F4 , F5 , F6 ,     AMPR,ASTR,CLPR,CRPR,MINS,EQL ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      F7 , F8 , F9 ,F10 ,F11 ,F12 ,     EXLM, AT ,CLCB,CRCB,SCLN,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,     HASH,DLR ,CLSQ,CRSQ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M2 , M3 , M1 ,     PERC,CIRC,CLAB,CRAB,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_MOVEMENT] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
      1  , 2  , 3  , 4  , 5  , 6  ,      7  , 8  , 9  , 0  ,MINS,EQL ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     GRV ,BTN1,MS_L,MS_U,MS_D,MS_R,     LEFT,DOWN, UP ,RGHT,SCLN,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT,BTN2,WH_L,WH_U,WH_D,WH_R,     HOME,PGDN,PGUP,END ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M2 , M3 , M1 ,     M1SP, M4 , M5 ,SFTD,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     GRV , Q  , W  , E  , R  , T  ,     PSLS, 7  , 8  , 9  ,MINS,EQL ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,     PAST, 4  , 5  , 6  ,PPLS,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,     EQL , 1  , 2  , 3  ,EQL ,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M2 , M3 , M1 ,     UNSC, 0  ,COMM,DOT ,ENT ,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_BACKLIGHT] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,     CTOG,CINC,CDEC, O  , P  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,     CSTE,CBRT, K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M2 , M3 , M1 ,     SPC , M4 , M5 ,SFTD,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  )
};

/* void persistent_default_layer_set(uint16_t default_layer) { */
/*   eeconfig_update_default_layer(default_layer); */
/*   default_layer_set(default_layer); */
/* } */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /* case QWERTY: */
    /*   if (record->event.pressed) { */
    /*     persistent_default_layer_set(1UL<<_QWERTY); */
    /*   } */
    /*   return false; */
    /*   break; */
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
