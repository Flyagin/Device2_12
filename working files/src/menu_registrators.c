#include "header.h"

/*****************************************************/
//������� ����� ����������� ��������� ����������
/*****************************************************/
void make_ekran_list_registrators(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_LIST_REGISTRATORS][MAX_COL_LCD] = 
  {
    {
      " ������.���-�   ",
      " �����. ���-�   ",
      " ����� ��������."
    },
    {
      " ������.�����. ",
      " �����. �����. ",
      " ����� �������."
    },
    {
      " Analog recorder",
      "Digital recorder",
      " Diagn.Archive  "
    },
    {
      " ������.���-�   ",
      " �����. ���-�   ",
      " ����� ��������."
    }
  };

  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
    if (index_of_ekran < MAX_ROW_FOR_LIST_REGISTRATORS)
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran][j];
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ������ ����������� ����������
/*****************************************************/
void make_ekran_list_records_registrator(unsigned int type_registrator)
{
  unsigned char name_string[MAX_ROW_FOR_LIST_REGISTRATORS_RECORDS][MAX_COL_LCD] =
  {
    "                ",
    "                "
  };

  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int number_records;
  
  if (type_registrator == INDEX_ML_ANALOG_REGISTRATOR_INFO) number_records = info_rejestrator_ar.number_records;
  else if (type_registrator == INDEX_ML_DIGITAL_REGISTRATOR_INFO) number_records = info_rejestrator_dr.number_records;
  else number_records = info_rejestrator_pr_err.number_records;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  if(number_records == 0)
  {
    //���� ������
    const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        "      ���       ",
        "    �������     "
      },
      {
        "     ����       ",
        "    ������     "
      },
      {
        "    Records     ",
        "   are absent   "
      },
      {
        "      ���       ",
        "    �������     "
      }
    };

    for(int index_1 = 0; index_1 < 2; index_1++)
    {
      for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
        name_string[index_1][index_2] = information[index_language][index_1][index_2];
    }

    //������ �� �������
    current_ekran.cursor_on = 0;
  }
  else if (current_ekran.index_position < ((int)number_records))
  {
    unsigned char information[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
    {
      " ������         ",
      " �����          ",
      " Record         ",
      " �����          "
    };

    const unsigned int index_of_number[MAX_NAMBER_LANGUAGE]=  {8, 7, 8, 7};
    unsigned int index_first_symbol_in_number = index_of_number[index_language];
    unsigned int index_last_symbol_in_number = index_first_symbol_in_number + 4 - 1;
    
    unsigned int k = 0;
    while (((index_of_ekran + k) < number_records) && (k < MAX_ROW_FOR_LIST_REGISTRATORS_RECORDS))
    {
      //������� ��������� �����
      for(unsigned int i = 0; i < 4; i++) information[index_language][index_first_symbol_in_number + i] = ' ';
      
      unsigned int temp_value = index_of_ekran + k;
      unsigned int index = 0;
      while (temp_value >= 10)
      {
        unsigned int value;
        value = temp_value % 10;
        temp_value /= 10;
        information[index_language][index_last_symbol_in_number - index] = value + 0x30;
        index++;
      }
      information[index_language][index_last_symbol_in_number - index] = temp_value + 0x30;
      
      //ϳ������� �����, ��� �� ���� ������ ������ ������
      unsigned int iteration = 0;
      while ((information[index_language][index_first_symbol_in_number] == ' ') && (iteration < 4))
      {
        for (unsigned int i = 0; i < (3 - iteration); i ++)
          information[index_language][index_first_symbol_in_number + i] = information[index_language][index_first_symbol_in_number + i + 1];
        
        information[index_language][index_first_symbol_in_number + (4 - 1) - iteration] = ' ';
        iteration++;
      }

      for (unsigned int i = 0; i < MAX_COL_LCD; i++) name_string[k][i] = information[index_language][i];
      k++;
    }

    //������ �������
    current_ekran.cursor_on = 1;
  }
  else
  {
    //����������� ��������� ��������
    const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        "     ������     ",
        "  �����������   "
      },
      {
        "    �������     ",
        "  �����������  "
      },
      {
        "    Display     ",
        "     error      "
      },
      {
        "     ������     ",
        "  �����������   "
      }
    };

    for(int index_1 = 0; index_1 < 2; index_1++)
    {
      for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
        name_string[index_1][index_2] = information[index_language][index_1][index_2];
    }

    //������ �� �������
    current_ekran.cursor_on = 0;
  }
  
  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[i][j];
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ��������� ���� ��� ������ ����������� ����������
/*****************************************************/
void make_ekran_list_titles_for_record_of_digital_registrator(void)
{
  int index_language = index_language_in_array(current_settings.language);

  if ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU) == 0)
  {
    //������ ���������� ����� � DataFlash ��� ���������
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TITLES_DIGITAL_REGISTRATOR][MAX_COL_LCD] = 
    {
      {
        " ����� �������  ",
        " ���.�����.����.",
        " ���.��� �.���� ",
        " ���.��� U-min  ",
        " ���.��� U-max  ",
        " ���.��� I2-max "
      },
      {
        " ̳��� ����     ",
        " ��.�����.����. ",
        " ���.��� �.��� ",
        " ���.��� U-min  ",
        " ���.��� U-max  ",
        " ���.��� I2-max "
      },
      {
        " Time label     ",
        " Digit.S.Changes",
        "M.at Max.Ph Cur ",
        " ���.��� U-min  ",
        " ���.��� U-max  ",
        " M.at Max.I2 Cur"
      },
      {
        " ����� �����  ",
        " ���.�����.����.",
        " ���.��� �.���� ",
        " ���.��� U-min  ",
        " ���.��� U-max  ",
        " ���.��� I2-max "
      }
    };

    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
  
    index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (index_of_ekran < MAX_ROW_FOR_TITLES_DIGITAL_REGISTRATOR)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_of_ekran++;
    }
  
    //������ �������
    current_ekran.cursor_on = 1;
    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
    
    //���������, �� ����� ��� ����� �������������� �� �����
    rewrite_ekran_once_more = 0;
  }
  else
  {
    //������ ���������� ����� � DataFlash �� �� ���������
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        " ������� ������ ",
        "  �� ��������   "
      },
      {
        " ������ ������� ",
        " �� ����������  "
      },
      {
        "    Reading     ",
        "is not completed"
      },
      {
        " ������� ������ ",
        "  �� ��������   "
      }
    };

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (i < 2)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
    }

    //������ �� �������
    current_ekran.cursor_on = 0;
    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = 0;

    //���������, �� ��� ����� ����� ������������
    rewrite_ekran_once_more = 1;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ���� � ���� ������ ����������
/*
0 - ���������� ���������
1 - ��������� ���������� ����
2 - ���������� ���������
*/
/*****************************************************/
void make_ekran_data_and_time_of_records_registrator(unsigned int type_of_registrator)
{
  int index_language = index_language_in_array(current_settings.language);

  if (
      ((type_of_registrator == 0) && (buffer_for_manu_read_record[FIRST_INDEX_START_START_RECORD_DR] == LABEL_START_RECORD_DR    )) ||
      ((type_of_registrator == 1) && (buffer_for_manu_read_record[0] == LABEL_START_RECORD_PR_ERR)) ||
      ((type_of_registrator == 2) && (buffer_for_manu_read_record[0] == LABEL_START_RECORD_AR) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU) == 0))
     )
  {
    //����� ���� ��������� �� ����� ������� ������ - �������, �� � ����� ��������� ����
    unsigned char name_string[MAX_ROW_FOR_EKRAN_DATA_LABEL][MAX_COL_LCD] = 
    {
      "   XX-XX-20XX   ",
      "   XX:XX:XX.XX  ",
    };
  
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
  
    index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    /******************************************/
    //���������� ���� ���������� �������
    /******************************************/
    if (type_of_registrator == 2)
    {
      __HEADER_AR header_ar_tmp;
      /*
      � ������ ������ ��������� ������ � ��������� ���������� �����������.
      ��� �������� �� �� ������ ������ ��������� ��������� ����������� ����������
      ��� ����� ���� ��������� ������ ����
      */
      header_ar_tmp = *((__HEADER_AR*)buffer_for_manu_read_record);
      unsigned int field;
      
      //����
      field = header_ar_tmp.time[4];
      name_string[ROW_R_Y_][COL_DY1_R] = (field >>  4) + 0x30;
      name_string[ROW_R_Y_][COL_DY2_R] = (field & 0xf) + 0x30;

      //̳����
      field = header_ar_tmp.time[5];
      name_string[ROW_R_Y_][COL_MY1_R] = (field >>  4) + 0x30;
      name_string[ROW_R_Y_][COL_MY2_R] = (field & 0xf) + 0x30;

      //г�
      field = header_ar_tmp.time[6];
      name_string[ROW_R_Y_][COL_SY1_R] = (field >>  4) + 0x30;
      name_string[ROW_R_Y_][COL_SY2_R] = (field & 0xf) + 0x30;

      //������
      field = header_ar_tmp.time[3];
      name_string[ROW_R_T_][COL_HT1_R] = (field >>  4) + 0x30;
      name_string[ROW_R_T_][COL_HT2_R] = (field & 0xf) + 0x30;

      //�������
      field = header_ar_tmp.time[2];
      name_string[ROW_R_T_][COL_MT1_R] = (field >>  4) + 0x30;
      name_string[ROW_R_T_][COL_MT2_R] = (field & 0xf) + 0x30;

      //�������
      field = header_ar_tmp.time[1];
      name_string[ROW_R_T_][COL_ST1_R] = (field >>  4) + 0x30;
      name_string[ROW_R_T_][COL_ST2_R] = (field & 0xf) + 0x30;

      //��� ������
      field = header_ar_tmp.time[0];
      name_string[ROW_R_T_][COL_HST1_R] = (field >>  4) + 0x30;
      name_string[ROW_R_T_][COL_HST2_R] = (field & 0xf) + 0x30;

      //���������, �� ����� ��� ����� �������������� �� �����
      rewrite_ekran_once_more = 0;
    }
    else
    {
      //����
      name_string[ROW_R_Y_][COL_DY1_R] = (buffer_for_manu_read_record[5] >>  4) + 0x30;
      name_string[ROW_R_Y_][COL_DY2_R] = (buffer_for_manu_read_record[5] & 0xf) + 0x30;

      //̳����
      name_string[ROW_R_Y_][COL_MY1_R] = (buffer_for_manu_read_record[6] >>  4) + 0x30;
      name_string[ROW_R_Y_][COL_MY2_R] = (buffer_for_manu_read_record[6] & 0xf) + 0x30;

      //г�
      name_string[ROW_R_Y_][COL_SY1_R] = (buffer_for_manu_read_record[7] >>  4) + 0x30;
      name_string[ROW_R_Y_][COL_SY2_R] = (buffer_for_manu_read_record[7] & 0xf) + 0x30;

      //������
      name_string[ROW_R_T_][COL_HT1_R] = (buffer_for_manu_read_record[4] >>  4) + 0x30;
      name_string[ROW_R_T_][COL_HT2_R] = (buffer_for_manu_read_record[4] & 0xf) + 0x30;

      //�������
      name_string[ROW_R_T_][COL_MT1_R] = (buffer_for_manu_read_record[3] >>  4) + 0x30;
      name_string[ROW_R_T_][COL_MT2_R] = (buffer_for_manu_read_record[3] & 0xf) + 0x30;

      //�������
      name_string[ROW_R_T_][COL_ST1_R] = (buffer_for_manu_read_record[2] >>  4) + 0x30;
      name_string[ROW_R_T_][COL_ST2_R] = (buffer_for_manu_read_record[2] & 0xf) + 0x30;

      //��� ������
      name_string[ROW_R_T_][COL_HST1_R] = (buffer_for_manu_read_record[1] >>  4) + 0x30;
      name_string[ROW_R_T_][COL_HST2_R] = (buffer_for_manu_read_record[1] & 0xf) + 0x30;
    }

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (index_of_ekran < MAX_ROW_FOR_EKRAN_DATA_LABEL)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_of_ekran++;
    }
  
    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  }
  else if ((type_of_registrator == 2) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU) != 0))
  {
    //������ ���������� ����� � DataFlash �� �� ���������
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        " ������� ������ ",
        "  �� ��������   "
      },
      {
        " ������ ������� ",
        " �� ����������  "
      },
      {
        "    Reading     ",
        "is not completed"
      },
      {
        " ������� ������ ",
        "  �� ��������   "
      }
    };

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (i < 2)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
    }

    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = 0;

    //���������, �� ��� ����� ����� ������������
    rewrite_ekran_once_more = 1;
  }
  else
  {
    //����� ���� �� ��������� �� ����� ������� ������ - ������ ��������, �� � ���� �� ��������� ����
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        " �������������  ",
        "     ������     "
      },
      {
        "  �����������  ",
        "      ����      "
      },
      {
        "    Invalid     ",
        "      data      "
      },
      {
        " �������������  ",
        "     ������     "
      }
    };
    
    if(type_of_registrator == 2)
    {
      //���������, �� ����� ��� ����� ���� ������ ����������� ���������� �������������� �� ����� - �� ������� ������� � ������������� ������
      rewrite_ekran_once_more = 0;
    }

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (i < 2)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
    }

    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = 0;
  }

  //������ �� �������
  current_ekran.cursor_on = 0;

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ����� ������� ��� �������� ������������/���������� ��������� ������ ����������� ����������
/*****************************************************/
void make_ekran_title_analog_value_records_digital_registrator(void)
{
  unsigned char name_string[MAX_ROW_FOR_TITLE_EKRAN_ANALOG_VALUES_DR][MAX_COL_LCD] =
  {
    "                ",
    "                "
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int number_info_records;
  
  number_info_records = buffer_for_manu_read_record[FIRST_INDEX_NUMBER_MAX_PHASE_DR + type_view_max_values_dr - IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE];
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  index_cell_into_array_for_min_max_measurement_dr = -1; //�������, �� �� ������ �� ������� ������ ������, ���� ������� ������� �����, ���� ���������� ��������
  if(number_info_records == 0)
  {
    const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        "      ���       ",
        "    �������     "
      },
      {
        "     ����       ",
        "    ������     "
      },
      {
        "    Records     ",
        "   are absent   "
      },
      {
        "      ���       ",
        "    �������     "
      }
    };

    for(int index_1 = 0; index_1 < 2; index_1++)
    {
      for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
        name_string[index_1][index_2] = information[index_language][index_1][index_2];
    }

    //������ �� �������
    current_ekran.cursor_on = 0;
  }
  else if (current_ekran.index_position < ((int)number_info_records))
  {
    unsigned int k = 0;
    while (((index_of_ekran + k) < number_info_records) && (k < MAX_ROW_FOR_TITLE_EKRAN_ANALOG_VALUES_DR))
    {
      //������ ����, ���� ������� �������� ���� ������
      unsigned int number_finded_this_type_of_current = 0;
      unsigned int index_cell_into_array = (FIRST_INDEX_FIRST_BLOCK_DR + (sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS - 1));//������ ������ ���'�� ������������ �� ���� ������� �����, ���� �������� ��� ������ �� ����� ���� ����������
      while ((number_finded_this_type_of_current != (index_of_ekran + k + 1)) && (index_cell_into_array < FIRST_INDEX_FIRST_DATA_DR))
      {
        if (buffer_for_manu_read_record[index_cell_into_array] == type_view_max_values_dr)
          number_finded_this_type_of_current++;
        if (number_finded_this_type_of_current != (index_of_ekran + k + 1))
          index_cell_into_array += (sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS);
      }
      
      unsigned char information[MAX_COL_LCD] = "                ";
      const unsigned char ms[MAX_NAMBER_LANGUAGE][3] = 
      {
        "��.",
        "��.",
        "ms.",
        "��."
      };
      if ((number_finded_this_type_of_current == (index_of_ekran + k + 1)) && (index_cell_into_array < FIRST_INDEX_FIRST_DATA_DR))
      {
        //�� ������� �������� ����
        //���� � ����� ����� �� � ����������� ������, �� ����� �����'����� ������ ������� �������� ��������� �����
        if (position_temp  == (index_of_ekran + k))
          index_cell_into_array_for_min_max_measurement_dr = index_cell_into_array - (sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS - 1);

        //��������� ��� ����
        index_cell_into_array -= 3; //���������� ������ �� ������� ������ ����
        unsigned char sring_of_time[8] = "        ";
        unsigned int time_of_slice = buffer_for_manu_read_record[index_cell_into_array] + (buffer_for_manu_read_record[index_cell_into_array + 1]<<8) + (buffer_for_manu_read_record[index_cell_into_array + 2]<<16);

        //���������� ��� ��� � �����
        unsigned int ost, local_index = 0;
        while ((time_of_slice >= 10) && (local_index < (8 - 1)))
        {
          ost = time_of_slice % 10;
          sring_of_time[7-local_index] = ost + 0x30;
          time_of_slice /= 10;
          local_index++;
        }
        sring_of_time[7-local_index] =  time_of_slice + 0x30;

        //������� ��� ���� ���� � ��� ������� �����
        local_index = 0;
        while ((sring_of_time[local_index] == ' ') && (local_index < 8)) local_index++;
        unsigned int local_index1 = 1;
        while (local_index < 8) information[local_index1++] = sring_of_time[local_index++];
        information[local_index1++] = ' ';
        information[local_index1++] = ms[index_language][0];
        information[local_index1++] = ms[index_language][1];
        information[local_index1++] = ms[index_language][2];
      }
      else
      {
        //���������� �� ���� � �� ���� ������ ��������, ��� ���� �� ���� ������, �� �������� ����������� ��� ������� �� �����
        const unsigned char error_meas[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
        {
          " ������         ",
          " �������        ",
          " Error          ",
          " ������         "
        };
        for (unsigned int i = 0; i < MAX_COL_LCD; i++) information[i] = error_meas[index_language][i];
      }

      for (unsigned int i = 0; i < MAX_COL_LCD; i++) name_string[k][i] = information[i];
      k++;
    }

    //������ �������
    current_ekran.cursor_on = 1;
  }
  else
  {
    //����������� ��������� ��������
    const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        "     ������     ",
        "  �����������   "
      },
      {
        "    �������     ",
        "  �����������  "
      },
      {
        "    Display     ",
        "     error      "
      },
      {
        "     ������     ",
        "  �����������   "
      }
    };

    for(int index_1 = 0; index_1 < 2; index_1++)
    {
      for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
        name_string[index_1][index_2] = information[index_language][index_1][index_2];
    }

    //������ �� �������
    current_ekran.cursor_on = 0;
  }
  
  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[i][j];
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ����� ������� ��� �������� ������������� ������ 3I0/����/���(���) ������ ����������� ����������
/*****************************************************/
void make_ekran_analog_value_records_digital_registrator(void)
{
  int index_language = index_language_in_array(current_settings.language);

  if (buffer_for_manu_read_record[FIRST_INDEX_START_START_RECORD_DR] == LABEL_START_RECORD_DR)
  {
    //����� ���� ��������� �� ����� ������� ������ - �������, �� � ����� ��������� ����
    unsigned char name_string[MAX_ROW_FOR_EKRAN_ANALOG_VALUES_DR][MAX_COL_LCD] = 
    {
      " Ia   =         ",
      " Ib   =         ",
      " Ic   =         ",
      " I2   =         ",
      " I1   =         ",
      " Ua-1 =         ",
      " Ub-1 =         ",
      " Uc-1 =         ",
      " Ua-2 =         ",
      " Ub-2 =         ",
      " Uc-2 =         ",
      " Uab-1=         ",
      " Ubc-1=         ",
      " Uca-1=         ",
      " Uab-2=         ",
      " Ubc-2=         ",
      " Uca-2=         ",
      " f1 =           ",
      " f2 =           "
    };
    unsigned char *point_unsigned_char = (unsigned char *)(buffer_for_manu_read_record + index_cell_into_array_for_min_max_measurement_dr);
    unsigned int *point_unsigned_int = (unsigned int*)point_unsigned_char;

    for (unsigned int i = 0; i < MAX_ROW_FOR_EKRAN_ANALOG_VALUES_DR; i++)
    {
      if (i < 17)
      {
       //������ � �������
        unsigned int temp_measurement = *(point_unsigned_int + i);
        unsigned int start_number_digit_after_point = 3;
        convert_and_insert_char_for_measurement(start_number_digit_after_point, temp_measurement, 1, 1, name_string[i], 7);
      }
      else if (i < 19)
      {
        //�������
        int temp_measurement = *(((int *)point_unsigned_int) + i);
        if (temp_measurement < 0)
        {
          if (temp_measurement == (-2*1000))
          {
            /*������� ����� ������ ����������� ���������� MIN_FREQUENCY*/
            name_string[i][4] = '<';
            temp_measurement = MIN_FREQUENCY*1000;
          }
          if (temp_measurement == (-3*1000))
          {
            /*������� ���� ������ ����������� ���������� MAX_FREQUENCY*/
            name_string[i][4] = '>';
            temp_measurement = MAX_FREQUENCY*1000;
          }       
        }
        convert_and_insert_char_for_frequency(temp_measurement, name_string[i]);
      }
      
      if (i < 5)
        name_string[i][MAX_COL_LCD - 1] = odynyci_vymirjuvannja[index_language][INDEX_A];
      else if (i < 17)
        name_string[i][MAX_COL_LCD - 1] = odynyci_vymirjuvannja[index_language][INDEX_V];
      else
      {
        //����� �� ��� ������ �� ��� ����������� ��������
      }
    }
  
    int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;

    index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (((int)index_of_ekran) < MAX_ROW_FOR_EKRAN_ANALOG_VALUES_DR)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_of_ekran++;
    }
  
    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
    //������ �������
    current_ekran.cursor_on = 1;
  }
  else
  {
    //����� ���� �� ��������� �� ����� ������� ������ - ������ ��������, �� � ���� �� ��������� ����
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        " �������������  ",
        "     ������     "
      },
      {
        "  �����������  ",
        "      ����      "
      },
      {
        "    Invalid     ",
        "      data      "
      },
      {
        " �������������  ",
        "     ������     "
      }
    };

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (i < 2)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
    }

    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = 0;
    //������ �� �������
    current_ekran.cursor_on = 0;
  }


  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ��� ���������� ������� � ������ ����������� ����������
/*****************************************************/
void make_ekran_changing_signals_digital_registrator(void)
{
  int index_language = index_language_in_array(current_settings.language);

  if (buffer_for_manu_read_record[FIRST_INDEX_START_START_RECORD_DR] == LABEL_START_RECORD_DR)
  {
    //����� ���� ��������� �� ����� ������� ������ - �������, �� � ����� ��������� ����
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][NUMBER_TOTAL_SIGNAL_FOR_RANG][MAX_COL_LCD] = 
    {
      {NAME_RANG_RU},
      {NAME_RANG_UA},
      {NAME_RANG_EN},
      {NAME_RANG_KZ},
    };
  
    unsigned int max_number_changers_in_record = buffer_for_manu_read_record[FIRST_INDEX_NUMBER_CHANGES_DR] | (buffer_for_manu_read_record[FIRST_INDEX_NUMBER_CHANGES_DR + 1]<<8);
    unsigned int position_temp;
    unsigned int index_of_ekran;
    unsigned int array_old[N_BIG], array_new[N_BIG], array_changing[N_BIG];
    
    //����������, �� �� �� ������ �� �������
    if (current_ekran.index_position < 0) current_ekran.index_position = max_number_changers_in_record - 1;
    else if (current_ekran.index_position >= ((int)max_number_changers_in_record)) current_ekran.index_position = 0;
    position_in_current_level_menu[EKRAN_CHANGES_SIGNALS_DR] = current_ekran.index_position;

    position_temp = current_ekran.index_position;
    index_of_ekran = position_temp & (unsigned int)(~((1<<(POWER_MAX_ROW_LCD>>1)) - 1));
  
    //�������  ����� � ������� �����
    for (unsigned int i=0; i< (MAX_ROW_LCD>>1); i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� �����������
      if (index_of_ekran < max_number_changers_in_record)
      {
        //������ ������ ����: ���������� �� ������� ���� � � ������ ���� ����
        int index_of_the_slice = 0; //�������� � ������� ����
        unsigned int current_number_changes = 0;
        while (
               ((current_number_changes + buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice) + (29 - 1)]) < (index_of_ekran + 1)) &&
               (index_of_the_slice < MAX_EVENTS_IN_ONE_RECORD)  
              )
        {
          current_number_changes += buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice) + (29 - 1)];
          index_of_the_slice++;
        }
        array_new[0] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) +  3] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) +  4]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) +  5]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) +  6]<<24);
        array_new[1] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) +  7] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) +  8]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) +  9]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 10]<<24);
        array_new[2] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 11] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 12]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 13]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 14]<<24);
        array_new[3] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 15] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 16]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 17]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 18]<<24);
        array_new[4] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 19] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 20]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 21]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 22]<<24);
        array_new[5] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 23] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 24]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 25]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 26]<<24);
        array_new[6] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice    ) + 27];

        array_old[0] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) +  3] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) +  4]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) +  5]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) +  6]<<24);
        array_old[1] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) +  7] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) +  8]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) +  9]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 10]<<24);
        array_old[2] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 11] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 12]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 13]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 14]<<24);
        array_old[3] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 15] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 16]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 17]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 18]<<24);
        array_old[4] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 19] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 20]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 21]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 22]<<24);
        array_old[5] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 23] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 24]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 25]<<16) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 26]<<24);
        array_old[6] = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice - 1) + 27];
        
        //���������, �� ������� ��������
        for (unsigned int j = 0; j < N_BIG; j++) array_changing[j] = array_new[j] ^ array_old[j];

        //������ �������, ��� ����� ����� ����������
        int index_of_function_in_the_slice = 0; //�������� � ������� ����
        do
        {
          if ((array_changing[index_of_function_in_the_slice >> 5] & (1 << (index_of_function_in_the_slice & ((1<<5)-1)))) != 0)
            current_number_changes++;
          if (current_number_changes  < (index_of_ekran + 1)) index_of_function_in_the_slice++;
        }
        while (
               (current_number_changes  < (index_of_ekran + 1)) &&
               (index_of_function_in_the_slice < NUMBER_TOTAL_SIGNAL_FOR_RANG)  
              );
        
        
        if ((index_of_the_slice < MAX_EVENTS_IN_ONE_RECORD) && (index_of_function_in_the_slice < NUMBER_TOTAL_SIGNAL_FOR_RANG) )
        {
          for (unsigned int k = 0; k < 2; k++)
          {
            if (((i<<1)+k) < MAX_ROW_LCD)
            {
              if (k == 0)
              {
                //� ������� ����� ���������� ����� �������, ���� �������
                for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[(i<<1)+k][j] = name_string[index_language][index_of_function_in_the_slice][j];
              }
              else
              {
                //� ������� ����� ���������� ��� ���� � ��� �������� ������� ����� ������
                unsigned char second_row[MAX_COL_LCD] = "                ";
                unsigned char sring_of_time[8] = "        ";
                const unsigned char ms[MAX_NAMBER_LANGUAGE][3] = 
                {
                  "��.",
                  "��.",
                  "ms.",
                  "��."
                };
                const unsigned char passive_active[MAX_NAMBER_LANGUAGE][2][5] = 
                {
                  {"����.", "���. "},
                  {"���. ", "���. "},
                  {"Pass.", "Act. "},
                  {"����.", "���. "}
                };
                unsigned int time_of_slice = buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice) + 0] + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice) + 1]<<8) + (buffer_for_manu_read_record[FIRST_INDEX_FIRST_DATA_DR + 29*(1 + index_of_the_slice) + 2]<<16);
                
                //���������� ��� ��� � �����
                unsigned int ost, local_index = 0;
                while ((time_of_slice >= 10) && (local_index < (8 - 1)))
                {
                  ost = time_of_slice % 10;
                  sring_of_time[7-local_index] = ost + 0x30;
                  time_of_slice /= 10;
                  local_index++;
                }
                sring_of_time[7-local_index] =  time_of_slice + 0x30;
                
                //������� ��� ���� ���� � ��� ������� �����
                local_index = 0;
                while ((sring_of_time[local_index] == ' ') && (local_index < 8)) local_index++;
                unsigned int local_index1 = 0;
                while (local_index < 8) second_row[local_index1++] = sring_of_time[local_index++];
                if (local_index1 < 8) second_row[local_index1++] = ' ';
                second_row[local_index1++] = ms[index_language][0];
                second_row[local_index1++] = ms[index_language][1];
                second_row[local_index1++] = ms[index_language][2];
                
                //��������� ���� ������ ����������� �������
                if ((array_new[index_of_function_in_the_slice >> 5] & (1 << (index_of_function_in_the_slice & ((1<<5)-1)))) != 0)
                {
                  //������ �������� � �������� ����
                  for (local_index1 = 11; local_index1 < MAX_COL_LCD; local_index1++)
                    second_row[local_index1] = passive_active[index_language][1][local_index1 - 11];
                }
                else
                {
                  //������ �������� � �������� ����
                  for (local_index1 = 11; local_index1 < MAX_COL_LCD; local_index1++)
                    second_row[local_index1] = passive_active[index_language][0][local_index1 - 11];
                }

                for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[(i<<1)+k][j] = second_row[j];
              }
            }
          }
        }
        else
        {
          unsigned char error_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
          {
            {
              " �������������� ",
              " ������ �������."
            },
            {
              "  �����������   ",
              " ������� �����."
            },
            {
              "   Undefined    ",
              " display error  "
            },
            {
              " �������������� ",
              " ������ �������."
            }
          };
          for (unsigned int k = 0; k < 2; k++)
          {
            if (((i<<1)+k) < MAX_ROW_LCD)
              for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[(i<<1)+k][j] = error_string[index_language][k][j];
          }
        }
      }
      else
      {
        for (unsigned int k = 0; k < 2; k++)
        {
          if (((i<<1)+k) < MAX_ROW_LCD)
            for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[(i<<1)+k][j] = ' ';
        }
      }

      index_of_ekran++;
    }
  
    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = (position_temp<<1) & (MAX_ROW_LCD - 1);
    //������ ���������
    current_ekran.cursor_on = 0;
  }
  else
  {
    //����� ���� �� ��������� �� ����� ������� ������ - ������ ��������, �� � ���� �� ��������� ����
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        " �������������  ",
        "     ������     "
      },
      {
        "  �����������  ",
        "      ����      "
      },
      {
        "    Invalid     ",
        "      data      "
      },
      {
        " �������������  ",
        "     ������     "
      }
    };

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (i < 2)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
    }

    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = 0;
    //������ �� �������
    current_ekran.cursor_on = 0;
    
    current_ekran.index_position = 0;
  }


  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ��������� ���� ��� ������ ���������� ���������� ����
/*****************************************************/
void make_ekran_list_titles_for_record_of_pr_err_registrator(void)
{
  int index_language = index_language_in_array(current_settings.language);

  if ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU) == 0)
  {
    //������ ���������� ����� � DataFlash ��� ���������
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TITLES_PR_ERR_REGISTRATOR][MAX_COL_LCD] = 
    {
      {
        " ����� �������  ",
        " ���.�����������"
      },
      {
        " ̳��� ����     ",
        " ��.���������� "
      },
      {
        " Time label     ",
        " Diagn.Changes  "
      },
      {
        " ����� �����  ",
        " ���.�����������"
      }
    };
  
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
  
    index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (index_of_ekran < MAX_ROW_FOR_TITLES_PR_ERR_REGISTRATOR)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_of_ekran++;
    }
  
    //������ �������
    current_ekran.cursor_on = 1;
    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
    
    //���������, �� ����� ��� ����� �������������� �� �����
    rewrite_ekran_once_more = 0;
  }
  else
  {
    //������ ���������� ����� � DataFlash ��� ���������
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        " ������� ������ ",
        "  �� ��������   "
      },
      {
        " ������ ������� ",
        " �� ����������  "
      },
      {
        "    Reading     ",
        "is not completed"
      },
      {
        " ������� ������ ",
        "  �� ��������   "
      }
    };

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (i < 2)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
    }

    //������ �� �������
    current_ekran.cursor_on = 0;
    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = 0;

    //���������, �� ��� ����� ����� ������������
    rewrite_ekran_once_more = 1;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ��� ���������� � ����� ���������� ���������� ����
/*****************************************************/
void make_ekran_changing_diagnostics_pr_err_registrator(void)
{
  int index_language = index_language_in_array(current_settings.language);

  if (buffer_for_manu_read_record[0] == LABEL_START_RECORD_PR_ERR)
  {
    //����� ���� ��������� �� ����� ������� ������ - �������, �� � ����� ��������� ����
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_DIAGNOSTYKA][MAX_COL_LCD] = 
    {
      {
        " ��.I2C         ",
        " ��.��������    ",
        " �������� ���   ",
        " ��.���.�����.  ",
        " ��.�����.�����.",
        " ��.���� �����. ",
        " ��.����������� ",
        " ����������� ���",
        " ��.���.�����.  ",
        " ��.�����.�����.",
        " ��.�����.������",
        " ��.��c��.��.�� ",
        " ��.��c��.�.��� ",
        "���.���./��.��� ",
        " ��.���.���./��.",
        "  ��.����.���.  ",
        "  ����.���.���  ",
        "��.���.����.���.",
        "��.�����.����.�.",
        " ��.���.��.���. ",
        " ���.��.���.��� ",
        "��.���.�.��.���.",
        "��.�����.��.���.",
        " ��.���.�.���.  ",
        " ���.�.���.���  ",
        " ��.���.�.�.���.",
        " ��.�����.�.���.",
        "��.���.���.��.�.",
        "���.���.��.�.���",
        "��.���.�.�.��.�.",
        "��.�����.�.��.�.",
        " ��.���.��.���. ",
        " ���.��.���.��� ",
        " ��.���.��.���. ",
        "��.�����.��.���.",
        " ��.�.�.������� ",
        "  ������� ���   ",
        " ��.���.������� ",
        " ������� ������.",
        "��������� �����.",
        "����� ����������",
        " ���.������.RTC ",
        " �� ���.���� RTC",
        " ���� GND ���1  ",
        " ���� VREF ���1 ",
        " ���� VDD ���1  ",
        "���� GND ���1 ��",
        "���� VREF ���1��",
        "���� VDD ���1 ��",
        " ���� GND ���2  ",
        " ���� VREF ���2 ",
        " ���� VDD ���2  ",
        "���� GND ���2 ��",
        "���� VREF ���2��",
        "���� VDD ���2 ��",
        "�����.���.�.���.",
        " ��.���.����    ",
        "��.���.��.�����.",
        " ���.���.a�.���.",
        "�����.��.��.���.",
        "������ �.��.���.",
        " �.���.��.�����.",
        " �����.��.�.���.",
        " ������ �.�.���.",
        "�����.���.��.��.",
        " ������ �.��.��.",
        " ����� ����.    ",
        " ������� ����.  ",
        " �������.����.  ",
        " ������.������� ",
        " ����� ���      ",
        " ��.SPI_DF      ",
        " ��.������� SRAM",
        " ��.�����.FLASH ",
        " ��.���.��.���. ",
        " ���.�.�������  ",
        " ������ 77      ",
        " ������ 78      ",
        " ������ 79      ",
        " ������ 80      ",
        " ������ 81      ",
        " ������ 82      ",
        " ������ 83      ",
        " ������ 84      ",
        " ������ 85      ",
        " ������ 86      ",
        " ������ 87      ",
        " ������ 88      "
      },
      {
        " ���.I2C        ",
        " ���.�����������",
        "����������� ����",
        " ���.���.������.",
        "���.�����.������",
        " ���.���� ������",
        " ���.���������  ",
        " ��������� ���� ",
        " ���.���.���.   ",
        " ���.�����.���. ",
        " ���.���.������ ",
        " ���.���.��.��.",
        " ���.���.�.���.",
        "���.���./��.����",
        "���.���.���./��.",
        " ���.���.���.  ",
        " ���.���.����  ",
        " ���.���.���.�.",
        "���.�����.���.�",
        " ���.���.��.�.  ",
        " ���.��.�.����  ",
        " ���.���.�.��.�.",
        " ���.�����.��.�.",
        " ���.���.�.�.   ",
        " ���.�.�.����   ",
        " ���.���.�.�.�. ",
        " ���.�����.�.�. ",
        " ���.���.�.��.�.",
        " ���.�.��.�.����",
        "���.���.�.�.��.�",
        "���.�����.�.��.�",
        " ���.���.��.�. ",
        " ���.��.�.���� ",
        " ���.���.��.�. ",
        "���.�����.��.�.",
        " ���.�.�.������",
        "  ������ ����  ",
        " ���.���.������",
        "������� �������.",
        " ��������� ���. ",
        " ³��.����������",
        " ���.������.RTC ",
        " �� ���.���� RTC",
        " ���� GND ���1  ",
        " ���� VREF ���1 ",
        " ���� VDD ���1  ",
        "���� GND ���1 ��",
        "���� VREF ���1��",
        "���� VDD ���1 ��",
        " ���� GND ���2  ",
        " ���� VREF ���2 ",
        " ���� VDD ���2  ",
        "���� GND ���2 ��",
        "���� VREF ���2��",
        "���� VDD ���2 ��",
        "�����.���.�.���.",
        " ���.���.����   ",
        "��.�.����.������",
        " �����.���.a�.�.",
        "������.���.��.�.",
        "������ �.��.�.  ",
        "�.�.����.������.",
        " ������.���.�.�.",
        " ������ �.�.�.  ",
        "�����.���.�.��.�",
        " ������ �.�.��.�",
        " ����� ������.  ",
        " ������� ������.",
        " ���.������.    ",
        " ������.��������",
        " ³����� �ʲ    ",
        " ���.SPI_DF     ",
        " ���.����.SRAM  ",
        " ���.�����.FLASH",
        " ���.���.��.���.",
        " ���.�.����㳿  ",
        " ������� 77     ",
        " ������� 78     ",
        " ������� 79     ",
        " ������� 80     ",
        " ������� 81     ",
        " ������� 82     ",
        " ������� 83     ",
        " ������� 84     ",
        " ������� 85     ",
        " ������� 86     ",
        " ������� 87     ",
        " ������� 88     "
      },
      {
        " I2C Err.       ",
        " Settings Err.  ",
        " No settings    ",
        " Sett.W.Err.    ",
        " Sett.Ctrl.Err. ",
        " Sett.Type Err. ",
        " Adjust Err.    ",
        " No adjust      ",
        " Adjust W.Err.  ",
        "Adjust Ctrl.Err.",
        " Adjust-Set Err.",
        "Tr.LED Rest Err.",
        "Sign DO Rest Err",
        " No DO/LED Inf. ",
        " DO/LED W Err.  ",
        "  ��.����.���.  ",
        "  ����.���.���  ",
        "��.���.����.���.",
        "��.�����.����.�.",
        " An.Rec.Inf.Err.",
        " No An.Rec.Inf. ",
        "An.Rec.Inf.W.Err",
        "An.Rec.Ctrl.Err.",
        " D.Rec.Inf.Err. ",
        " No D.Rec.Inf.  ",
        "Inf.D.Rec.W.Err.",
        " D.Rec.Ctrl.Err.",
        " PER Inf.Err.   ",
        " No Inf.of PER  ",
        "Inf.W.Err.of PER",
        " PER Ctrl.Err.  ",
        " Res.C.Inf.Err. ",
        " No Res.C.Inf.  ",
        "Inf.Res.C.W.Err.",
        " Res.C.Ctrl.Err.",
        " ��.�.�.������� ",
        "  ������� ���   ",
        " ��.���.������� ",
        " RTC:Battery low",
        " RTC:Osc.stop   ",
        " RTC:Osc.fail   ",
        " RTC:Halt update",
        "RTC:No def.sett.",
        " ADC1:GND fail  ",
        " ADC1:VREF fail ",
        " ADC1:VDD fail  ",
        "ADC1:GND Test R.",
        "ADC1:VREF Test R",
        "ADC1:VDD Test R.",
        " ADC2:GND fail  ",
        " ADC2:VREF fail ",
        " ADC2:VDD fail  ",
        "ADC2:GND Test R.",
        "ADC2:VREF Test R",
        "ADC2:VDD Test R.",
        "�����.���.�.���.",
        " DO Ctrl.Err.   ",
        " An.Rec.busy    ",
        " An.Rec.buff.OVF",
        "Undef.An.Rec.Err",
        "An.Rec.Data lost",
        " D.Rec.busy     ",
        "Undef.D.Rec.Err.",
        " D.Rec.Data lost",
        "OVF of PER buff.",
        " PER Data lost  ",
        " Device Start   ",
        " Device Restart ",
        " Device Stop    ",
        " ������.������� ",
        " LCD Fail       ",
        " DF SPI Err.    ",
        " Ext.SRAM Err.  ",
        " Int.FLASH Err. ",
        " ��.���.��.���. ",
        " ���.�.�������  ",
        " Error 77       ",
        " Error 78       ",
        " Error 79       ",
        " Error 80       ",
        " Error 81       ",
        " Error 82       ",
        " Error 83       ",
        " Error 84       ",
        " Error 85       ",
        " Error 86       ",
        " Error 87       ",
        " Error 88       "
      },
      {
        " ��.I2C         ",
        " ��.��������    ",
        " �������� ���   ",
        " ��.���.�����.  ",
        " ��.�����.�����.",
        " ��.���� �����. ",
        " ��.����������� ",
        " ����������� ���",
        " ��.���.�����.  ",
        " ��.�����.�����.",
        " ��.�����.������",
        " ��.��c��.��.�� ",
        " ��.��c��.�.��� ",
        "���.���./��.��� ",
        " ��.���.���./��.",
        "  ��.����.���.  ",
        "  ����.���.���  ",
        "��.���.����.���.",
        "��.�����.����.�.",
        " ��.���.��.���. ",
        " ���.��.���.��� ",
        "��.���.�.��.���.",
        "��.�����.��.���.",
        " ��.���.�.���.  ",
        " ���.�.���.���  ",
        " ��.���.�.�.���.",
        " ��.�����.�.���.",
        "��.���.���.��.�.",
        "���.���.��.�.���",
        "��.���.�.�.��.�.",
        "��.�����.�.��.�.",
        " ��.���.��.���. ",
        " ���.��.���.��� ",
        " ��.���.��.���. ",
        "��.�����.��.���.",
        " ��.�.�.������� ",
        "  ������� ���   ",
        " ��.���.������� ",
        " ������� ������.",
        "��������� �����.",
        "����� ����������",
        " ���.������.RTC ",
        " �� ���.���� RTC",
        " ���� GND ���1  ",
        " ���� VREF ���1 ",
        " ���� VDD ���1  ",
        " ���� GND ���1��",
        "���� VREF ���1��",
        "���� VDD ���1 ��",
        " ���� GND ���2  ",
        " ���� VREF ���2 ",
        " ���� VDD ���2  ",
        " ���� GND ���2��",
        "���� VREF ���2��",
        "���� VDD ���2 ��",
        "�����.���.�.���.",
        " ��.���.����    ",
        "��.���.��.�����.",
        " ���.���.a�.���.",
        "�����.��.��.���.",
        "������ �.��.���.",
        " �.���.��.�����.",
        " �����.��.�.���.",
        " ������ �.�.���.",
        "�����.���.��.��.",
        " ������ �.��.��.",
        " ����� ����.    ",
        " ������� ����.  ",
        " �������.����.  ",
        " ������.������� ",
        " ����� ���      ",
        " ��.SPI_DF      ",
        " ��.������� SRAM",
        " ��.�����.FLASH ",
        " ��.���.��.���. ",
        " ���.�.�������  ",
        " ������ 77      ",
        " ������ 78      ",
        " ������ 79      ",
        " ������ 80      ",
        " ������ 81      ",
        " ������ 82      ",
        " ������ 83      ",
        " ������ 84      ",
        " ������ 85      ",
        " ������ 86      ",
        " ������ 87      ",
        " ������ 88      "
      }
    };
  
    unsigned int max_number_changers_in_record = buffer_for_manu_read_record[8];
    unsigned int position_temp;
    unsigned int index_of_ekran;
    unsigned int diagnostic_old[3], diagnostic_new[3], diagnostic_changing[3];

    diagnostic_old[0] = buffer_for_manu_read_record[ 9] + (buffer_for_manu_read_record[10]<<8) + (buffer_for_manu_read_record[11]<<16) + (buffer_for_manu_read_record[12]<<24);
    diagnostic_old[1] = buffer_for_manu_read_record[13] + (buffer_for_manu_read_record[14]<<8) + (buffer_for_manu_read_record[15]<<16) + (buffer_for_manu_read_record[16]<<24);
    diagnostic_old[2] = buffer_for_manu_read_record[17] + (buffer_for_manu_read_record[18]<<8) + (buffer_for_manu_read_record[19]<<16);
    diagnostic_new[0] = buffer_for_manu_read_record[20] + (buffer_for_manu_read_record[21]<<8) + (buffer_for_manu_read_record[22]<<16) + (buffer_for_manu_read_record[23]<<24);
    diagnostic_new[1] = buffer_for_manu_read_record[24] + (buffer_for_manu_read_record[25]<<8) + (buffer_for_manu_read_record[26]<<16) + (buffer_for_manu_read_record[27]<<24);
    diagnostic_new[2] = buffer_for_manu_read_record[28] + (buffer_for_manu_read_record[29]<<8) + (buffer_for_manu_read_record[30]<<16);
        
    //���������, �� ������� ��������
    diagnostic_changing[0] = diagnostic_new[0] ^ diagnostic_old[0];
    diagnostic_changing[1] = diagnostic_new[1] ^ diagnostic_old[1];
    diagnostic_changing[2] = diagnostic_new[2] ^ diagnostic_old[2];
    
    //����������, �� �� �� ������ �� �������
    if (current_ekran.index_position < 0) current_ekran.index_position = max_number_changers_in_record - 1;
    else if (current_ekran.index_position >= ((int)max_number_changers_in_record)) current_ekran.index_position = 0;
    position_in_current_level_menu[EKRAN_CHANGES_DIAGNOSTICS_PR_ERR] = current_ekran.index_position;

    position_temp = current_ekran.index_position;
    index_of_ekran = position_temp & (unsigned int)(~((1<<(POWER_MAX_ROW_LCD>>1)) - 1));
  
    //�������  ����� � ������� �����
    for (unsigned int i=0; i< (MAX_ROW_LCD>>1); i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� �����������
      if (index_of_ekran < max_number_changers_in_record)
      {
        //������ �������, ��� ����� ����� ����������
        unsigned int current_number_changes = 0;
        unsigned int index_of_diagnostic_in_the_slice = 0; //�������� � ����� �������
        do
        {
          if (_CHECK_SET_BIT(diagnostic_changing, index_of_diagnostic_in_the_slice) != 0)
            current_number_changes++;
          if (current_number_changes  < (index_of_ekran + 1)) index_of_diagnostic_in_the_slice++;
        }
        while (
               (current_number_changes  < (index_of_ekran + 1)) &&
               (index_of_diagnostic_in_the_slice < MAX_ROW_FOR_DIAGNOSTYKA)  
              );
        
        
        if (index_of_diagnostic_in_the_slice < MAX_ROW_FOR_DIAGNOSTYKA)
        {
          for (unsigned int k = 0; k < 2; k++)
          {
            if (((i<<1)+k) < MAX_ROW_LCD)
            {
              if (k == 0)
              {
                //� ������� ����� ���������� ����� ����������, ���� �������
                for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[(i<<1)+k][j] = name_string[index_language][index_of_diagnostic_in_the_slice][j];
              }
              else
              {
                //� ������� ����� ���������� ��� �������� �������� ����� ���� ����������
                unsigned char second_row[MAX_COL_LCD] = "                ";

                const unsigned char passive_active[MAX_NAMBER_LANGUAGE][2][5] = 
                {
                  {"����.", "���. "},
                  {"���. ", "���. "},
                  {"Pass.", "Act. "},
                  {"����.", "���. "}
                };

                //��������� ���� ������ ����������� �������
                if (_CHECK_SET_BIT(diagnostic_new, index_of_diagnostic_in_the_slice) != 0)
                {
                  //������ �������� � �������� ����
                  for (int j = 0; j < 4; j++)
                    second_row[1 + j] = passive_active[index_language][1][j];
                }
                else
                {
                  //������ �������� � �������� ����
                  for (int j = 0; j < 4; j++)
                    second_row[1 + j] = passive_active[index_language][0][j];
                }

                for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[(i<<1)+k][j] = second_row[j];
              }
            }
          }
        }
        else
        {
          unsigned char error_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
          {
            {
              " �������������� ",
              " ������ �������."
            },
            {
              "  �����������   ",
              " ������� �����."
            },
            {
              "   Undefined    ",
              " display error  "
            },
            {
              " �������������� ",
              " ������ �������."
            }
          };
          for (unsigned int k = 0; k < 2; k++)
          {
            if (((i<<1)+k) < MAX_ROW_LCD)
              for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[(i<<1)+k][j] = error_string[index_language][k][j];
          }
        }
      }
      else
      {
        for (unsigned int k = 0; k < 2; k++)
        {
          if (((i<<1)+k) < MAX_ROW_LCD)
            for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[(i<<1)+k][j] = ' ';
        }
      }

      index_of_ekran++;
    }
  
    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = (position_temp<<1) & (MAX_ROW_LCD - 1);
    //������ �������
    current_ekran.cursor_on = 1;
  }
  else
  {
    //����� ���� �� ��������� �� ����� ������� ������ - ������ ��������, �� � ���� �� ��������� ����
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        " �������������  ",
        "     ������     "
      },
      {
        "  �����������  ",
        "      ����      "
      },
      {
        "    Invalid     ",
        "      data      "
      },
      {
        " �������������  ",
        "     ������     "
      }
    };

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      if (i < 2)
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
    }

    //³���������� ������ �� ��������
    current_ekran.position_cursor_y = 0;
    //������ �� �������
    current_ekran.cursor_on = 0;
    
    current_ekran.index_position = 0;
  }


  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
