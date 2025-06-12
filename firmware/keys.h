#ifndef KEYS_H
#define KEYS_H

// #include <BleKeyboard.h>

// Special Keys
void key_media_next_track(BleKeyboard &blekeyboard) { blekeyboard.press(KEY_MEDIA_NEXT_TRACK); delay(10); blekeyboard.release(KEY_MEDIA_NEXT_TRACK);}
void key_media_previous_track(BleKeyboard &k) { k.press(KEY_MEDIA_PREVIOUS_TRACK); k.release(KEY_MEDIA_PREVIOUS_TRACK); }
void key_media_stop(BleKeyboard &k) { k.press(KEY_MEDIA_STOP); k.release(KEY_MEDIA_STOP); }
void key_media_play_pause(BleKeyboard &k) { k.press(KEY_MEDIA_PLAY_PAUSE); k.release(KEY_MEDIA_PLAY_PAUSE); }
void key_media_mute(BleKeyboard &k) { k.press(KEY_MEDIA_MUTE); k.release(KEY_MEDIA_MUTE); }
void key_media_volume_up(BleKeyboard &k) { k.press(KEY_MEDIA_VOLUME_UP); k.release(KEY_MEDIA_VOLUME_UP); }
void key_media_volume_down(BleKeyboard &k) { k.press(KEY_MEDIA_VOLUME_DOWN); k.release(KEY_MEDIA_VOLUME_DOWN); }
void key_media_www_home(BleKeyboard &k) { k.press(KEY_MEDIA_WWW_HOME); k.release(KEY_MEDIA_WWW_HOME); }
void key_media_local_machine_browser(BleKeyboard &k) { k.press(KEY_MEDIA_LOCAL_MACHINE_BROWSER); k.release(KEY_MEDIA_LOCAL_MACHINE_BROWSER); }
void key_media_calculator(BleKeyboard &k) { k.press(KEY_MEDIA_CALCULATOR); k.release(KEY_MEDIA_CALCULATOR); }
void key_media_www_bookmarks(BleKeyboard &k) { k.press(KEY_MEDIA_WWW_BOOKMARKS); k.release(KEY_MEDIA_WWW_BOOKMARKS); }
void key_media_www_search(BleKeyboard &k) { k.press(KEY_MEDIA_WWW_SEARCH); k.release(KEY_MEDIA_WWW_SEARCH); }
void key_media_www_stop(BleKeyboard &k) { k.press(KEY_MEDIA_WWW_STOP); k.release(KEY_MEDIA_WWW_STOP); }
void key_media_www_back(BleKeyboard &k) { k.press(KEY_MEDIA_WWW_BACK); k.release(KEY_MEDIA_WWW_BACK); }
void key_media_consumer_control_configuration(BleKeyboard &k) { k.press(KEY_MEDIA_CONSUMER_CONTROL_CONFIGURATION); k.release(KEY_MEDIA_CONSUMER_CONTROL_CONFIGURATION); }
void key_media_email_reader(BleKeyboard &k) { k.press(KEY_MEDIA_EMAIL_READER); k.release(KEY_MEDIA_EMAIL_READER); }

// Numeric 0-9
void key_0(BleKeyboard &k) { k.press('0'); k.release('0'); }
void key_1(BleKeyboard &k) { k.press('1'); k.release('1'); }
void key_2(BleKeyboard &k) { k.press('2'); k.release('2'); }
void key_3(BleKeyboard &k) { k.press('3'); k.release('3'); }
void key_4(BleKeyboard &k) { k.press('4'); k.release('4'); }
void key_5(BleKeyboard &k) { k.press('5'); k.release('5'); }
void key_6(BleKeyboard &k) { k.press('6'); k.release('6'); }
void key_7(BleKeyboard &k) { k.press('7'); k.release('7'); }
void key_8(BleKeyboard &k) { k.press('8'); k.release('8'); }
void key_9(BleKeyboard &k) { k.press('9'); k.release('9'); }

// Alphabet a-z (lowercase)
void key_a(BleKeyboard &k) { k.press('a'); k.release('a'); }
void key_b(BleKeyboard &k) { k.press('b'); k.release('b'); }
void key_c(BleKeyboard &k) { k.press('c'); k.release('c'); }
void key_d(BleKeyboard &k) { k.press('d'); k.release('d'); }
void key_e(BleKeyboard &k) { k.press('e'); k.release('e'); }
void key_f(BleKeyboard &k) { k.press('f'); k.release('f'); }
void key_g(BleKeyboard &k) { k.press('g'); k.release('g'); }
void key_h(BleKeyboard &k) { k.press('h'); k.release('h'); }
void key_i(BleKeyboard &k) { k.press('i'); k.release('i'); }
void key_j(BleKeyboard &k) { k.press('j'); k.release('j'); }
void key_k(BleKeyboard &k) { k.press('k'); k.release('k'); }
void key_l(BleKeyboard &k) { k.press('l'); k.release('l'); }
void key_m(BleKeyboard &k) { k.press('m'); k.release('m'); }
void key_n(BleKeyboard &k) { k.press('n'); k.release('n'); }
void key_o(BleKeyboard &k) { k.press('o'); k.release('o'); }
void key_p(BleKeyboard &k) { k.press('p'); k.release('p'); }
void key_q(BleKeyboard &k) { k.press('q'); k.release('q'); }
void key_r(BleKeyboard &k) { k.press('r'); k.release('r'); }
void key_s(BleKeyboard &k) { k.press('s'); k.release('s'); }
void key_t0(BleKeyboard &k) { k.press('t'); k.release('t'); }
void key_u(BleKeyboard &k) { k.press('u'); k.release('u'); }
void key_v(BleKeyboard &k) { k.press('v'); k.release('v'); }
void key_w(BleKeyboard &k) { k.press('w'); k.release('w'); }
void key_x(BleKeyboard &k) { k.press('x'); k.release('x'); }
void key_y(BleKeyboard &k) { k.press('y'); k.release('y'); }
void key_z(BleKeyboard &k) { k.press('z'); k.release('z'); }

// Alphabet A-Z (uppercase)
void key_A(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('a'); k.release('a'); k.release(KEY_LEFT_SHIFT); }
void key_B(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('b'); k.release('b'); k.release(KEY_LEFT_SHIFT); }
void key_C(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('c'); k.release('c'); k.release(KEY_LEFT_SHIFT); }
void key_D(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('d'); k.release('d'); k.release(KEY_LEFT_SHIFT); }
void key_E(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('e'); k.release('e'); k.release(KEY_LEFT_SHIFT); }
void key_F(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('f'); k.release('f'); k.release(KEY_LEFT_SHIFT); }
void key_G(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('g'); k.release('g'); k.release(KEY_LEFT_SHIFT); }
void key_H(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('h'); k.release('h'); k.release(KEY_LEFT_SHIFT); }
void key_I(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('i'); k.release('i'); k.release(KEY_LEFT_SHIFT); }
void key_J(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('j'); k.release('j'); k.release(KEY_LEFT_SHIFT); }
void key_K(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('k'); k.release('k'); k.release(KEY_LEFT_SHIFT); }
void key_L(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('l'); k.release('l'); k.release(KEY_LEFT_SHIFT); }
void key_M(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('m'); k.release('m'); k.release(KEY_LEFT_SHIFT); }
void key_N(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('n'); k.release('n'); k.release(KEY_LEFT_SHIFT); }
void key_O(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('o'); k.release('o'); k.release(KEY_LEFT_SHIFT); }
void key_P(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('p'); k.release('p'); k.release(KEY_LEFT_SHIFT); }
void key_Q(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('q'); k.release('q'); k.release(KEY_LEFT_SHIFT); }
void key_R(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('r'); k.release('r'); k.release(KEY_LEFT_SHIFT); }
void key_S(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('s'); k.release('s'); k.release(KEY_LEFT_SHIFT); }
void key_T(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('t'); k.release('t'); k.release(KEY_LEFT_SHIFT); }
void key_U(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('u'); k.release('u'); k.release(KEY_LEFT_SHIFT); }
void key_V(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('v'); k.release('v'); k.release(KEY_LEFT_SHIFT); }
void key_W(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('w'); k.release('w'); k.release(KEY_LEFT_SHIFT); }
void key_X(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('x'); k.release('x'); k.release(KEY_LEFT_SHIFT); }
void key_Y(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('y'); k.release('y'); k.release(KEY_LEFT_SHIFT); }
void key_Z(BleKeyboard &k) { k.press(KEY_LEFT_SHIFT); k.press('z'); k.release('z'); k.release(KEY_LEFT_SHIFT); }

// Common symbols 
void key_exclamation(BleKeyboard &k) { k.press('!'); k.release('!'); }
void key_at(BleKeyboard &k) { k.press('@'); k.release('@'); }
void key_hash(BleKeyboard &k) { k.press('#'); k.release('#'); }
void key_dollar(BleKeyboard &k) { k.press('$'); k.release('$'); }
void key_percent(BleKeyboard &k) { k.press('%'); k.release('%'); }
void key_caret(BleKeyboard &k) { k.press('^'); k.release('^'); }
void key_ampersand(BleKeyboard &k) { k.press('&'); k.release('&'); }
void key_asterisk(BleKeyboard &k) { k.press('*'); k.release('*'); }
void key_left_paren(BleKeyboard &k) { k.press('('); k.release('('); }
void key_right_paren(BleKeyboard &k) { k.press(')'); k.release(')'); }
void key_minus(BleKeyboard &k) { k.press('-'); k.release('-'); }
void key_underscore(BleKeyboard &k) { k.press('_'); k.release('_'); }
void key_equal(BleKeyboard &k) { k.press('='); k.release('='); }
void key_plus(BleKeyboard &k) { k.press('+'); k.release('+'); }
void key_left_bracket(BleKeyboard &k) { k.press('['); k.release('['); }
void key_right_bracket(BleKeyboard &k) { k.press(']'); k.release(']'); }
void key_left_brace(BleKeyboard &k) { k.press('{'); k.release('{'); }
void key_right_brace(BleKeyboard &k) { k.press('}'); k.release('}'); }
void key_semicolon(BleKeyboard &k) { k.press(';'); k.release(';'); }
void key_colon(BleKeyboard &k) { k.press(':'); k.release(':'); }
void key_quote(BleKeyboard &k) { k.press('\''); k.release('\''); }
void key_double_quote(BleKeyboard &k) { k.press('\"'); k.release('\"'); }
void key_comma(BleKeyboard &k) { k.press(','); k.release(','); }
void key_period(BleKeyboard &k) { k.press('.'); k.release('.'); }
void key_slash(BleKeyboard &k) { k.press('/'); k.release('/'); }
void key_question(BleKeyboard &k) { k.press('?'); k.release('?'); }
void key_backslash(BleKeyboard &k) { k.press('\\'); k.release('\\'); }
void key_pipe(BleKeyboard &k) { k.press('|'); k.release('|'); }

#endif
