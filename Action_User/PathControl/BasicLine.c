/**
******************************************************************************
* @file   ʵ�ֿ���ֱ�߼�����ת�Ĺ���
* @author tzaiyang
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
* @brief  �������
* @param  none
* @param
* @retval none
*/
void LockWheel()  
{
	VelCrl(1,0);
	VelCrl(2,0);
	VelCrl(3,0);	
}

/**
  * @brief  ����ֱ�߼�����ת
  * @param  Vel:���ĺ��ٶȣ����� Vel>0��
  * @param  ward:�����н�����
                   -180��+180
  * @param  Rotate:���������ת�ٶȣ�����ʱ���� ����ͼ��
  * @param  selfAngle:���������̬�Ƕ�
  * @retval none
  * @author lxy
  */
void BasicLine(int Vel,float ward,float Rotate)
{ 
	static  int tarV[3];
	        int V_sum;	
					int RotateVal;
					int maxV=0;
	        int i=0;
	        float reduceP;

	/*������ת������*/
	RotateVal=VelTransform(Rotate);
  /*����ǰ���ܳ��ٵ�������*/
	V_sum=VelTransform(Vel);
	
/*�����ٶȼ���*/
	#ifdef    BLUE_FIELD
	tarV[2]= (V_sum*Cos(ward-Get_Angle()+ 60))+RotateVal;
	tarV[1]=-(V_sum*Cos(ward-Get_Angle()+  0))+RotateVal;
	tarV[0]=-(V_sum*Cos(ward-Get_Angle()+120))+RotateVal;
	#elif	    defined	RED_FIELD
	tarV[0]=-(V_sum*Cos(ward-Get_Angle()+ 60))-RotateVal;//������ʱ��tarV[0]���Զ��Ӹ����ţ�����0����2�ŶԵ�
	tarV[1]= (V_sum*Cos(ward-Get_Angle()+  0))-RotateVal;
	tarV[2]= (V_sum*Cos(ward-Get_Angle()+120))-RotateVal;
  #endif
	
//����ٶ�����
	for(i=0;i<3;i++)
	{
		if(fabs(tarV[i])>maxV)
			  maxV=fabs(tarV[i]);
	}
	
	if(maxV>420000)
	{
		for(i=0;i<3;i++)
		{
			reduceP=(float)tarV[i]/(float)maxV;
			tarV[i]=420000*reduceP;
		}
	}

	/*�����ٶȸ���*/
	VelCrl(1,tarV[0]);
	VelCrl(2,tarV[1]);
	VelCrl(3,tarV[2]);
	
}



/************************ (C) COPYRIGHT 2015 ACTION *****END OF FILE****/



