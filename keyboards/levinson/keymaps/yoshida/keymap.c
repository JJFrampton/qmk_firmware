#include "levinson.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _SYMBOLS 1
#define _MOVEMENT 2
#define _NUMPAD 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBOLS,
  MOVEMENT,
  NUMPAD,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen

/* Custom mod layers: */
#define KC_M1 SYMBOLS
#define KC_M2 MOVEMENT
#define KC_M3 NUMPAD
#define KC_M4 SPC
#define KC_M5 SPC
/* Mod layer shifters */
#define KC_SFTD
#define KC_SFTU

#define KC_CLPR LSFT(9)
#define KC_CRPR LSFT(0)
#define KC_CLCB LSFT(LBRC)
#define KC_CRCB LSFT(RBRC)
#define KC_CLSQ LBRC
#define KC_CRSQ RBRC
#define KC_CLAB LSFT(COMM)
#define KC_CRAB LSFT(DOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M1 , M2 , M3 ,     SPC , M4 , M5 ,SFTD,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYMBOLS] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
      F1 , F2 , F3 , F4 , F5 , F6 ,     AMPR,ASTR,CLPR,CRPR, P  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      F7 , F8 , F9 ,F10 ,F11 ,F12 ,     EXLM, AT ,CLCB,CRCB,SCLN,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,     HASH,DLR ,CLSQ,CRSQ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M1 , M2 , M3 ,     PERC,CIRC,CLAB,CRAB,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_MOVEMENT] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
      1  , 2  , 3  , 4  , 5  , 6  ,      7  , 8  , 9  , 0  ,MINS,EQL 
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     GRAV,BTN1,MS_L,MS_U,MS_D,MS_R,     RGHT,DOWN, UP ,LEFT,SCLN,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT,BTN2,WH_L,WH_U,WH_D,WH_R,     HOME,PGDN,PGUP,END ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M1 , M2 , M3 ,     SPC , M4 , M5 ,SFTD,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     GRV , Q  , W  , E  , R  , T  ,      Y  , 7  , 8  , 9  ,PMNS,PSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,      H  , 4  , 5  , 6  ,PPLS,PAST,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , 1  , 2  , 3  ,ENT ,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M1 , M2 , M3 ,     SPC , 0  , 0  ,DOT ,ENT ,EQL
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case SYMBOLS:
      if (record->event.pressed) {
        layer_on(_SYMBOLS);
        update_tri_layer(_SYMBOLS, _CODE, _ADJUST);
      } else {
        layer_off(_SYMBOLS);
        update_tri_layer(_SYMBOLS, _CODE, _ADJUST);
      }
      return false;
      break;
    case MOVEMENT:
      if (record->event.pressed) {
        layer_on(_MOVEMENT);
        update_tri_layer(_MOVEMENT, _CODE, _ADJUST);
      } else {
        layer_off(_MOVEMENT);
        update_tri_layer(_MOVEMENT, _CODE, _ADJUST);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        layer_on(_NUMPAD);
        update_tri_layer(_NUMPAD, _CODE, _ADJUST);
      } else {
        layer_off(_NUMPAD);
        update_tri_layer(_NUMPAD, _CODE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
