#include "KEY_CRL.h"

KEY key;

void KEY_Init( void )
{
    key.channel_write_flag = 0;
    key.temp_alarm_writr_flag = 0;
}

void jump_to_init( void )
{
    icon_refresh();
    /*       无图标跳动     */
    gui_beat.beat_switch = BEAT_OFF;

    /*       可继续查询从机状态     */

    /*       复位图标跳动起始点     */
    gui_beat.beat_select = 0;

    key.channel_write_flag    = 0;
    key.temp_alarm_writr_flag = 0;
    dry_dis();
    channel_dis();
}

void key_scan( void )
{
    uint8_t key_value;

    /*       50ms检测一次     */
    if(key.key_scan_flag == 1)
	{
		key_value = (B1_VAL) | (B2_VAL<<1) | (B3_VAL<<2) | (B4_VAL<<3) | (B5_VAL<<4);
	}
    switch (key_value)
    {
        case KEY1:      KEY1_press();       break;

        case KEY2:      KEY2_press();       break;

        case KEY3:      KEY3_press();       break;

        case KEY4:      KEY4_press();       break;

        case KEY5:      KEY5_press();       break;

        default:                            break;
    }
}

void KEY1_press( void )
{
    uint8_t key_value = KEY1;
    uint8_t key1_press_cnt = 100;

    buzzer_open();
    while((key_value == KEY1)&&(key1_press_cnt != 0)) 
    {
        key_value = (B1_VAL) | (B2_VAL<<1) | (B3_VAL<<2) | (B4_VAL<<3) | (B5_VAL<<4);
        key1_press_cnt--;
        delay_ms(10); 
    }
    if(( key1_press_cnt == 0 ) && ( key.channel_write_flag == 0 ))      //长按KEY1进入Dry选择
    {
        buzzer_close();
        delay_ms(500);

        gui_beat.beat_select = DRY_ICON;
        gui_beat.beat_switch = BEAT_ON;
        key.channel_write_flag  = 1; 
    }

    if( key.channel_write_flag == 1 )                         //进入Dry选择后短按KEY1调节Dry通道
    {
        gui_info.dry_info++;
        if( gui_info.dry_info == 6 )
        {
            gui_info.dry_info = 1;
        }
        dry_dis();
    }else                                                   //非Dry选择  则调节Channel通道
    {
        gui_info.channel_info++;
        if( gui_info.channel_info == 6 )
        {
            gui_info.channel_info = 1;
        }

        channel_dis();
    }
    
    senf_to_slave_16();
    
    buzzer_close();
    key.key_scan_flag = 0;
}

void KEY2_press()
{
    buzzer_open();

    if( gui_beat.beat_switch == 0 )             //无图标跳动，则调节功率
    {
        delay_ms(30);
        if( gui_info.power_val < 100 )
        {
            gui_info.power_val += 5;
        }
        power_dis();
        senf_to_slave_16();
    }else if( key.temp_alarm_writr_flag == 1 )  //Alarm调节界面，调节三路报警温度
    {
        switch(gui_beat.beat_select)
            {
                case TEMP1_ALARM:
                    if( gui_info.temp1_alarm_val < 120 )
                    {
                        gui_info.temp1_alarm_val++;
                    }
                            
                    break;

                case TEMP2_ALARM:

                    if( gui_info.temp2_alarm_val < 120 )
                    {
                        gui_info.temp2_alarm_val++;
                    }
                    break;

                case TEMP3_ALARM:

                    if( gui_info.temp3_alarm_val < 120 )
                    {
                        gui_info.temp3_alarm_val++;
                    }
                    break;

                default:
                    break;
            }
    }else                                   //图标调节界面，调节三个图标变量
    {
        switch(gui_beat.beat_select)
        {
            case POWER_ICON:
                if( gui_info.power_val < 100 )
                {
                    gui_info.power_val += 5;
                }
                power_dis();
                break;

            case FAN_ICON:
                if( gui_info.fan_level < 6 )
                {
                    gui_info.fan_level += 1;
                }
                fan_dis();
                break;

            case MODE_ICON:
                gui_info.mode_info += 1;
                if( gui_info.mode_info >= 3 )
                {
                    gui_info.mode_info = 3;
                }
                mode_dis();
                mode_write();

                break;

            default:
                break;
        }
        senf_to_slave_16();
    }
    
    buzzer_close();
    key.key_scan_flag = 0;
}


void KEY3_press()
{
    buzzer_open();
    if( key.channel_write_flag == 1 )       //如果处于Dry调节界面，短按KEY3进入Alarm温度调节界面
    {
        key.channel_write_flag    = 0;
        key.temp_alarm_writr_flag = 1;

        dry_dis();                          //刷新

        gui_beat.beat_select = 7;
        gui_beat.beat_switch = BEAT_ON;
    }

    if( key.temp_alarm_writr_flag == 1 )   //如果处于Alarm温度调节界面，则在三路Alarm温度之间跳转
    {
        switch(gui_beat.beat_select)
        {
            case TEMP1_ALARM:

                gui_beat.beat_select = TEMP2_ALARM;

                break;

            case TEMP2_ALARM:

                gui_beat.beat_select = TEMP3_ALARM;
                break;

            case TEMP3_ALARM:

                gui_beat.beat_select = TEMP1_ALARM;
                break;

            default:
                break;
        }   
    }else                           //如果处于图标调节界面，则在三个图标之间跳转
    {
        switch(gui_beat.beat_select)
        {
            case POWER_ICON:
                power_dis();
                gui_beat.beat_select = FAN_ICON;

                break;

            case FAN_ICON:
                fan_dis();
                gui_beat.beat_select = MODE_ICON;
                gui_info.mode_info = 2;
                break;

            case MODE_ICON:
                mode_dis();
                jump_to_init();
                break;

            default:
                gui_beat.beat_select++;
                gui_beat.beat_switch = BEAT_ON;
                break;
        }
    }
    
    senf_to_slave_16();
    
    buzzer_close();
    key.key_scan_flag = 0;
}

void KEY4_press()
{
    buzzer_open();

    if( gui_beat.beat_switch == 0 )         //无图标跳动，则调节功率
    {
        delay_ms(30);
        if( gui_info.power_val > 20 )
        {
            gui_info.power_val -= 5;
        }
        senf_to_slave_16();
        power_dis();
    }
    else if( key.temp_alarm_writr_flag == 1 )  //Alarm调节界面，调节三路报警温度
    {
        switch(gui_beat.beat_select)
            {
                case TEMP1_ALARM:
                    if( gui_info.temp1_alarm_val > 20 )
                    {
                        gui_info.temp1_alarm_val--;
                    }
                            
                    break;

                case TEMP2_ALARM:

                    if( gui_info.temp2_alarm_val > 20 )
                    {
                        gui_info.temp2_alarm_val--;
                    }
                    break;

                case TEMP3_ALARM:

                    if( gui_info.temp3_alarm_val > 20 )
                    {
                        gui_info.temp3_alarm_val--;
                    }
                    break;

                default:
                    break;
            }
    }else                              //图标调节界面，调节三个图标变量         
    {
        switch(gui_beat.beat_select)
        {
            case POWER_ICON:
                if( gui_info.power_val > 0 )
                {
                    gui_info.power_val -= 5;
                }
                power_dis();
                break;

            case FAN_ICON:
                if( gui_info.fan_level > 0)
                {
                    gui_info.fan_level -= 1;
                }
                fan_dis();
                break;

            case MODE_ICON:
                gui_info.mode_info -= 1;
                if( gui_info.mode_info <= 1 )
                {
                    gui_info.mode_info = 1;
                }
                mode_dis();
                mode_write();

                break;

            default:
                break;
        }
        senf_to_slave_16();
    }

    buzzer_close();
    key.key_scan_flag = 0;
}

void KEY5_press()
{
    uint8_t key_value = KEY5;
    uint8_t key5_press_cnt = 100;

    buzzer_open();

    while((key_value == KEY5)&&(key5_press_cnt!=0)) 
    {
        key_value = (B1_VAL) | (B2_VAL<<1) | (B3_VAL<<2) | (B4_VAL<<3) | (B5_VAL<<4);
        key5_press_cnt--;
        delay_ms(10); 
    }
    if( key5_press_cnt == 0 )           //长按切换同步状态
    {
        gui_info.sync_switch = 1 - gui_info.sync_switch;
        sync_dis();
        senf_to_slave_16();

        buzzer_close();
        delay_ms(500);
    }else                               //短按退出并保存
    {
        jump_to_init();
        senf_to_slave_16();
    }

    buzzer_close();
    key.key_scan_flag = 0;
}

void buzzer_open( void )
{
    HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_SET);
}

void buzzer_close( void )
{
    delay_ms(150);
    HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET);
}
