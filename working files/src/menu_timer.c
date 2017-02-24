#include "header.h"

/*****************************************************/
//������� ����� ����������� ���� ����������� ���� ������������� �������
/*****************************************************/
void make_ekran_control_timer(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_CTRL_TIMER_M2][MAX_COL_LCD + 1] = 
  {
    {
      "      ���       "
    },
    {
      "      ���       "
    },
    {
      "      Type      "
    },
    {
      "      ���       "
    }
  };
  int index_language;
  if (current_state_menu2.edition == ED_VIEWING) index_language = index_language_in_array(settings_fix_prt.language);
  else if (
           (current_state_menu2.edition == ED_EDITION) ||
           (current_state_menu2.edition == ED_CONFIRM_CHANGES)
          )  
  {
    index_language = index_language_in_array(settings_fix_edit.language);
  }
  else
  {
    index_language = index_language_in_array(settings_fix.language);
  }
  
  unsigned int position_temp = current_state_menu2.index_position;
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  uint32_t *p_control;
  if (current_state_menu2.edition == ED_VIEWING) p_control = &((((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->settings.control);
  else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_control = &((((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->control);
  else p_control = &((((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->control);
  
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
    if (index_in_ekran_tmp < MAX_ROW_CTRL_TIMER_M2)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
      }
      else
      {
        //� ������� ����� ����� �������� ��������
        if (index_in_ekran_tmp == INDEX_CTRL_TIMER_M2_TYPE)  
        {
          const uint8_t information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
          {
            {"    �������     ", "    ��������    "},
            {"    �������     ", "    ��������    "},
            {"    IMPULSE     ", "     DELAY      "},
            {"    �������     ", "    ��������    "},
          };
          const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
          {
            {3, 3},
            {3, 3},
            {3, 4},
            {3, 3}
          };
          
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][((*p_control) >> index_in_ekran_tmp) & 0x1][j];
          current_state_menu2.position_cursor_x = cursor_x[index_language][((*p_control) >> index_in_ekran_tmp) & 0x1];
        }
      }
    }
    else
      for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_in_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_state_menu2.position_cursor_y = ((position_temp << 1) + 1) & (MAX_ROW_LCD - 1);
  //������ �������
  current_state_menu2.cursor_on = 1;
  //������ �� ����
  if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
  else current_state_menu2.cursor_blinking_on = 1;
  //�������� �������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ���� ����������� ����������� �������������������� �������
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_control_timer(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_EDITION:
    {
      //����������, �� ���� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      uint32_t *p_control_edit = &((((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->control);
      uint32_t *p_control_cont = &((((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->control);
      if (*p_control_cont != *p_control_edit) 
      {
        if (((*p_control_edit) & ((uint32_t)(~MASKA_CTRL_TIMER_M2))) == 0)
        {
          *p_control_cont = *p_control_edit;
          config_settings_modified |= MASKA_CHANGED_SETTINGS;
          result = RPEDE_DATA_CHANGED_OK;
        }
        else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ���� ����������� �������������������� �������
*/
/*****************************************************/
void press_esc_in_control_timer(void)
{
  uint32_t *p_control_edit = &((((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->control);
  uint32_t *p_control_cont = &((((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->control);
  *p_control_edit = *p_control_cont;
}
/*****************************************************/

/*****************************************************/
//���� ����������� ������ ���������� ��� ��-�������
/*****************************************************
������ ���������
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

������ ���������
  ����
*****************************************************/
void change_control_timer(unsigned int action)
{
  //������� ����� � �������� ����
  uint32_t *p_control_edit = &((((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->control);
  if (
      ((action & (1 << BIT_KEY_LEFT )) != 0) ||
      ((action & (1 << BIT_KEY_RIGHT)) != 0)
     )   
  {
    *p_control_edit ^= (uint32_t)(1 << current_state_menu2.index_position);
  }
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ������� ���������� ��� �������������������� �������
/*****************************************************/
void make_ekran_delay_timer(void)
{
  if (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
  {
    const unsigned char information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " ���.�� ��������",
      " ���.�� �������",
      "  Out of Limits ",
      "���.�� �������� "
    };
    make_ekran_about_info(true, information_about_error);
  }
  else
  {
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_DELAY_TIMER_M2][MAX_COL_LCD + 1] = 
    {
      {
        "  ������ �����  ",
        " ������ ������  "
      },
      {
        "  ������ �����  ",
        " ������ ������  "
      },
      {
        "  Pause Timer   ",
        " Operation Timer"
      },
      {
        "  ������ �����  ",
        " ������ ������  "
      }
    };
    
    int index_language;
    if (current_state_menu2.edition == ED_VIEWING) index_language = index_language_in_array(settings_fix_prt.language);
    else if (
             (current_state_menu2.edition == ED_EDITION) ||
             (current_state_menu2.edition == ED_CONFIRM_CHANGES)
            )  
    {
      index_language = index_language_in_array(settings_fix_edit.language);
    }
    else
    {
      index_language = index_language_in_array(settings_fix.language);
    }
  
    unsigned int position_temp = current_state_menu2.index_position;
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    unsigned int first_symbol;
    uint32_t vaga, value;
  
    __settings_for_TIMER *p_settings_for_timer;
    if (current_state_menu2.edition == ED_VIEWING) p_settings_for_timer = &((((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->settings);
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_settings_for_timer = (((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node);
    else p_settings_for_timer = (((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node);
    size_t col_begin, col_end, col_comma;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_ROW_DELAY_TIMER_M2)
      {
        if ((i & 0x1) == 0)
        {
          //� ��������� ����� ����� �������� ���������
          for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
          first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������

          switch (index_in_ekran_tmp)
          {
          case INDEX_DELAY_TIMER_M2_PAUSE:
            {
              vaga = 100000; //������������ ������� ����������
              col_begin = COL_DELAY_TIMER_PAUSE_BEGIN;
              col_end = COL_DELAY_TIMER_PAUSE_END;
              col_comma = COL_DELAY_TIMER_PAUSE_COMMA;
            
              value = p_settings_for_timer->delay.delay_pause;
            
              break;
            }
          case INDEX_DELAY_TIMER_M2_WORK:
            {
              vaga = 100000; //������������ ������� ����������
              col_begin = COL_DELAY_TIMER_WORK_BEGIN;
              col_end = COL_DELAY_TIMER_WORK_END;
              col_comma = COL_DELAY_TIMER_WORK_COMMA;
            
              value = p_settings_for_timer->delay.delay_work;
            
              break;
            }
          }
        }
        else
        {
          //� ������� ����� ����� �������� ��������
          for (size_t j = 0; j < MAX_COL_LCD; j++)
          {
            if (
                ((j < col_begin) ||  (j > col_end )) &&
                (j != (col_end + 2))
               )working_ekran[i][j] = ' ';
            else if (j == col_comma )working_ekran[i][j] = ',';
            else if (j == (col_end + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, col_comma, 0);
          }
        }
        
      }
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_state_menu2.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
    if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
    {
      int last_position_cursor_x = MAX_COL_LCD;
      switch (current_state_menu2.index_position)
      {
      case INDEX_DELAY_TIMER_M2_PAUSE:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_TIMER_PAUSE_BEGIN;
          last_position_cursor_x = COL_DELAY_TIMER_PAUSE_END;
          break;
        }
      case INDEX_DELAY_TIMER_M2_WORK:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_TIMER_WORK_BEGIN;
          last_position_cursor_x = COL_DELAY_TIMER_WORK_END;
          break;
        }
      }

      //ϳ������� ������ �� ������� �������
      while (
             ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x + 1]) == ' ') && 
             (current_state_menu2.position_cursor_x < (last_position_cursor_x -1))
             )
      {
        current_state_menu2.position_cursor_x++;
      }

      //������ ������� ���, ��� �� ��� ����� ������
      if (
          ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x]) != ' ') && 
          (current_state_menu2.position_cursor_x > 0)
         )
      {
        current_state_menu2.position_cursor_x--;
      }
    }
    //������ �������
    current_state_menu2.cursor_on = 1;
    //������ �� ����
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }
  //�������� �������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ���� ����������� �������� �������������������� �������
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_delay_timer(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      switch (current_state_menu2.index_position)
      {
      case INDEX_DELAY_TIMER_M2_PAUSE:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_TIMER_PAUSE_BEGIN;
          break;
        }
      case INDEX_DELAY_TIMER_M2_WORK:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_TIMER_WORK_BEGIN;
          break;
        }
      }
      break;
    }
  case ED_EDITION:
    {
      //����������, �� ���� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      __settings_for_TIMER *p_settings_for_timer_edit = (((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node);
      __settings_for_TIMER *p_settings_for_timer_cont = (((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node);
      switch (current_state_menu2.index_position)
      {
      case INDEX_DELAY_TIMER_M2_PAUSE:
        {
          if (p_settings_for_timer_cont->delay.delay_pause != p_settings_for_timer_edit->delay.delay_pause) 
          {
            if (check_data_setpoint(p_settings_for_timer_edit->delay.delay_pause, TIMEOUT_DF_PAUSE_MIN, TIMEOUT_DF_PAUSE_MAX) == 1)
            {
              p_settings_for_timer_cont->delay.delay_pause = p_settings_for_timer_edit->delay.delay_pause;
              config_settings_modified |= MASKA_CHANGED_SETTINGS;
              result = RPEDE_DATA_CHANGED_OK;
            }
            else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
          }

          break;
        }
      case INDEX_DELAY_TIMER_M2_WORK:
        {
          if (p_settings_for_timer_cont->delay.delay_work != p_settings_for_timer_edit->delay.delay_work) 
          {
            if (check_data_setpoint(p_settings_for_timer_edit->delay.delay_work, TIMEOUT_DF_WORK_MIN, TIMEOUT_DF_WORK_MAX) == 1)
            {
              p_settings_for_timer_cont->delay.delay_work = p_settings_for_timer_edit->delay.delay_work;
              config_settings_modified |= MASKA_CHANGED_SETTINGS;
              result = RPEDE_DATA_CHANGED_OK;
            }
            else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
          }

          break;
        }
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ���� �������� �������������������� �������
*/
/*****************************************************/
void press_esc_in_delay_timer(void)
{
  __settings_for_TIMER *p_settings_for_timer_edit = (((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node);
  __settings_for_TIMER *p_settings_for_timer_cont = (((__settings_for_TIMER*)sca_of_p[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node);
  switch (current_state_menu2.index_position)
  {
  case INDEX_DELAY_TIMER_M2_PAUSE:
    {
      p_settings_for_timer_edit->delay.delay_pause = p_settings_for_timer_cont->delay.delay_pause;
      break;
    }
  case INDEX_DELAY_TIMER_M2_WORK:
    {
      p_settings_for_timer_edit->delay.delay_work = p_settings_for_timer_cont->delay.delay_work;
      break;
    }
  }
}
/*****************************************************/

/*****************************************************/
//���� ������������
/*****************************************************
������ ���������
(1 << BIT_KEY_DOWN) - �������� ������ ����
(1 << BIT_KEY_UP)   - �������� ������ �����
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

������ ���������
  ����
*****************************************************/
void change_delay_timer(unsigned int action)
{
  //������� ����� � �������� ����
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    int32_t *p_value = NULL;
    unsigned int col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case INDEX_DELAY_TIMER_M2_PAUSE:
      {
        p_value = &((((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->delay.delay_pause);
        col_end = COL_DELAY_TIMER_PAUSE_END;
        col_comma = COL_DELAY_TIMER_PAUSE_COMMA;
        break;
      }
    case INDEX_DELAY_TIMER_M2_WORK:
      {
        p_value = &((((__settings_for_TIMER*)sca_of_p_edit[ID_FB_TIMER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_logical_node)->delay.delay_work);
        col_end = COL_DELAY_TIMER_WORK_END;
        col_comma = COL_DELAY_TIMER_WORK_COMMA;
        break;
      }
    }
    
    if (p_value != NULL)
    {
      *p_value = edit_setpoint(((action & (1 << BIT_KEY_UP)) != 0), *p_value, 1, col_comma, col_end, 10);
    }
  }
  else if (
           ((action & (1 << BIT_KEY_LEFT )) != 0) ||
           ((action & (1 << BIT_KEY_RIGHT)) != 0)
          )   
  {
    int col_begin, col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case INDEX_DELAY_TIMER_M2_PAUSE:
      {
        col_begin = COL_DELAY_TIMER_PAUSE_BEGIN;
        col_end = COL_DELAY_TIMER_PAUSE_END;
        col_comma = COL_DELAY_TIMER_PAUSE_COMMA;
        break;
      }
    case INDEX_DELAY_TIMER_M2_WORK:
      {
        col_begin = COL_DELAY_TIMER_WORK_BEGIN;
        col_end = COL_DELAY_TIMER_WORK_END;
        col_comma = COL_DELAY_TIMER_WORK_COMMA;
        break;
      }
    }
    
    if (action & (1 << BIT_KEY_LEFT ))
    {
      current_state_menu2.position_cursor_x--;
      if (current_state_menu2.position_cursor_x == col_comma )current_state_menu2.position_cursor_x--;
      if ((current_state_menu2.position_cursor_x < col_begin) ||
          (current_state_menu2.position_cursor_x > col_end))
        current_state_menu2.position_cursor_x = col_end;
    }
    else
    {
      current_state_menu2.position_cursor_x++;
      if (current_state_menu2.position_cursor_x == col_comma )current_state_menu2.position_cursor_x++;
      if ((current_state_menu2.position_cursor_x < col_begin) ||
          (current_state_menu2.position_cursor_x > col_end))
        current_state_menu2.position_cursor_x = col_begin;
    }
    
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/