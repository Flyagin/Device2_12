#ifndef __CONST_MENU_VER2__
#define __CONST_MENU_VER2__

enum _edition_stats
{
  ED_VIEWING = 0,               /* 0 - ���� ����� �� � ����� ����������  */
  ED_CAN_BE_EDITED,             /* 1 - ���� ����� �� � ����� ���������� ��� � ������ �������� � ����� ����������� ��� ������� �������� ������  */
  ED_EDITION,                   /* 2 - ���� ����� � ����� �����������  */
  ED_CONFIRM_CHANGES,           /* 3 - ���� ���� ������������ �����������  */ 
  ED_WARNING_EDITION_BUSY,      /* 4 - � ������ ��������� ��������� �������  ��� ����������� �������� � ����� ����������� (���������� ���� ��� ������� � ������ ������� Enter �������� make_ekran_about_info. �� ������������ Enter ���������� � ���� ������ ����)*/
  ED_WARNING_ENTER_ESC,         /* 5 - � ������ ��������� ��������� �������  (���������� ���� ��� ������� � ����� Enter/Esc �������� �������� make_ekran_about_info. �� ������������ Enter ���������� � ���� ������ ����)*/
  ED_WARNING_ENTER,             /* 6 - � ������ ��������� ��������� �������  (���������� ���� ��� ������� � ������ ������� Enter �������� make_ekran_about_info. �� ������������ Enter ���������� � ���� ������ ����)*/
  ED_INFO,                      /* 7 - � ������ ��������� ��������� ������������ ������������� �� ������ ����� �����������  (���������� ���� ���������� � ������ ������� Enter �������� make_ekran_about_info) �� ������������ Enter ����������� � ��������� ����*/
  ED_ERROR                      /* 8 - � ������ ��������� ��������� �������� �������  (�������� ���������� ��� ����-��� ��������� ��������� ����-��� ������)*/
};

enum _result_pressed_enter_during_edition
{
  RPEDE_NONE = 0,
  RPEDE_DATA_NOT_CHANGED,
  RPEDE_DATA_CHANGED_OK,
  RPEDE_DATA_CHANGED_OUT_OF_RANGE,
  RPEDE_DATA_CHANGED_WRONG_RETURN_OK,
  RPEDE_DATA_CHANGED_WRONG_RETURN_BAD,
};

enum _menu2_levels
{
  MAIN_MANU2_LEVEL = 0,
    TIME_MANU2_LEVEL,
    MEASUREMENT_MENU2_LEVEL,
    INPUTS_OUTPUTS_MENU2_LEVEL,
      INPUTS_MENU2_LEVEL,
      OUTPUTS_MENU2_LEVEL,
    REGISTRATORS_MENU2_LEVEL,
    
    __BEGIN_SETTINGS_MENU2_LEVEL,
    
    LIST_SETTINGS_MENU2_LEVEL = __BEGIN_SETTINGS_MENU2_LEVEL,
      CONFIGURATION_MENU2_LEVEL,
      LIST_SETTINGS_BIOS_MENU2_LEVEL,
        LIST_INPUTS_MENU2_LEVEL,
          LIST_SETTINGS_INPUT_MENU2_LEVEL,
            DELAY_INPUT_MENU2_LEVEL,
            CTRL_INPUT_MENU2_LEVEL,
        LIST_OUTPUTS_MENU2_LEVEL,
          LIST_SETTINGS_OUTPUT_MENU2_LEVEL,
            CTRL_OUTPUT_MENU2_LEVEL,
        LIST_LEDS_MENU2_LEVEL,
          LIST_SETTINGS_LED_MENU2_LEVEL,
            CTRL_LED_MENU2_LEVEL,
      LIST_ALARMS_MENU2_LEVEL,
        LIST_SETTINGS_ALARM_MENU2_LEVEL,
          DELAY_ALARM_MENU2_LEVEL,
          CTRL_ALARM_MENU2_LEVEL,
      LIST_GROUP_ALARMS_MENU2_LEVEL,
        LIST_SETTINGS_GROUP_ALARM_MENU2_LEVEL,
          PICKUP_GROUP_ALARM_MENU2_LEVEL,
          DELAY_GROUP_ALARM_MENU2_LEVEL,
          CTRL_GROUP_ALARM_MENU2_LEVEL,
      LIST_TIMERS_MENU2_LEVEL,
        LIST_SETTINGS_TIMER_MENU2_LEVEL,
          DELAY_TIMER_MENU2_LEVEL,
      LIST_MEANDERS_MENU2_LEVEL,
        LIST_SETTINGS_MEANDER_MENU2_LEVEL,
          DELAY_MEANDER_MENU2_LEVEL,
      PARAM_LIST_LOGICAL_NODES_FOR_INPUT_MENU2_LEVEL,
      
        __BEGIN_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL,
        PARAM_LIST_INPUTS_MENU2_LEVEL = __BEGIN_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL,
        PARAM_LIST_OUTPUTS_MENU2_LEVEL,
        PARAM_LIST_LEDS_MENU2_LEVEL,
        PARAM_LIST_ALARMS_MENU2_LEVEL,
        PARAM_LIST_GROUP_ALARMS_MENU2_LEVEL,
        PARAM_LIST_ANDS_MENU2_LEVEL,
        PARAM_LIST_ORS_MENU2_LEVEL,
        PARAM_LIST_XORS_MENU2_LEVEL,
        PARAM_LIST_NOTS_MENU2_LEVEL,
        PARAM_LIST_TIMERS_MENU2_LEVEL,
        PARAM_LIST_TRIGGERS_MENU2_LEVEL,
        __NEXT_AFTER_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL,
        
          PARAM_LIST_INPUTS_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL = __NEXT_AFTER_PARAM_LIST_SELECTED_TYPE_LOGICAL_NODE_MENU2_LEVEL,
            PARAM_VIEW_CHOSEN_SIGNAL_OF_SELECTED_LOGICAL_NODE_MENU2_LEVEL,
              PARAM_LIST_LOGICAL_NODES_FOR_OUTPUT_MENU2_LEVEL,
      LANGUAGE_MENU2_LEVEL,
      LIST_SETTINGS_COMMUNIACATION_PARAMETERS_MENU2_LEVEL,
        NAME_OF_CELL_MENU2_LEVEL,
        ADDRESS_MENU2_LEVEL,
        SETTINGS_RS485_MENU2_LEVEL,
          BAUD_RS485_MENU2_LEVEL,
          PARE_RS485_MENU2_LEVEL,
          STOP_BITS_RS485_MENU2_LEVEL,
          TIMEOUT_RS485_MENU2_LEVEL,
      LIST_PASSWORDS_MENU2_LEVEL,
        SET_NEW_PASSWORD_MENU2_LEVEL,
    
    __NEXT_AFTER_SETTINGS_MENU2_LEVEL,
    
    DIAGNOSTICS_MENU2_LEVEL = __NEXT_AFTER_SETTINGS_MENU2_LEVEL,
    LABELS_MENU2_LEVEL,
      CONFIG_LABEL_MENU2_LEVEL,
      SETTINGS_LABEL_MENU2_LEVEL,
    INFO_MENU2_LEVEL,
      DATE_TIME_INFO_MENU2_LEVEL,
    
  PASSWORD_MENU2_LEVEL,
  
  MAX_NUMBER_MENU2_LEVEL
};

#endif
