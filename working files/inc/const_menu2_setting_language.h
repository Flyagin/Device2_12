#ifndef __CONST_SETTING_LANGUAGE_MENU2__
#define __CONST_SETTING_LANGUAGE_MENU2__

#define LANGUAGE_ABSENT         -1
#define LANGUAGE_NONE           0
#define LANGUAGE_RU             1
#define LANGUAGE_UA             2
#define LANGUAGE_EN             3
#define LANGUAGE_KZ             4

enum __index_language_m2
{
  INDEX_LANGUAGE_RU = 0,
  INDEX_LANGUAGE_UA,
  INDEX_LANGUAGE_EN,
  INDEX_LANGUAGE_KZ,
  
  MAX_NAMBER_LANGUAGE
};

#define MAX_ROW_FOR_VIEW_SETTING_LANGUAGE             1

//const uint8_t name_string_language[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_SETTING_LANGUAGE][MAX_COL_LCD + 1] = 
//{
//  "      ����      ",
//  "      ����      ",
//  "    Language    ",
//  "      ����      "
//};
//
//uint8_t information_language[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
//{
//  "    �������     ",
//  "   ���������   ",
//  "    English     ",
//  "     �����      "
//};
//const unsigned int cursor_x_language[MAX_NAMBER_LANGUAGE] = {3, 2, 3, 4};

#endif

//extern const uint8_t name_string_language[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_SETTING_LANGUAGE][MAX_COL_LCD + 1];
//extern uint8_t information_language[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1];
//extern const unsigned int cursor_x_language[MAX_NAMBER_LANGUAGE];


