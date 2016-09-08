/**
  ******************************************************************************
  * @file    Fuzzy PID files   ����ģ��PID�����㷨��ֱ�߱ջ�
  * @author  ACTION-Tzaiyang
  * @version 1.0
  * @date    March-1st-2016 
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  *
  * 
  ******************************************************************************
  */ 
/* Includes -------------------------------------------------------------------*/
#include "Walk.h"

/* Private  typedef -----------------------------------------------------------*/
/* Private  define ------------------------------------------------------------*/
/* Private  macro -------------------------------------------------------------*/
/* Private  variables ---------------------------------------------------------*/
static int8_t  isfirst=1;
/* Extern   variables ---------------------------------------------------------*/
/* Extern   function prototypes -----------------------------------------------*/
/* Private  function prototypes -----------------------------------------------*/
/* Private  functions ---------------------------------------------------------*/
/* Exported function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/


/**
  * @brief  ����ģ��PID�����㷨��ֱ�߱ջ�
  * @param  Vel:�����ٶȣ����� Vel>0��
  * @param  Ward��ǰ������
  * @param  Refvalue���ο�ֵ
  * @param  Curvalue��ʵ��ֵ
  * @param  pPosition��λ�ñջ�p����
  * @param  Flag�����ڱ�ʶλ

  * @retval none
  */
void FuzPidLine(float Vel,float Ward,float Refangle,float Refvalue,float Curvalue,int8_t Flag,FPIDGather_TypeDef *FPIDGather)
{
					 float      Actvel;
					 float      adjVel;
					 float      newWard;
					 float      changeWard;
					 float      changeVel;
					 float      rotate;

					 float      errValue;
					 float	    errAngle;
					 float      errActvel;
	 static  float      sumErrAngle;
	 static  float      sumErrValue;
	 static  float      sumErrActvel;
	 static  float      last_errAngle;
	 static  float      last_errValue;
	 static  float      last_errActvel;
   static  float      errcValue;
   static  float      errcAngle;
   static  float      errcActvel;
	         int8_t     errValueCla;
					 int8_t     errAngleCla;
	         int8_t     errAcvelCla;
					 int8_t     errcValueCla;
					 int8_t     errcAngleCla;
	         int8_t     errcAcvelCla;
	 static  PIDGather_TypeDef  PIDGather; 
	      
	 Actvel=sqrt( pow(Get_ActVel_X(),2)+pow(Get_ActVel_Y(),2) );
	
	 errValue=(Refvalue-Curvalue)*Flag;/*λ�����*/
	 errAngle=Refangle-Get_Angle();/*�Ƕ����*/
	 errActvel=Vel-Actvel;/*�ٶȲ�ֵ*/
	 
   errcValue=(errValue-last_errValue);
   errcAngle=(errAngle-last_errAngle);
   errcActvel=(errActvel-last_errActvel);
	 
   //��������
   if(fabs(errValue)>ERRVALUE_MAX)   (errValue>0)?(errValue=ERRVALUE_MAX):(errValue=ERRVALUE_MIN);
   if(fabs(errAngle)>ERRANGLE_MAX)   (errAngle>0)?(errAngle=ERRANGLE_MAX):(errAngle=ERRANGLE_MIN);
   if(fabs(errActvel)>ERRACTVEL_MAX) (errActvel>0)?(errActvel=ERRACTVEL_MAX):(errActvel=ERRACTVEL_MIN);
   //����΢������
   if(fabs(errcValue)>ERRCVALUE_MAX)   (errcValue>0)?(errcValue=ERRCVALUE_MAX):(errcValue=ERRCVALUE_MIN);
   if(fabs(errcAngle)>ERRCANGLE_MAX)   (errcAngle>0)?(errcAngle=ERRCANGLE_MAX):(errcAngle=ERRCANGLE_MIN);
   if(fabs(errcActvel)>ERRCACTVEL_MAX) (errcActvel>0)?(errcActvel=ERRCACTVEL_MAX):(errcActvel=ERRCACTVEL_MIN);  
	 
	 if(isfirst){
		 sumErrAngle=0;
		 sumErrValue=0;
		 sumErrActvel=0; 
		 rotate =0;
		 changeWard=0;
		 adjVel=0; 
	 }
	 else      {
		 sumErrAngle+=errAngle;
		 sumErrValue+=errValue;
		 sumErrActvel+=errActvel;
		 
		 //���ֵ�������
     if(fabs(sumErrAngle)>ERRSUMANGLE_MAX)  (sumErrAngle>0)?(sumErrAngle=ERRSUMANGLE_MAX):(sumErrAngle=ERRSUMANGLE_MIN);
     if(fabs(sumErrValue)>ERRSUMVALUE_MAX)  (sumErrValue>0)?(sumErrValue=ERRSUMVALUE_MAX):(sumErrValue=ERRSUMVALUE_MIN);
     if(fabs(sumErrActvel)>ERRSUMACTVEL_MAX)(sumErrActvel>0)?(sumErrActvel=ERRSUMACTVEL_MAX):(sumErrActvel=ERRSUMACTVEL_MIN);
		 
		 (errValue>0)?(errValueCla=(int8_t)(errValue*3/ERRVALUE_MAX+0.5f)):(errValueCla=(int8_t)(errValue*3/ERRVALUE_MAX-0.5f));
		 (errAngle>0)?(errAngleCla=(int8_t)(errAngle*3/ERRANGLE_MAX+0.5f)):(errAngleCla=(int8_t)(errAngle*3/ERRANGLE_MAX-0.5f));
		 (errActvel>0)?(errAcvelCla=(int8_t)(errActvel*3/ERRACTVEL_MAX+0.5f)):(errAcvelCla=(int8_t)(errActvel*3/ERRACTVEL_MAX-0.5f));
		 
		 (errcValue>0)?(errcValueCla=(int8_t)(errcValue*3/ERRCVALUE_MAX+0.5f)):(errcValueCla=(int8_t)(errcValue*3/ERRCVALUE_MAX-0.5f));
		 (errcAngle>0)?(errcAngleCla=(int8_t)(errcAngle*3/ERRCANGLE_MAX+0.5f)):(errcAngleCla=(int8_t)(errcAngle*3/ERRCANGLE_MAX-0.5f));
		 (errcActvel>0)?(errcAcvelCla=(int8_t)(errcActvel*3/ERRCACTVEL_MAX+0.5f)):(errcAcvelCla=(int8_t)(errcActvel*3/ERRCACTVEL_MAX-0.5f));
		 
		 //PID�趨
		 FuzPidTable(VALUE_PID_SET,errValueCla,errcValueCla,&PIDGather,FPIDGather);
		 FuzPidTable(ANGLE_PID_SET,errAngleCla,errcAngleCla,&PIDGather,FPIDGather);
		 FuzPidTable(ACVEL_PID_SET,errAcvelCla,errcAcvelCla,&PIDGather,FPIDGather);
     //PID�������
		 rotate = -errAngle*(PIDGather.Angle).pParam-sumErrAngle*(PIDGather.Angle).iParam-errcAngle*(PIDGather.Angle).dParam;
		 changeWard=errValue*(PIDGather.Position).pParam+sumErrValue*(PIDGather.Position).iParam+errcValue*(PIDGather.Position).dParam; /*��Ҫ���ڵĽǶ�*/
	   adjVel=errActvel*(PIDGather.Actvel).pParam+sumErrActvel*(PIDGather.Actvel).iParam+(errcActvel)*PIDGather.Actvel.dParam; 
	 }
	 
	 newWard=Ward+changeWard;/*���º�Ƕ�*/
	 changeVel=(Vel+adjVel)/Cos(changeWard);/*���º��ٶ�*/
	 
	 BasicLine(changeVel,newWard,rotate);
	 last_errAngle=errAngle;
	 last_errValue=errValue;
	 last_errActvel=errActvel;
	 ClearFirst();
}

/**
  * @brief  ģ��PID���ƹ����ƥ��
  * @param  PIDGather:PID����
  * @param  Err:�����ȼ�
  * @param  Errc:�����仯�ʵȼ�

  * @retval none
  */

void FuzPidTable(int8_t Flag,int Err,int Errc,PIDGather_TypeDef *PIDGather,FPIDGather_TypeDef *FPIDGather)
{
  if(Err==NB)//First Column
	{
		if(Errc==NB){
			if(Flag==VALUE_PID_SET)PIDValSet( PB,NB,PS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PB,NB,PS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PB,NB,PS,&PIDGather->Actvel , &FPIDGather->FActvel  );
		}
		if(Errc==NM){
			if(Flag==VALUE_PID_SET)PIDValSet( PB,NB,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PB,NB,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PB,NB,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NS){
			if(Flag==VALUE_PID_SET)PIDValSet( PM,NB,NB,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PM,NB,NB,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PM,NB,NB,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==ZO){
			if(Flag==VALUE_PID_SET)PIDValSet( PM,NB,NB,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PM,NB,NB,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PM,NB,NB,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PS){
			if(Flag==VALUE_PID_SET)PIDValSet( PS,NM,NB,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PS,NM,NB,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PS,NM,NB,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PM){
			if(Flag==VALUE_PID_SET)PIDValSet( ZO,ZO,NM,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( ZO,ZO,NM,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( ZO,ZO,NM,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PB){
			if(Flag==VALUE_PID_SET)PIDValSet( ZO,ZO,PS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( ZO,ZO,PS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( ZO,ZO,PS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
	}
	if(Err==NM)//Second Column
	{
		if(Errc==NB){
			if(Flag==VALUE_PID_SET)PIDValSet( PB,NB,PS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PB,NB,PS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PB,NB,PS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NM){
			if(Flag==VALUE_PID_SET)PIDValSet( PB,NB,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PB,NB,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PB,NB,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NS){
			if(Flag==VALUE_PID_SET)PIDValSet( PM,NB,NB,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PM,NB,NB,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PM,NB,NB,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==ZO){
			if(Flag==VALUE_PID_SET)PIDValSet( PS,NB,NM,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PS,NB,NM,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PS,NB,NM,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PS){
			if(Flag==VALUE_PID_SET)PIDValSet( PS,NM,NM,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PS,NM,NM,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PS,NM,NM,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PM){
			if(Flag==VALUE_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PB){
			if(Flag==VALUE_PID_SET)PIDValSet( NS,ZO,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NS,ZO,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NS,ZO,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
	}
	if(Err==NS)//Third Column
	{
		if(Errc==NB){
			if(Flag==VALUE_PID_SET)PIDValSet( PM,NM,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PM,NM,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PM,NM,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NM){
			if(Flag==VALUE_PID_SET)PIDValSet( PM,NM,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PM,NM,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PM,NM,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NS){
			if(Flag==VALUE_PID_SET)PIDValSet( PM,NM,NM,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PM,NM,NM,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PM,NM,NM,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==ZO){
			if(Flag==VALUE_PID_SET)PIDValSet( PS,NM,NM,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PS,NM,NM,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PS,NM,NM,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PS){
			if(Flag==VALUE_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PM){
			if(Flag==VALUE_PID_SET)PIDValSet( NS,PS,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NS,PS,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NS,PS,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PB){
			if(Flag==VALUE_PID_SET)PIDValSet( NS,PS,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NS,PS,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NS,PS,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
	}
	if(Err==ZO)//Forth Column
	{
		if(Errc==NB){
			if(Flag==VALUE_PID_SET)PIDValSet( PM,NM,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PM,NM,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PM,NM,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NM){
			if(Flag==VALUE_PID_SET)PIDValSet( PM,NM,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PM,NM,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PM,NM,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NS){
			if(Flag==VALUE_PID_SET)PIDValSet( PS,NS,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PS,NS,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PS,NS,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==ZO){
			if(Flag==VALUE_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PS){
			if(Flag==VALUE_PID_SET)PIDValSet( NS,PS,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NS,PS,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NS,PS,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PM){
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PM,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PM,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PM,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PB){
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PM,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PM,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PM,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
	}
	if(Err==PS)//Fifth Column
	{
		if(Errc==NB){
			if(Flag==VALUE_PID_SET)PIDValSet( PS,NS,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PS,NS,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PS,NS,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NM){ 
			if(Flag==VALUE_PID_SET)PIDValSet( PS,NS,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PS,NS,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PS,NS,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NS){
			if(Flag==VALUE_PID_SET)PIDValSet( ZO,ZO,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( ZO,ZO,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( ZO,ZO,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==ZO){
			if(Flag==VALUE_PID_SET)PIDValSet( NS,PM,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NS,PM,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NS,PM,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PS){
			if(Flag==VALUE_PID_SET)PIDValSet( NS,PM,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NS,PM,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NS,PM,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PM){
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PM,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PM,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PM,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PB){
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PM,ZO,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PM,ZO,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PM,ZO,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
	}
	if(Err==PM)//Sixth Column
	{
		if(Errc==NB){
			if(Flag==VALUE_PID_SET)PIDValSet( PS,ZO,PB,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( PS,ZO,PB,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( PS,ZO,PB,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NM){
			if(Flag==VALUE_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( ZO,ZO,NS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NS){
			if(Flag==VALUE_PID_SET)PIDValSet( NS,PS,PS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NS,PS,PS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NS,PS,PS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==ZO){
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PS,PS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PS,PS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PS,PS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PS){ 
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PM,PS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PM,PS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PM,PS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PM){ 
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PB,PS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PB,PS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PB,PS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PB){
			if(Flag==VALUE_PID_SET)PIDValSet( NB,PB,PB,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NB,PB,PB,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NB,PB,PB,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
	}
	if(Err==PB)//Seventh Column
	{
		if(Errc==NB){
			if(Flag==VALUE_PID_SET)PIDValSet( ZO,ZO,PB,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( ZO,ZO,PB,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( ZO,ZO,PB,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NM){ 
			if(Flag==VALUE_PID_SET)PIDValSet( ZO,ZO,PM,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( ZO,ZO,PM,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( ZO,ZO,PM,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==NS){
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PS,PM,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PS,PM,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PS,PM,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==ZO){ 
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PM,PM,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PM,PM,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PM,PM,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PS){  
			if(Flag==VALUE_PID_SET)PIDValSet( NM,PM,PS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NM,PM,PS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NM,PM,PS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PM){
			if(Flag==VALUE_PID_SET)PIDValSet( NB,PB,PS,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NB,PB,PS,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NB,PB,PS,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
		if(Errc==PB){ 
			if(Flag==VALUE_PID_SET)PIDValSet( NB,PB,PB,&PIDGather->Position,&FPIDGather->FPosition);
			if(Flag==ANGLE_PID_SET)PIDValSet( NB,PB,PB,&PIDGather->Angle,   &FPIDGather->FAngle);
			if(Flag==ACVEL_PID_SET)PIDValSet( NB,PB,PB,&PIDGather->Actvel , &FPIDGather->FActvel);
		}
	}
}


void SetFirst(void)
{
	isfirst=1;
}

void ClearFirst(void)
{
	isfirst=0;
}

/**
  * @brief  ����ģ��PID�����㷨��PID�����Ե���
  * @param  pid_p:p����������
  * @param  pid_i:i����������
  * @param  pid_d:d����������
  * @param  PIDGathe:�����ջ�PID�����Ľṹ��
  * @param  FPIDVal:PID�����Ļ�����pid�ĵ����ȷ�Χ������ؽṹ��

  * @retval none
  */
void PIDValSet(float pid_p,float pid_i,float pid_d,PID_TypeDef *PIDVal,FPID_TypeDef *FPIDVal)
{
	PIDVal->pParam=FPIDVal->p_base+pid_p*FPIDVal->p_adj;
	PIDVal->iParam=FPIDVal->i_base+pid_i*FPIDVal->i_adj;
	PIDVal->pParam=FPIDVal->d_base+pid_d*FPIDVal->d_adj;
}


