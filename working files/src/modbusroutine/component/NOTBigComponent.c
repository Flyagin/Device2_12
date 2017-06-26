#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 13525
//���� �-�� �������
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 2

int privateNOTBigGetReg1(int adrReg);
int privateNOTBigGetReg2(int adrReg);

int getNOTBigModbusRegister(int);//�������� ���������� ��������
int getNOTBigModbusBit(int);//�������� ���������� ����
int setNOTBigModbusRegister(int, int);//�������� ���������� ��������
int setNOTBigModbusBit(int, int);//�������� ���������� ����

void setNOTBigCountObject(void);//�������� �-�� �������
void preNOTBigReadAction(void);//action �� ������
void postNOTBigReadAction(void);//action ����� ������
void preNOTBigWriteAction(void);//action �� ������
void postNOTBigWriteAction(void);//action ����� ������
void loadNOTBigActualData(void);

COMPONENT_OBJ *notbigcomponent;

/**************************************/
//���������� ���������� NOT
/**************************************/
void constructorNOTBigComponent(COMPONENT_OBJ *notbigcomp)
{
  notbigcomponent = notbigcomp;

  notbigcomponent->countObject = 0;//�-�� �������

  notbigcomponent->getModbusRegister = getNOTBigModbusRegister;//�������� ���������� ��������
  notbigcomponent->getModbusBit      = getNOTBigModbusBit;//�������� ���������� ����
  notbigcomponent->setModbusRegister = setNOTBigModbusRegister;//�������� ���������� ��������
  notbigcomponent->setModbusBit      = setNOTBigModbusBit;//�������� ���������� ����

  notbigcomponent->preReadAction   = preNOTBigReadAction;//action �� ������
  notbigcomponent->postReadAction  = postNOTBigReadAction;//action ����� ������
  notbigcomponent->preWriteAction  = preNOTBigWriteAction;//action �� ������
  notbigcomponent->postWriteAction = postNOTBigWriteAction;//action ����� ������

  notbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

void loadNOTBigActualData(void) {
 setNOTBigCountObject(); //�������� �-�� �������
  //ActualData
   __LN_NOT *arr = (__LN_NOT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
   for(int item=0; item<notbigcomponent->countObject; item++) {
   //NOT item.1 0
   int value = arr[item].settings.param[0];
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   //NOT item.1 1
   value = arr[item].settings.param[1];
   tempReadArray[item*REGISTER_FOR_OBJ+1] = value;
   }//for
}//loadActualData() 

int getNOTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(notbigcomponent->isActiveActualData) loadNOTBigActualData(); //ActualData
  notbigcomponent->isActiveActualData = 0;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getNOTBigModbusBit(int adrBit)
{
  //�������� ���������� ��������
  superSetOperativMarker(notbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(privateNOTBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(notbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  switch((adrReg-BEGIN_ADR_REGISTER)%REGISTER_FOR_OBJ) {
   case 0:
    if(dataReg>MAXIMUMI) return MARKER_ERRORDIAPAZON;
   break; 
   case 1:
   break; 
  default: return MARKER_OUTPERIMETR;
  }//switch
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusBit(int adrBit, int x)
{
  UNUSED(x);
  //�������� ���������� ��������
  superSetOperativMarker(notbigcomponent, adrBit);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setNOTBigCountObject(void) {
//�������� �-�� �������
  int cntObj = current_config.n_not;   //ʳ������ �������� "��"
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  notbigcomponent->countObject = cntObj;
}//
void preNOTBigReadAction(void) {
//action �� ������
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//����������� ������
  notbigcomponent->isActiveActualData = 1;
}//
void postNOTBigReadAction(void) {
//action ����� ������
  if(notbigcomponent->operativMarker[0]<0) return;//�� ���� ������
}//
void preNOTBigWriteAction(void) {
//action �� ������
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//����������� ������
  notbigcomponent->isActiveActualData = 1;
}//
void postNOTBigWriteAction(void) {
//action ����� ������
  if(notbigcomponent->operativMarker[0]<0) return;//�� ���� ������
//  int offset = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
//  int countRegister = notbigcomponent->operativMarker[1]-notbigcomponent->operativMarker[0]+1;
//  if(notbigcomponent->operativMarker[1]<0) countRegister = 1;
}//

int privateNOTBigGetReg1(int adrReg)
{
  //��������� ���������� ��������
  int count_register = notbigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateNOTBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
