#include "levinson.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _NUMB 3
#define _CODE 4
#define _SYS 5
#define _FN4 6
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  NUMB,
  CODE,
  SYS,
  FN4,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_X1 CODE
#define KC_X2 NUMB
#define KC_X3 SYS
#define KC_X4 MT(MOD_LSFT, KC_ENT)

/* Custom mod layers: */
#define KC_M1
#define KC_M2
#define KC_M3
#define KC_M4
#define KC_M5
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

  /* [_COLEMAK] = LAYOUT_kc( */
  [_MOVEMENT] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  ,WH_L,WH_U,WH_D,WH_R,     HOME,PGDN,PGUP,END , p  ,DEL
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     BSPC,BTN1,MS_L,MS_U,MS_D,MS_R,     RGHT,DOWN, UP ,LEFT,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT,BTN2, X  , C  , V  , B  ,      K  , M  ,COMM,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M1 , M2 , M3 ,     SPC , M4 , M5 ,SFTD,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_MOVEMENT_2] = LAYOUT_kc(
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

  /* [_DVORAK] = LAYOUT_kc( */
  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     GRV , Q  , W  , E  , R  , T  ,      7  , 8  , 9  ,PMNS,PSLS,EQL
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,      4  , 5  , 6  ,PPLS,PAST,BSLS
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      1  , 2  , 3  ,ENT ,ENT ,RSFT
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M1 , M2 , M3 ,      0  , 0  ,DOT ,ENT ,ENT ,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_NUMPAD_2] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     GRV , Q  , W  , E  , R  , T  ,      Y  , 7  , 8  , 9  ,PMNS,PSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,      H  , 4  , 5  , 6  ,PPLS,PAST,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , 1  , 2  , 3  ,ENT ,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M1 , M2 , M3 ,     SPC , 0  , 0  ,DOT ,ENT ,EQL
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYMBOLS] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,      Y  ,CLPR,CRPR, O  , P  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,      H  ,CLCB,CRCB, L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  ,CLSQ,CRSQ,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M1 , M2 , M3 ,     SPC ,CLAB,CRAB,SFTD,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYMBOLS_2] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     EXLM, AT ,HASH,DLR ,PERC,CIRC,     AMPR,ASTR,CLPR,CRPR, P  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  ,EXLM,AT ,HASH ,      H  , J  ,CLCB,CRCB,SCLN,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,CLSQ,CRSQ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT,LGUI, M1 , M2 , M3 ,     SPC , M4 ,CLAB,CRAB,SFTU,ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYMBOLS_3] = LAYOUT_kc(
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

  [_NUMB] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,PMNS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     GRV , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,UNDS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,MPRV,MPLY,MNXT,    ,         ,VOLD,VOLU,MUTE,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,LALT,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_CODE] = LAYOUT_kc(
  //,----+------+----+----+----+----.    ,----+----+----+----+----+----.
     ESC ,      ,    , UP ,    ,    ,     PGUP,HOME,LPRN,RPRN,BSLS,PIPE,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
     CAPS,SELECT,LEFT,DOWN,RGHT,DEL ,     PGDN, END,LBRC,RBRC,MINS,UNDS,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
         , UNDO ,CUT ,COPY,PASTE,   ,     LEFT,RGHT,LCBR,RCBR,PLUS,PEQL,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
         ,      ,    ,    ,    ,LALT,         ,    ,    ,    ,    ,
  //`----+------+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYS] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|Sat Up|Sat Dn|Val Up|Val Dn|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT_ortho_4x12( \
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  )


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

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
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case NUMB:
      if (record->event.pressed) {
        layer_on(_NUMB);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      } else {
        layer_off(_NUMB);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      }
      return false;
      break;
    case CODE:
      if (record->event.pressed) {
        layer_on(_CODE);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      } else {
        layer_off(_CODE);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
