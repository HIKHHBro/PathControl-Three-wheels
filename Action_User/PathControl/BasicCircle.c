/**
  ******************************************************************************
  * @file    ���ļ�ʵ���˱ջ������Ĺ���
  * @author  tzaiyang
  * @version 
  * @date    
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
/* Extern   variables ---------------------------------------------------------*/
/* Extern   function prototypes -----------------------------------------------*/
/* Private  function prototypes -----------------------------------------------*/
/* Private  functions ---------------------------------------------------------*/
/* Exported function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/**
  * @brief  �ջ�����,���귵��ֵ1��û���귵��ֵ0
  * @param  Vel:�������ٶȣ����� Vel>0��
  * @param  WardInit����ʼ�ķ���
  * @param  WardEnd������ķ���
  * @param  Radius�����İ뾶������Ϊ˳ʱ�룬����Ϊ��ʱ�룩
  * @param  IsRotate��IsRotate==1,Ҫ��ת��IsRotate==0������ת

  * @retval none
  * @author tzy
  */
int8_t BasicCircle(int Vel,float WardInit,float WardEnd,float Refangle,float Radius,int8_t IsRotate,FPIDGather_TypeDef *fpid)
{
	float ActRadius,Pos_Ox,Pos_Oy,angle,WardAdd;
	
	Pos_Ox=get_origin_x(Radius,WardInit);//����ԭ��
	Pos_Oy=get_origin_y(Radius,WardInit);
	ActRadius=sqrt(pow((Get_POS_X()-Pos_Ox),2)+pow((Get_POS_Y()-Pos_Oy),2));//ʵ�ʰ뾶
	angle=((90-WardInit)-Acos(get_cos(Radius,WardInit)));//��Բ�ĽǶ� 

	WardAdd=WardInit+angle;	
	
	if(Radius>0)//˳ʱ��
	{
	  if(IsRotate==1)FuzPidLine(Vel,WardAdd,WardAdd,Radius,ActRadius,1,fpid);
    if(IsRotate==0)FuzPidLine(Vel,WardAdd,Refangle,Radius,ActRadius,1,fpid);
	  if(WardAdd<=WardEnd)return CIRCLE_END;
	  if(WardAdd>WardEnd) return 0;		
	}
	else if(Radius<0)//��ʱ��
	{
		if(IsRotate==1) FuzPidLine(Vel,WardAdd,WardAdd,-Radius,ActRadius,-1,fpid);
    if(IsRotate==0)	FuzPidLine(Vel,WardAdd,Refangle,-Radius,ActRadius,-1,fpid); 
		if(WardAdd>=WardEnd)return CIRCLE_END;
		if(WardAdd<WardEnd) return 0;
	}
  return  2;	
}

/************************ (C) COPYRIGHT 2015 ACTION *****END OF FILE****/

