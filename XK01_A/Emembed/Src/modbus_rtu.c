#include "modbus_rtu.h"

MODBUS_INFO modbus;

/**
 * @brief	发送1帧数据
 * 
 * @param   buf：待发送数组首地址           
 * @param   len：数组长度           
 * 
  @return  void
 */
void modbus_send_data( UART_HandleTypeDef *huart, uint8_t *buf , uint8_t len )
{
    HAL_UART_Transmit(huart,(uint8_t*)buf,len,1000);
    
    while (__HAL_UART_GET_FLAG(huart,UART_FLAG_TC) != SET);
}

/**
 * @brief	modbus接收函数，接收并判断Function后转到相应Function函数进行处理
 * 
 * @param   buf：待发送数组首地址           
 * @param   len：数组长度           
 * 
  @return  void
 */
void Modbus_Event_Slave1( void )
{
    uint16_t crc,rccrc;
     /*1.接收完毕                                           */
    if( rs485_1.reflag == 1 )
    { 
        printf("222 \r\n");
        rs485_1.reflag = 0;

        /*2.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_1.rcvbuf, rs485_1.recount-2);
        rccrc = (rs485_1.rcvbuf[rs485_1.recount-2]<<8) | (rs485_1.rcvbuf[rs485_1.recount-1]);
        if ( crc == rccrc)
        {
            if( rs485_1.rcvbuf[0] == SLAVE_ADDR )
            {
                switch ( rs485_1.rcvbuf[1] )
                {         
                    case 0x03:		Modbus_Fun3_Slave1();		break;
                    case 0x04:		Modbus_Fun4_Slave1();      break;            

                    default:						    break;
                }
                    /* RX允许继续接收，开启超时接收计时               */
                    rs485_1.recount = 0;
            }
        }
    }
}

void Modbus_Event_Slave2( void )
{
    uint16_t crc,rccrc;

     /*1.接收完毕                                           */
    if( rs485_2.reflag == 1 )
    { 
        rs485_2.reflag = 0;

        /*2.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_2.rcvbuf, rs485_2.recount-2);
        rccrc = (rs485_2.rcvbuf[rs485_2.recount-2]<<8) | (rs485_2.rcvbuf[rs485_2.recount-1]);
        if ( crc == rccrc)
        {
            if( rs485_2.rcvbuf[0] == SLAVE_ADDR )
            {
                switch ( rs485_2.rcvbuf[1] )
                {         
                    case 0x03:		Modbus_Fun3_Slave2();		break;
                    case 0x04:		Modbus_Fun4_Slave2();      break;            

                    default:						    break;
                }
                    /* RX允许继续接收，开启超时接收计时               */
                    rs485_2.recount = 0;
            }
        }
    }
}

void Modbus_Event_Slave3( void )
{
    uint16_t crc,rccrc;

     /*1.接收完毕                                           */
    if( rs485_3.reflag == 1 )
    { 
        rs485_3.reflag = 0;

        /*2.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_3.rcvbuf, rs485_3.recount-2);
        rccrc = (rs485_3.rcvbuf[rs485_3.recount-2]<<8) | (rs485_3.rcvbuf[rs485_3.recount-1]);
        if ( crc == rccrc)
        {
            if( rs485_3.rcvbuf[0] == SLAVE_ADDR )
            {
                switch ( rs485_3.rcvbuf[1] )
                {         
                    case 0x03:		Modbus_Fun3_Slave3();		break;
                    case 0x04:		Modbus_Fun4_Slave3();      break;            

                    default:						    break;
                }
                    /* RX允许继续接收，开启超时接收计时               */
                    rs485_3.recount = 0;
            }
        }
    }
}

void Modbus_Fun3_Slave1()
{
   uint8_t start_addr_03 = 3;              //Slave reply  DATA1_H address

   for( uint16_t i = 0; i < 6; i++)
   {
       switch (i)
       {
        /*          40001 功率            */
        case 0:
            gui_info.power_val = rs485_1.rcvbuf[start_addr_03 + 1];  
            break;

        /*          40002 风速            */
        case 1:
            gui_info.fan_level = rs485_1.rcvbuf[start_addr_03 + 1];  

            break;

        /*          40003 报警温度            */
        case 2:

            gui_info.temp1_alarm_val = rs485_1.rcvbuf[start_addr_03 + 1];  
            break; 

        /*          40004 同步状态            */
        case 3:
            gui_info.sync_switch = rs485_1.rcvbuf[start_addr_03 + 1];  

            break;

        /*          40005 模式            */
        case 4:
            gui_info.ac_switch_slave1 = rs485_1.rcvbuf[start_addr_03];
            gui_info.channel_info = rs485_1.rcvbuf[start_addr_03 + 1];  

            break; 
        /*          40006 模式            */
        case 5:
            gui_info.mode_info = rs485_1.rcvbuf[start_addr_03 + 1];  

            break;    

        default:
            break;
       }
       start_addr_03 += 2;
   }
   gui_info.connect_on_flag1 = 1;
}

void Modbus_Fun3_Slave2()
{
   gui_info.temp2_alarm_val = rs485_2.rcvbuf[8];  
   gui_info.ac_switch_slave2 = rs485_2.rcvbuf[11];
   gui_info.connect_on_flag2 = 1;
}

void Modbus_Fun3_Slave3()
{
   gui_info.temp3_alarm_val = rs485_3.rcvbuf[8];  
    gui_info.ac_switch_slave3 = rs485_3.rcvbuf[11];
   gui_info.connect_on_flag3 = 1;
}

void Modbus_Fun4_Slave1()
{
    uint8_t start_addr_04 = 3;              //Slave reply  DATA1_H address

    for( uint16_t i = 0; i < 2; i++)
    {
        switch (i)
        {
            case 0:
                gui_info.temp1_val = rs485_1.rcvbuf[start_addr_04 + 1];  

                break;

            case 1:
                gui_info.envir_humidity = rs485_1.rcvbuf[start_addr_04];  
                gui_info.envir_temp     = rs485_1.rcvbuf[start_addr_04 + 1];
                LCD_ShowNum(270,57,gui_info.temp1_val,3,16,POINT_COLOR,BACK_COLOR);

                dht11_dis();
                printf("temp1 === \r\n");
                break;

            default:
                break;
        }
        start_addr_04 += 2;
    }
}

void Modbus_Fun4_Slave2()
{
    gui_info.temp2_val = rs485_2.rcvbuf[4];
    LCD_ShowNum(270,99,gui_info.temp2_val,3,16,POINT_COLOR,BACK_COLOR);
    printf("temp2 === \r\n");
    
}

void Modbus_Fun4_Slave3()
{
    gui_info.temp3_val = rs485_3.rcvbuf[4];
    LCD_ShowNum(270,141,gui_info.temp3_val,3,16,POINT_COLOR,BACK_COLOR);
    printf("temp3 === \r\n");
}
/**
 * @brief	crc校验函数
 * 
 * @param   buf：  Address(1 byte) +Funtion(1 byte) ）+Data(n byte)   
 * @param   length:数据长度           
 * 
  @return  crc16:crc校验的值 2byte
 */
//buf内的值为 
uint16_t MODBUS_CRC16(uint8_t *buf, uint8_t length)
{
	uint8_t	i;
	uint16_t	crc16;

    /* 1, 预置16位CRC寄存器为0xffff（即全为1）                          */
	crc16 = 0xffff;	

	do
	{
        /* 2, 把8位数据与16位CRC寄存器的低位相异或，把结果放于CRC寄存器     */        
		crc16 ^= (uint16_t)*buf;		//
		for(i=0; i<8; i++)		
		{
            /* 3, 如果最低位为1，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位 再异或0xA001    */
			if(crc16 & 1)
            {
                crc16 = (crc16 >> 1) ^ 0xA001;
            }
            /* 4, 如果最低位为0，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位                */
            else
            {
                crc16 >>= 1;
            }		
		}
		buf++;
	}while(--length != 0);

	return	(crc16);
}


void get_slave1_statu_03( void )
{
    uint8_t send_buf[8] = {SLAVE_ADDR,0x03,0x00,0x00,0x00,0x05,0x69,0x9D};

    TX1_485;
    delay_ms(5);

    memcpy(modbus.modbus_send_buf,send_buf,8);

    modbus_send_data(&huart1, modbus.modbus_send_buf,8); 

    RX1_485;
    delay_ms(2);
}

void get_slave2_statu_03( void )
{
    uint8_t send_buf[8] = {SLAVE_ADDR,0x03,0x00,0x00,0x00,0x05,0x69,0x9D};

    TX2_485;
    delay_ms(5);

    memcpy(modbus.modbus_send_buf,send_buf,8);

    modbus_send_data(&huart2, modbus.modbus_send_buf,8); 

    RX2_485;
    delay_ms(2);
}

void get_slave3_statu_03( void )
{
    uint8_t send_buf[8] = {SLAVE_ADDR,0x03,0x00,0x00,0x00,0x05,0x69,0x9D};

    TX3_485;
    delay_ms(5);

    memcpy(modbus.modbus_send_buf,send_buf,8);

    modbus_send_data(&huart3, modbus.modbus_send_buf,8); 

    RX3_485;
    delay_ms(2);
}

void get_slave_statu_04( UART_HandleTypeDef *huart )
{
    uint8_t send_buf[8] = {SLAVE_ADDR,0x04,0x00,0x00,0x00,0x02,0x6B,0x69};

    if( huart->Instance == USART1)
    {
        TX1_485;
        delay_ms(2);
    
        memcpy(modbus.modbus_send_buf,send_buf,8);

        modbus_send_data(huart,modbus.modbus_send_buf,8); 

        RX1_485;
        delay_ms(2);
    }
    
    if( huart->Instance == USART2)
    {
        TX2_485;
        delay_ms(2);
    
        memcpy(modbus.modbus_send_buf,send_buf,8);

        modbus_send_data(huart,modbus.modbus_send_buf,8); 

        RX2_485;
        delay_ms(2);
    }

    if( huart->Instance == USART3)
    {
        TX3_485;
        delay_ms(2);
    
        memcpy(modbus.modbus_send_buf,send_buf,8);

        modbus_send_data(huart,modbus.modbus_send_buf,8); 

        RX3_485;
        delay_ms(2);
    }
}

void senf_to_slave_16( void )
{
    send_to_slave1();
    send_to_slave2();
    send_to_slave3();
}

void send_to_slave1( void )
{
   uint8_t send_buf[21];
   uint16_t crc;

   TX1_485;
   delay_ms(5);

   send_buf[0] = SLAVE_ADDR;
   send_buf[1] = 0x10;
   send_buf[2] = 0x00;
   send_buf[3] = 0x00;
   send_buf[4] = 0x00;
   send_buf[5] = 0x06;
   send_buf[6] = 0x0C;

   send_buf[7] = 0x00;
   send_buf[8] = gui_info.power_val;

   send_buf[9] = 0x00;
   send_buf[10] = gui_info.fan_level;

   send_buf[11] = 0X00;
   send_buf[12] = gui_info.temp1_alarm_val;

   send_buf[13] = 0x00;
   send_buf[14] = gui_info.sync_switch;

    send_buf[15] = gui_info.ac_switch_slave1;
    send_buf[16] = gui_info.channel_info;


   send_buf[17] = gui_info.mode_allow;
   send_buf[18] = gui_info.mode_info;

   crc = MODBUS_CRC16(send_buf,19);

   send_buf[19] = crc>>8;
   send_buf[20] = crc;

   memcpy(modbus.modbus_send_buf,send_buf,21);

   modbus_send_data(&huart1,modbus.modbus_send_buf,21);
   RX1_485;
    delay_ms(2);
   gui_info.mode_allow = 0;
}


void send_to_slave2( void )
{
   uint8_t send_buf[21];
   uint16_t crc;

   TX2_485;
   delay_ms(5);

   send_buf[0] = SLAVE_ADDR;
   send_buf[1] = 0x10;
   send_buf[2] = 0x00;
   send_buf[3] = 0x00;
   send_buf[4] = 0x00;
   send_buf[5] = 0x06;
   send_buf[6] = 0x0C;

   send_buf[7] = 0x00;
   send_buf[8] = gui_info.power_val;

   send_buf[9] = 0x00;
   send_buf[10] = gui_info.fan_level;

   send_buf[11] = 0X00;
   send_buf[12] = gui_info.temp2_alarm_val;

   send_buf[13] = 0x00;
   send_buf[14] = gui_info.sync_switch;

    send_buf[15] = gui_info.ac_switch_slave2;
    send_buf[16] = gui_info.channel_info;

   send_buf[17] = gui_info.mode_allow;
   send_buf[18] = gui_info.mode_info;

   crc = MODBUS_CRC16(send_buf,19);

   send_buf[19] = crc>>8;
   send_buf[20] = crc;

   memcpy(modbus.modbus_send_buf,send_buf,21);

   modbus_send_data(&huart2,modbus.modbus_send_buf,21);
   RX2_485;
   delay_ms(2);
   gui_info.mode_allow = 0;
}


void send_to_slave3( void )
{
   uint8_t send_buf[21];
   uint16_t crc;

   TX3_485;
   delay_ms(5);

   send_buf[0] = SLAVE_ADDR;
   send_buf[1] = 0x10;
   send_buf[2] = 0x00;
   send_buf[3] = 0x00;
   send_buf[4] = 0x00;
   send_buf[5] = 0x06;
   send_buf[6] = 0x0C;

   send_buf[7] = 0x00;
   send_buf[8] = gui_info.power_val;

   send_buf[9] = 0x00;
   send_buf[10] = gui_info.fan_level;

   send_buf[11] = 0X00;
   send_buf[12] = gui_info.temp3_alarm_val;

   send_buf[13] = 0x00;
   send_buf[14] = gui_info.sync_switch;

    send_buf[15] = gui_info.ac_switch_slave3;
    send_buf[16] = gui_info.channel_info;

   send_buf[17] = gui_info.mode_allow;
   send_buf[18] = gui_info.mode_info;

   crc = MODBUS_CRC16(send_buf,19);

   send_buf[19] = crc>>8;
   send_buf[20] = crc;

   memcpy(modbus.modbus_send_buf,send_buf,21);

   modbus_send_data(&huart3,modbus.modbus_send_buf,21);
   RX3_485;
delay_ms(2);
   gui_info.mode_allow = 0;
}
