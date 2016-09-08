/**
******************************************************************************
* @file      ����ģ��PID�����㷨��PID�����趨
* @author    tzaiyang
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
  * @brief  ����ģ��PID�����㷨��PID�����Ե���
  * @param  pid_p:p����������
  * @param  pid_i:i����������
  * @param  pid_d:d����������
  * @param  PIDGathe:�����ջ�PID�����Ľṹ��
  * @param  FPIDVal:PID�����Ļ�����pid�ĵ����ȷ�Χ������ؽṹ��

  * @retval none
  */
void FPIDValSet(float p_base,float i_base,float d_base,float p_adj,float i_adj,float d_adj,FPID_TypeDef *FPIDVal)
{
	 FPIDVal->p_base=p_base;
	 FPIDVal->i_base=p_base;
	 FPIDVal->d_base=p_base;
	
	 FPIDVal->p_adj =p_adj;
	 FPIDVal->i_adj =i_adj;
	 FPIDVal->d_adj =d_adj;
}


/************************ (C) COPYRIGHT 2016 ACTION *****END OF FILE****/



