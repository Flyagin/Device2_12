#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include <stdlib.h>
#include "Shematic.h"
//#include "StructElem.h"
#include "BaseInPoint.h"
#include "InPoint.h"
#include "ExtPoint.h"
#include "LUBase.h"
#include "LUNot_1_1.h"
#include "LUDInput_0_1.h"
#include "LUDout_1_0.h"
#include "LUDInput_0_1.h"
#include "LULed.h"
#include "LUAnd_8_1.h"
#include "LUOr_8_1.h"
#include "LUXor_8_1.h"
#include "Mft.h"
#include "LULss.h"
#include "LUFKey.h"
#include "LUBGS.hpp"
#include "LUTrig.hpp"
#include "LUAlt.hpp"
#include "LUTu.h"
//#include <conio.h>
#include <string.h>
#include <ctime>
//#include "stng.h"
#include "IStng.h"
#include "I_Shm.h"

#include "MALed.hpp"
#include "RunErLed.hpp"
#include "LUTestLed.h"
//#include "../inc/variables_external.h"
//#include "../inc/libraries.h"
void DiOp(void *pObj);
void DoOp(void *pObj);
void LedOp(void *pObj);
void ButtonOp(void *pObj);
void LssOptim(void *pObj);
void BGSOp(void *pObj);
void AndOp(void *pObj);
void OrOp(void *pObj);
void XorOp(void *pObj);
void NotOp(void *pObj);
void MftOp(void *pObj);
void TrgOp(void *pObj);
void AltOp(void *pObj);
void TuOp(void *pObj);


//#pragma inline
void Shematic::DoCalcLUSources(void){

 register long i,j,lAmtProcessObj;
 void* pv;
register LUAreaListElem*pLUAreaListElem;
short *parIdxLUAreaListElem;
// struct {
//     short shAmountCalcLU, shRes;
//     void *pV;
//     LUAreaListElem* arrLUAreaListElem;
//     CLUBase* pCLUBase;//
// } sLV;
//    sLV.shAmountCalcLU = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
//    sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    //pLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
    pLUAreaListElem = static_cast<LUAreaListElem*>(pLUAreaList);

    parIdxLUAreaListElem = arIdxLUAreaListElem;

    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))->n_input; //current_config_prt.n_input;
//////////////////////////////////////////////////////////////////
    short shCounterInitCLUDout = 0;
    i = parIdxLUAreaListElem[LU_INPUT-1];//Get Obj List Index
    
    while (shCounterInitCLUDout < lAmtProcessObj ) {
            j = i + shCounterInitCLUDout;
           // pv = (pLUAreaListElem[j]).pvLU;
           // READ_DI_Op(pv);//DiOp
            READ_DI_Op( pLUAreaListElem[j].pvLU );//DiOp
            shCounterInitCLUDout++;
    } 
/////////////////////////////////////////////////////////////////
    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))->n_button;
    shCounterInitCLUDout = 0;
    i = parIdxLUAreaListElem[LU_FKEY-1];        
    do {
            j = i + shCounterInitCLUDout;
            pv = (pLUAreaListElem[j]).pvLU;
            ButtonOp(pv);
    } while (++shCounterInitCLUDout < lAmtProcessObj );
//////////////////////////////////////////////////////////////////
    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))-> n_meander;   
    shCounterInitCLUDout = 0;
    i = parIdxLUAreaListElem[LU_MEANDERS-1];
    while (shCounterInitCLUDout < lAmtProcessObj ) {
            j = i + shCounterInitCLUDout;
            pv = (pLUAreaListElem[j]).pvLU;
            AltOp(pv);
            shCounterInitCLUDout++;
            
    } 
//////////////////////////////////////////////////////////////////        
//    lAmtProcessObj = (static_cast<__CONFIG* >(p_current_config_prt))-> n_tu;
//    long lIdxCounter = 0;
//    i = parIdxLUAreaListElem[LU_TU-1];
//    
//    while (lIdxCounter < lAmtProcessObj ) {
//            j = i + lIdxCounter++;
//            pv = (pLUAreaListElem[j]).pvLU;
//            TuOp(pv);            
//    } 



}
//#pragma inline 
void Shematic::LUSelector( long lIdxLU){
register void* pv;
register LUAreaListElem*pLUAreaListElem;

pLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
pv = (pLUAreaListElem[lIdxLU]).pvLU;
(static_cast<CLUBase*>( pv))->LogicFunc( pv);
}
//    while (sLV.shAmountCalcLU--) {
//        pv = static_cast<void*>( &sLV.arrLUAreaListElem[i]);
//        sLV.pCLUBase = static_cast<CLUBase*>( (static_cast<LUAreaListElem*> (pv))->pvLU);//(CLUBase*)
//        pv = static_cast<void*>( sLV.pCLUBase); //->LogicFunc;
//       if ((static_cast<CLUBase*>( pv))->LogicFunc != Null_OP) {
//                        (static_cast<CLUBase*>( pv))->LogicFunc( reinterpret_cast<void*>(sLV.pCLUBase));
//                    }
//    }
//#pragma inline
void Shematic::LUIterator(long AmountCalcLU, long lIdxLU){
register void* pv;
register LUAreaListElem*pLUAreaListElem;

pLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
//parIdxLUAreaListElem = arIdxLUAreaListElem;
    while (AmountCalcLU--) {
        pv = (pLUAreaListElem[lIdxLU++]).pvLU;
        (static_cast<CLUBase*>( pv))->LogicFunc( pv);
    }
}
#include "Sch_Aux.cpp"
extern char chStateOptimisation;
void Shematic::DoCalcLU(void){
register union {
short* pOrderCalcNum;
char  *pCh;
}P;
long lAmtProcessObj,lIdxCounter;
long i,j;
//    TmrCalls();    
//    UpdateStateDI();
if(chStateOptimisation == 2)
   asm(
       "bkpt 1"
       );
    DoCalcLUSources();
    P.pCh = const_cast<char*>(arrChCalcLUOrderNumsSchmPage2);

    lAmtProcessObj = sizeof(arrChCalcLUOrderNumsSchmPage2)>>1;
    lIdxCounter = 0;
    do {
        i = P.pOrderCalcNum[lIdxCounter];
        j = i >> 8;
        i &= 0xff;
        i += arIdxLUAreaListElem[j-1];
        LUSelector(i);
    } while (++lIdxCounter < lAmtProcessObj );
    i = arIdxLUAreaListElem[LU_OUTPUT-1];
    LUIterator((static_cast<__CONFIG* >(p_current_config_prt))->n_output,i);//
}


//`extern DICfgSuit sDiCfg;
//`void DiOp(void *pObj){
//`    long i;
//`    CLUDInput_0_1 *pCLUDInput_0_1 = static_cast<CLUDInput_0_1 *> (pObj);
//`    i = pCLUDInput_0_1->shShemasOrdNumStng;
//`    i--;
//`i = sDiCfg.DiState.ul_val;
//`    //if (DiHrdStateUI32Bit.ul_val & (1 << i))
//`    if (sDiCfg.DiState.ul_val & (1 << i))
//`        pCLUDInput_0_1->arrOut[0] = 1; //static_cast<char>(pCLUDInput_0_1->shLUBieldOrdNum);//Any value from Input
//`    else
//`        pCLUDInput_0_1->arrOut[0] = 0;
//`}

void DoOp(void *pObj){
    CLUDout_1_0& refCLUDout_1_0 = *(static_cast<CLUDout_1_0*> (pObj));
refCLUDout_1_0.CalcReleySchematic();
}
void LedOp(void *pObj){
CLULed& rCLULed = *(static_cast<CLULed*> (pObj));
rCLULed.CalcLedSchematic();    
}
//#pragma inline
void ButtonOp(void *pObj){
long i;
CLUFKey *pCLUFKey = static_cast<CLUFKey*>(pObj);
i = static_cast<char*>(pCLUFKey->pIn)[0];
    if(i!= 0)
    pCLUFKey->chKeyPres = i;
    pCLUFKey->arrOut[0] = i;    
}

void LssOptip(void *pObj){
CLULss& rCLULss = *(static_cast<CLULss*>(pObj));

rCLULss.CalcLssSchematic();	    
}
void BGSOp(void *pObj){
CBGSig& rCBGSig = *(static_cast<CBGSig*> (pObj));
rCBGSig.CalcBusGrSigSchematic();    
}
void AndOp(void *pObj){
register long i, j;
register char* pCh;
    i = 0;
    do{
        pCh = (static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++];
        j = pCh[0];
    }while((j != 0) && (i < 8));
//    for (i = 0, pCh = (static_cast<CLUAnd_8_1*> (pObj))->arrPchIn[0], j = 1; i < 8; i++) {
//        if (pCh[i] == 0) {
//            j = 0;
//            break;
//        }
//    }
(reinterpret_cast<CLUAnd_8_1 *> (pObj))->arrOut[0] = static_cast<char> (j);

}
void OrOp(void *pObj){
    register long i, j;
    register char* pCh;
    i = 0;
    do{
        pCh = (static_cast<CLUOr_8_1*> (pObj))->arrPchIn[i++];
        j = pCh[0];
    }while((j == 0) && (i < 8));
    

    (reinterpret_cast<CLUOr_8_1 *> (pObj))->arrOut[0] = static_cast<char> (j);
    
}
void XorOp(void *pObj){
CLUXor_8_1& refCLUXor = *(static_cast<CLUXor_8_1 *> (pObj));
    refCLUXor.arrOut[0] = *(refCLUXor.arrPchIn[0])^*(refCLUXor.arrPchIn[1]);    
}
void NotOp(void *pObj){
CLUNot_1_1& refCLUNot_1_1 = *(static_cast<CLUNot_1_1 *>(pObj));
refCLUNot_1_1.arrOut[0] = !*(refCLUNot_1_1.arrPchIn[0]);    
}
void MftOp(void *pObj){
    register long i;
    //register char* pCh;, j
	CMft& rCMft = *(static_cast<CMft*>(pObj));
	i = static_cast<long>(*(rCMft.arrPchIn[0]));
//	j = rCMft.TpauseMft(i);
//	i = static_cast<long>(*(rCMft.arrPchIn[1]));//Reset
//	if(rCMft.m_MftSuit.chTypeMft == 1){
//		
//		i = rCMft.TWorkMft(i,j);
//	}
//	else{
//		i = rCMft.TdelayMft(i,j);
//	}
rCMft.arrOut[0] = static_cast<char>(i);    
}
void TrgOp(void *pObj){
CLUTrig& refCLUDTrg = *(static_cast<CLUTrig *> (pObj));
    long k, j, l; //
    //char *pCh;
    k = 0;
//    if(chGBL_BP_StopLUTrig == refCLUDTrg.shShemasOrdNumStng)
//    asm(
//                "bkpt 1"
//                );

    if (*(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__SET - 1])) //{
        k |= 1; //} 

    //pCh = refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__CLR - 1];
    if (*(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__CLR - 1]))//{
        k |= 2; //}
    

    if (k == 0) {
    l = *(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__C_SLASH - 1]);
        if (refCLUDTrg.chIn_C == 0 && l > 0) {
        j = *(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__D - 1]);
            if ( j) {
                //set
                refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 1;
                refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 0;
                refCLUDTrg.chQ = 1;
            }
            else{
                ;
                refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 0;
                refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 1;
                refCLUDTrg.chQ = 0;
            }
        }
    } else
        if (k == 1) {
        refCLUDTrg.chQ = 1;
        //refCLUDTrg.chIn_C = 0;//
        refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 1;
        refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 0;
    } else
        if (k == 2) {
        refCLUDTrg.chQ = 0;
        //refCLUDTrg.chIn_C = 0;//
        refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q - 1] = 0;
        refCLUDTrg.arrOut[DTRG__4_2_OUT_NAME_Q_INV - 1] = 1;
        
    } else if (k == 3) {
        refCLUDTrg.chError = 1;
        
    }
refCLUDTrg.chIn_C = *(refCLUDTrg.arrPchIn[DTRG__4_2_IN_NAME__C_SLASH - 1]);    
}
void AltOp(void *pObj){
    register long i, j;

    CPulseAlternator& rPulseAlt = *(static_cast<CPulseAlternator*> (pObj));
    j = rPulseAlt.arrOut[0];
    i = rPulseAlt.TAlt(j);
	
rPulseAlt.arrOut[0] = static_cast<char>(i);    
}
#pragma inline=forced
void TuOp(void *pObj){
long i;
	CLUTu *pCLUTu = static_cast<CLUTu*>(pObj);
//find Index
i = pCLUTu->shShemasOrdNumStng;
    i--;
    pCLUTu->arrOut[0] = 0;
}



//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//``````````````````````````````````````````````````````````````````````````````````
//==================================================================================
//--- 			 Optimized function for CPP Schematic     -----------
//==================================================================================
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""










