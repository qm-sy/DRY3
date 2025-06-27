#include "communication.h"

RS485_1 rs485_1;
RS485_2 rs485_2;
RS485_3 rs485_3;

/**
 * @brief	uart1回调函数 用于接收数据
 * 
 * @param   huart：标识触发回调函数的UART外设                     
 * 
  @return  void
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if( huart->Instance == USART1)
    {
        if ( rs485_1.reflag == 1 )
        {
            return;
        }
		rs485_1.rcvbuf[rs485_1.recount++] = (uint8_t)(huart1.Instance->DR & 0x00FF);
		rs485_1.timout = 0;
		if( rs485_1.recount == 1 )
		{
			rs485_1.timrun = 1;
		}

		HAL_UART_Receive_IT(&huart1,&rs485_1.rcvbuf[rs485_1.recount],1);
    }

    if( huart->Instance == USART2)
    {
        if ( rs485_2.reflag == 1 )
        {
            return;
        }
		rs485_2.rcvbuf[rs485_2.recount++] = (uint8_t)(huart2.Instance->DR & 0x00FF);
		rs485_2.timout = 0;
		if( rs485_2.recount == 1 )
		{
			rs485_2.timrun = 1;
		}

		HAL_UART_Receive_IT(&huart2,&rs485_2.rcvbuf[rs485_2.recount],1);
    }

    if( huart->Instance == USART3)
    {
        if ( rs485_3.reflag == 1 )
        {
            return;
        }
		rs485_3.rcvbuf[rs485_3.recount++] = (uint8_t)(huart3.Instance->DR & 0x00FF);
		rs485_3.timout = 0;
		if( rs485_3.recount == 1 )
		{
			rs485_3.timrun = 1;
		}

		HAL_UART_Receive_IT(&huart3,&rs485_3.rcvbuf[rs485_3.recount],1);
    }
}

void RS485_Init( void )
{
    RX1_485;
    RX2_485;
    RX3_485;

	rs485_1.reflag = 0;
	rs485_1.recount = 0;
    rs485_1.timout = 0;
    rs485_1.timrun = 0;

    rs485_2.reflag = 0;
	rs485_2.recount = 0;
    rs485_2.timout = 0;
    rs485_2.timrun = 0;

    rs485_3.reflag = 0;
	rs485_3.recount = 0;
    rs485_3.timout = 0;
    rs485_3.timrun = 0;

    modbus.modbus_04_scan_flag  = 0;
    rs485_1.reset_flag = 0;
}
