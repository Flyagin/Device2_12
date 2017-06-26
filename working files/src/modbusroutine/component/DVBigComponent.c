//#include <QtWidgets>
#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 900
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateDVBigGetReg1(int adrReg);
int privateDVBigGetReg2(int adrReg);

int getDVBigModbusRegister(int);//�������� ���������� ��������
int getDVBigModbusBit(int);//�������� ���������� ����
int setDVBigModbusRegister(int, int);// ��������
int setDVBigModbusBit(int, int);// ����

void setDVBigCountObject(void);//�������� �-�� �������
void preDVBigReadAction(void);//action �� ������
void postDVBigReadAction(void);//action ����� ������
void preDVBigWriteAction(void);//action �� ������
void postDVBigWriteAction(void);//action ����� ������
void loadDVBigActualData(void);

COMPONENT_OBJ *dvbigcomponent;

/**************************************/
//���������� ���������� ��
/**************************************/
void constructorDVBigComponent(COMPONENT_OBJ *dvbigcomp)
{
  dvbigcomponent = dvbigcomp;

  dvbigcomponent->countObject = 14;//�-�� �������

  dvbigcomponent->getModbusRegister = getDVBigModbusRegister;//�������� ���������� ��������
  dvbigcomponent->getModbusBit      = getDVBigModbusBit;//�������� ���������� ����
  dvbigcomponent->setModbusRegister = setDVBigModbusRegister;// ��������
  dvbigcomponent->setModbusBit      = setDVBigModbusBit;// ����

  dvbigcomponent->preReadAction   = preDVBigReadAction;//action �� ������
  dvbigcomponent->postReadAction  = postDVBigReadAction;//action ����� ������
  dvbigcomponent->preWriteAction  = preDVBigWriteAction;//action �� ������
  dvbigcomponent->postWriteAction = postDVBigWriteAction;//action ����� ������

  dvbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadDVBigActualData(void) {
 setDVBigCountObject(); //�������� �-�� �������

  //ActualData
   __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<dvbigcomponent->countObject; item++) {
   int value = (((arr[item].settings.control & (1 << INDEX_CTRL_INPUT_TYPE_SIGNAL)) !=0) << 0) | (1 << 1) | ((V110_V220 != 0) << 2);
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   value = arr[item].settings.set_delay[INPUT_SET_DELAY_DOPUSK];
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;
  }//for

  /*
  1. ������ ��������� �������� ��������� ��������������� ����� ��������� �� � ��� Small
  2. ���� �������� � ���������� ***_prt, �� ��� �������� __LN_XXX � ��� ����� �������� ��� �������� __settings_for_���
  __LN_XXX ������ � ���� _settings_for_���
  
  3. 
  enum _XXX__output_signals - ������������ ������ ������ (���������� � 0 ��� ��� �������������� ��'���� �����, ��� ����� ��������� � 1, ����� ������ 1 ��� ������������� ��'���� ��� ������ �������� ��� ����������� ������������� ��'����)
  enum _XXX_d_trigger  - ����� ��� �����
  enum _XXX_input_signal - ������������ ������ �����
  enum _settings_delay_of_XXX - ������������ ��� ��������
  enum __index_ctrl_xxx - ������������ ��� "������" ���������
  enum _settings_pickup_of_XXX ������������ ��� �������
  
  4. ���� �������������
  uint32_t param[XXX_SIGNALS_IN] - ������ ������, ���� ���������� �� ����� ����. �������� (id; N; out) id - � enum _id_fb; N � out ����������� � 1-��
  
  int32_t pickup[GROUP_ALARM_PICKUPS] - ������� (� �������� �� ��-�������)
  int32_t set_delay[XXX_SET_DELAYS] - �������� (� �������� �� ��)
  uint32_t control - ����������
  uint32_t analog_input_control - ��� ��� ���� ���������� ������
  
  */
}//loadActualData() 

int getDVBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(dvbigcomponent->isActiveActualData) loadDVBigActualData(); //ActualData
  dvbigcomponent->isActiveActualData = 0;
  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;//MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getDVBigModbusBit(int adrReg)
{
  //�������� ���������� ��������
  superSetOperativMarker(dvbigcomponent, adrReg);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateDVBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
//  if(privateDVBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(dvbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
   break; 
   case 1:
    if(dataReg>60) return MARKER_ERRORDIAPAZON;
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setDVBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(dvbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setDVBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_input; //ʳ������ ���������� �����
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  dvbigcomponent->countObject = cntObj;
}//
void preDVBigReadAction(void) {
//action �� ������
  dvbigcomponent->operativMarker[0] = -1;
  dvbigcomponent->operativMarker[1] = -1;//����������� ������
  dvbigcomponent->isActiveActualData = 1;
}//
void postDVBigReadAction(void) {
//action ����� ������
  if(dvbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preDVBigWriteAction(void) {
//action �� ������
  dvbigcomponent->operativMarker[0] = -1;
  dvbigcomponent->operativMarker[1] = -1;//����������� ������
  dvbigcomponent->isActiveActualData = 1;
}//
void postDVBigWriteAction(void) {
//action ����� ������
  if(dvbigcomponent->operativMarker[0]<0) return;//�� ���� ������
/*
  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
  int countRegister = dvbigcomponent->operativMarker[1]-dvbigcomponent->operativMarker[0]+1;
  if(dvbigcomponent->operativMarker[1]<0) countRegister = 1;

        qDebug()<<"offsetDV= "<<offset;

        qDebug()<<"operativMarkerDV[0]= "<<dvbigcomponent->operativMarker[0];
        qDebug()<<"operativMarkerDV[1]= "<<dvbigcomponent->operativMarker[1];
*/
}//

int privateDVBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = dvbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateDVBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
