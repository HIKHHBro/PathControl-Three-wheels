/**
  ******************************************************************************
  * @file    ���¸���������Ҫ�����ݣ������������꣬ʵ���˶��ٶȵ�ʵʱ����
  * @author  
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

static float Original_Pos_x;
static float Original_Pos_y;
static float Original_Angle;


static float Pos_x;
static float Pos_y;
static float Angle;

static float Pos_xtemp;                      //temporary value of coordinate in X direction 
static float Pos_ytemp;                      //temporary value of coordinate in Y direction

static int   Vel[7];

static int   actVelX,actVelY;

/* Extern   variables ---------------------------------------------------------*/
/* Extern   function prototypes -----------------------------------------------*/
/* Private  function prototypes -----------------------------------------------*/
/* Private  functions ---------------------------------------------------------*/
/* Exported function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

	/**
  * @brief   ��λϵͳ��������ϵ��X�������                                  
  * @param   
  * @param 
  * @retval  none
  */
	void Set_POS_X(float val)
	{
		Pos_x=val;
	}
	float Get_POS_X(void)
	{
	  return Pos_x;
	}
	/**
  * @brief   ��λϵͳ��������ϵ��Y�������                                  
  * @param   
  * @param 
  * @retval  none
  */
	void Set_POS_Y(float val)
	{
		Pos_y=val;
	}
	float Get_POS_Y(void)
	{
		return Pos_y;
	}
	/**
  * @brief   ��λϵͳ��������ϵ����̬����                                  
  * @param   
  * @param 
  * @retval  none
  */
	 void Set_Angle(float val)
	{
		Angle=val;
	}
	float Get_Angle(void)
	{
		return Angle;
	}
	
			/**
  * @brief   ��λϵͳԭʼX�������                                  
  * @param   
  * @param 
  * @retval  none
  */
	void Set_Original_POS_X(float val)
	{
		Original_Pos_x=val;
	}
	float	Get_Original_POS_X(void)
	{
		  return   Original_Pos_x;
	}

		/**
  * @brief   ��λϵͳԭʼY�������                                  
  * @param   
  * @param 
  * @retval  none
  */
	void Set_Original_POS_Y(float val)
	{
		Original_Pos_y=val;
	}
	float Get_Original_POS_Y(void)
	{
		  return   Original_Pos_y; 
	}

	/**
  * @brief   ��λϵͳԭʼ��̬����                                  
  * @param   
  * @param 
  * @retval  none
  */	
		void Set_Original_Angle(float val)
	{
		   Original_Angle=val;
	}

  float Get_Original_Angle(void)
	{
		  return   Original_Angle; 
	}

	/**
  * @brief   �׶���x�������                                  
  * @param   
  * @param 
  * @retval  none
  */	
	void Set_POS_Xtemp(float val)
	{
		Pos_xtemp=val;
	}
	float Get_POS_Xtemp(void)
	{
		return Pos_xtemp;
	}
	
	/**
  * @brief   �׶���y�������                                  
  * @param   
  * @param 
  * @retval  none
  */	
		void Set_POS_Ytemp(float val)
	{
		Pos_ytemp=val;
	}
	float Get_POS_Ytemp(void)
	{
		return Pos_ytemp;
	}

/**
  * @brief   ���ʵ���ٶȸ���                                  
  * @param   num �������
  * @param 
  * @retval  none
  */	
	void Set_Vel(int vel,int num)
	{
		Vel[num]=vel;
	}
	int Get_Vel(int num)
	{
		return Vel[num];
	}

/**
  * @brief   X����ʵ���ٶȸ���                                  
  * @param   none
  * @param 
  * @retval  none
  */
	void Set_ActVel_X(int val)
{
	  actVelX=val;
}
int Get_ActVel_X(void)
{
	  return   actVelX;
}

/**
  * @brief   Y����ʵ���ٶȸ���                                  
  * @param   none
  * @param 
  * @retval  none
  */
void Set_ActVel_Y(int val)
{
	  actVelY=val;
}
int Get_ActVel_Y(void)
{
	  return   actVelY;
}

/**
  * @brief   �׶����������                                  
  * @param   none
  * @param 
  * @retval  none
  */
void xyTempUpdate(void)
{
		Set_POS_Xtemp(Get_POS_X());
		Set_POS_Ytemp(Get_POS_Y());
}


/**
  * @brief   ʵ���ٶȸ���                                  
  * @param   none
  * @param 
  * @retval  none
  */
void  SetActualVel(void)
{
		int posX=0,posY=0;
		int vel_X=0,vel_Y=0;
		int i=0;
		static int prePosX[10],prePosY[10];	
	/*����ʵ���ٶ�*/
		 posX=Get_POS_X();
		 posY=Get_POS_Y();
		
		 vel_X=(posX-prePosX[0])*10;
		 vel_Y=(posY-prePosY[0])*10;
		 		 
		 Set_ActVel_X(vel_X);
		 Set_ActVel_Y(vel_Y);	
     /*���´洢������*/
		 for(i=0;i<9;i++)
		 {
			  prePosX[i]=prePosX[i+1];
			  prePosY[i]=prePosY[i+1];
		 }
		 prePosX[9]=posX;
		 prePosY[9]=posY;
}


/************************ (C) COPYRIGHT 2016 ACTION *****END OF FILE****/
