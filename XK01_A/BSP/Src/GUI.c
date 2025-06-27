#include "GUI.h"
#include "pic.h"

GUI_INFO gui_info;
GUI_BEAT gui_beat;

void GUI_Init( void )
{
    gui_info.fan_level              = LEVEL_3;
    gui_info.mode_allow             = 0;
    gui_info.mode_info              = 3;
    gui_info.power_val              = 50;
    gui_info.dry_info               = 5;
    gui_info.channel_info           = 5;
    gui_info.sync_switch            = SYNC_ON;
    gui_info.temp1_alarm_val         = 75;
    gui_info.temp2_alarm_val         = 75;
    gui_info.temp3_alarm_val         = 75;
    gui_info.connect_on_flag1        = UNCONNECT;
    gui_info.connect_on_flag2        = UNCONNECT;
    gui_info.connect_on_flag3        = UNCONNECT;
    gui_info.ac_switch_slave1        = 1;
    gui_info.ac_switch_slave2        = 1;
    gui_info.ac_switch_slave3        = 1;
    gui_beat.beat_start_flag         = 0;
    gui_beat.beat_clear              = 0;

    gui_beat.beat_select             = 0; 
    gui_beat.beat_switch             = BEAT_OFF; 
}

static void fan_beat( void )
{   
    if( gui_beat.beat_clear == 1 )
    {
        LCD_Fill(179,195,191,219,BACK_COLOR);
    }else
    {
        fan_dis();
    }
}

static void mode_beat( void )
{   
    if( gui_beat.beat_clear == 1 )
    {
        LCD_Fill(278,195,320,219,BACK_COLOR);
    }else
    {
        mode_dis();
    }
}

static void power_beat( void )
{   
    if( gui_beat.beat_clear == 1 )
    {
        LCD_Fill(63,195,99,219,BACK_COLOR);
    }else
    {
        power_dis();
    }
}

static void temp1_alarm_beat( void )
{
    if( gui_beat.beat_clear == 1 )
    {
        LCD_Fill(270,57,294,81,BACK_COLOR);
    }else
    {
        temp_alarm_dis();
    }
}

static void temp2_alarm_beat( void )
{
    if( gui_beat.beat_clear == 1 )
    {
        LCD_Fill(270,99,294,123,BACK_COLOR);
    }else
    {
        temp_alarm_dis();
    }
}

static void temp3_alarm_beat( void )
{
    if( gui_beat.beat_clear == 1 )
    {
        LCD_Fill(270,141,294,165,BACK_COLOR);
    }else
    {
        temp_alarm_dis();
    }
}

static void dry_beat( void )
{
    if( gui_beat.beat_clear == 1 )
    {
        LCD_Fill(16,55,49,77,BACK_COLOR);
        LCD_Fill(16,97,49,119,BACK_COLOR);
        LCD_Fill(16,138,49,160,BACK_COLOR);
    }else
    {
        dry_dis();
    }
}

void power_dis( void )
{
    LCD_ShowNum(63,195,gui_info.power_val,3,24,GREEN,BACK_COLOR);
}

void fan_dis( void )
{
    LCD_ShowNum(179,195,gui_info.fan_level,1,24,GREEN,BACK_COLOR);
}

void mode_dis( void )
{
    switch (gui_info.mode_info)
    {
        case 1:
            PutChinese_16(202,278,"节",BACK_COLOR,GREEN);
            PutChinese_16(202,295,"能",BACK_COLOR,GREEN);

            break;

        case 2:
            PutChinese_16(202,278,"普",BACK_COLOR,YELLOW);
            PutChinese_16(202,295,"通",BACK_COLOR,YELLOW);

            break;

        case 3:
            PutChinese_16(202,278,"强",BACK_COLOR,BRRED);
            PutChinese_16(202,295,"劲",BACK_COLOR,BRRED);

            break;

        default:
            break;
    }
}

void mode_write( void )
{
    gui_info.mode_allow = 1;
    switch (gui_info.mode_info)
    {
        case 1:
            gui_info.power_val = 30;
            gui_info.fan_level = 3;

            break;

        case 2:
            gui_info.power_val = 50;
            gui_info.fan_level = 4;

            break;

        case 3:
            gui_info.power_val = 80;
            gui_info.fan_level = 6;

            break;

        default:
            break;
    }
}

void temp_alarm_dis( void )
{
    LCD_ShowNum(270,57,gui_info.temp1_alarm_val,3,16,POINT_COLOR,BACK_COLOR);
    LCD_ShowNum(270,99,gui_info.temp2_alarm_val,3,16,POINT_COLOR,BACK_COLOR);
    LCD_ShowNum(270,141,gui_info.temp3_alarm_val,3,16,POINT_COLOR,BACK_COLOR);
}

void temp_dis( void )
{
    LCD_ShowNum(270,57,gui_info.temp1_val,3,16,POINT_COLOR,BACK_COLOR);
    LCD_ShowNum(270,99,gui_info.temp2_val,3,16,POINT_COLOR,BACK_COLOR);
    LCD_ShowNum(270,141,gui_info.temp3_val,3,16,POINT_COLOR,BACK_COLOR);
}

void alarm_icon_dis( void )
{
    if( gui_info.temp1_val >= gui_info.temp1_alarm_val )
    {
        LCD_Show_Image_Internal_Flash(97,3,29,29,gImage_temp_alarm_red,1682);
    }else
    {
        LCD_Fill(97,3,126,32,BACK_COLOR);
    }
}

void connect_dis( void )
{
    LCD_Fill(13,3,43,33,BACK_COLOR);
    LCD_Show_Image_Internal_Flash(13,3,29,30,gImage_connect_on,1740);
}

void dht11_dis( void )
{
    LCD_ShowNum(233,13,gui_info.envir_temp,2,16,DARKBLUE,BACK_COLOR);
    LCD_ShowNum(274,13,gui_info.envir_humidity,2,16,DARKBLUE,BACK_COLOR);
}

void dry_check( void )
{
    if(( gui_info.ac_switch_slave1 == 1 ) && ( gui_info.ac_switch_slave2 == 0 ) && ( gui_info.ac_switch_slave3 == 0 ))
    {
        gui_info.dry_info = 1;
    }

    if(( gui_info.ac_switch_slave1 == 0 ) && ( gui_info.ac_switch_slave2 == 1 ) && ( gui_info.ac_switch_slave3 == 0 ))
    {
        gui_info.dry_info = 2;
    }

    if(( gui_info.ac_switch_slave1 == 0 ) && ( gui_info.ac_switch_slave2 == 0 ) && ( gui_info.ac_switch_slave3 == 1 ))
    {
        gui_info.dry_info = 3;
    }

    if(( gui_info.ac_switch_slave1 == 1 ) && ( gui_info.ac_switch_slave2 == 1 ) && ( gui_info.ac_switch_slave3 == 0 ))
    {
        gui_info.dry_info = 4;
    }

    if(( gui_info.ac_switch_slave1 == 1 ) && ( gui_info.ac_switch_slave2 == 1 ) && ( gui_info.ac_switch_slave3 == 1 ))
    {
        gui_info.dry_info = 5;
    }
}
void dry_dis( void )
{
    
    channel_dis();
    switch (gui_info.dry_info)
    {
        case 1:
            gui_info.ac_switch_slave1 = 1;
            gui_info.ac_switch_slave2 = 0;
            gui_info.ac_switch_slave3 = 0;
            LCD_Show_Image_Internal_Flash(16,55,33,22,gImage_dry1_on,1452);
            LCD_Show_Image_Internal_Flash(16,97,32,22,gImage_dry2_off,1408);
            LCD_Show_Image_Internal_Flash(16,138,32,22,gImage_dry3_off,1408);
            break;

        case 2:
            gui_info.ac_switch_slave1 = 0;
            gui_info.ac_switch_slave2 = 1;
            gui_info.ac_switch_slave3 = 0;
            LCD_Show_Image_Internal_Flash(16,55,33,22,gImage_dry1_off,1452);
            LCD_Show_Image_Internal_Flash(16,97,32,22,gImage_dry2_on,1408);
            LCD_Show_Image_Internal_Flash(16,138,32,22,gImage_dry3_off,1408);
            break;

        case 3:
            gui_info.ac_switch_slave1 = 0;
            gui_info.ac_switch_slave2 = 0;
            gui_info.ac_switch_slave3 = 1;
            LCD_Show_Image_Internal_Flash(16,55,33,22,gImage_dry1_off,1452);
            LCD_Show_Image_Internal_Flash(16,97,32,22,gImage_dry2_off,1408);
            LCD_Show_Image_Internal_Flash(16,138,32,22,gImage_dry3_on,1408);
            break;

        case 4:
            gui_info.ac_switch_slave1 = 1;
            gui_info.ac_switch_slave2 = 1;
            gui_info.ac_switch_slave3 = 0;
            LCD_Show_Image_Internal_Flash(16,55,33,22,gImage_dry1_on,1452);
            LCD_Show_Image_Internal_Flash(16,97,32,22,gImage_dry2_on,1408);
            LCD_Show_Image_Internal_Flash(16,138,32,22,gImage_dry3_off,1408);
            break;

        case 5:
            gui_info.ac_switch_slave1 = 1;
            gui_info.ac_switch_slave2 = 1;
            gui_info.ac_switch_slave3 = 1;
            LCD_Show_Image_Internal_Flash(16,55,33,22,gImage_dry1_on,1452); 
            LCD_Show_Image_Internal_Flash(16,97,32,22,gImage_dry2_on,1408);
            LCD_Show_Image_Internal_Flash(16,138,32,22,gImage_dry3_on,1408);
            break;

        default:
            break;
    }
}
void channel_dis( void )
{
    switch (gui_info.dry_info)
    {
        case 1:
            channel1_dis();
            channel2_undis();
            channel3_undis();
            break;

        case 2:
            channel1_undis();
            channel2_dis();
            channel3_undis();
            break;

        case 3:
            channel1_undis();
            channel2_undis();
            channel3_dis();
            break;

        case 4:
            channel1_dis();
            channel2_dis();
            channel3_undis();
            break;

        case 5:
            channel1_dis();
            channel2_dis();
            channel3_dis();
            break;

        default:
            break;
    }
}

void channel_undis( void )
{
    channel1_undis();
    channel2_undis();
    channel3_undis();
}

void channel1_dis( void )
{
    switch (gui_info.channel_info)
    {
        case 1:
            LCD_Show_Image_Internal_Flash(85,55,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(145,55,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(205,55,46,22,gImage_channel_off,2024);
            break;

        case 2:
            LCD_Show_Image_Internal_Flash(85,55,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(145,55,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(205,55,46,22,gImage_channel_off,2024);
            break;

        case 3:
            LCD_Show_Image_Internal_Flash(85,55,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(145,55,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(205,55,46,22,gImage_channel_on,2024);
            break;

        case 4:
            LCD_Show_Image_Internal_Flash(85,55,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(145,55,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(205,55,46,22,gImage_channel_off,2024);
            break;

        case 5:
            LCD_Show_Image_Internal_Flash(85,55,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(145,55,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(205,55,46,22,gImage_channel_on,2024);
            break;

        default:
            break;
    }
}

void channel1_undis( void )
{
    LCD_Show_Image_Internal_Flash(85,55,46,22,gImage_channel_off,2024);
    LCD_Show_Image_Internal_Flash(145,55,46,22,gImage_channel_off,2024);
    LCD_Show_Image_Internal_Flash(205,55,46,22,gImage_channel_off,2024);
}

void channel2_dis( void )
{
    switch (gui_info.channel_info)
    {
        case 1:
            LCD_Show_Image_Internal_Flash(85,97,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(145,97,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(205,97,46,22,gImage_channel_off,2024);
            break;

        case 2:
            LCD_Show_Image_Internal_Flash(85,97,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(145,97,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(205,97,46,22,gImage_channel_off,2024);
            break;

        case 3:
            LCD_Show_Image_Internal_Flash(85,97,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(145,97,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(205,97,46,22,gImage_channel_on,2024);
            break;

        case 4:
            LCD_Show_Image_Internal_Flash(85,97,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(145,97,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(205,97,46,22,gImage_channel_off,2024);
            break;

        case 5:
            LCD_Show_Image_Internal_Flash(85,97,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(145,97,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(205,97,46,22,gImage_channel_on,2024);
            break;

        default:
            break;
    }
}

void channel2_undis( void )
{
    LCD_Show_Image_Internal_Flash(85,97,46,22,gImage_channel_off,2024);
    LCD_Show_Image_Internal_Flash(145,97,46,22,gImage_channel_off,2024);
    LCD_Show_Image_Internal_Flash(205,97,46,22,gImage_channel_off,2024);
}

void channel3_dis( void )
{
    switch (gui_info.channel_info)
    {
        case 1:
            LCD_Show_Image_Internal_Flash(85,138,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(145,138,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(205,138,46,22,gImage_channel_off,2024);
            break;

        case 2:
            LCD_Show_Image_Internal_Flash(85,138,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(145,138,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(205,138,46,22,gImage_channel_off,2024);
            break;

        case 3:
            LCD_Show_Image_Internal_Flash(85,138,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(145,138,46,22,gImage_channel_off,2024);
            LCD_Show_Image_Internal_Flash(205,138,46,22,gImage_channel_on,2024);
            break;

        case 4:
            LCD_Show_Image_Internal_Flash(85,138,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(145,138,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(205,138,46,22,gImage_channel_off,2024);
            break;

        case 5:
            LCD_Show_Image_Internal_Flash(85,138,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(145,138,46,22,gImage_channel_on,2024);
            LCD_Show_Image_Internal_Flash(205,138,46,22,gImage_channel_on,2024);
            break;

        default:
            break;
    }
}

void channel3_undis( void )
{
    LCD_Show_Image_Internal_Flash(85,138,46,22,gImage_channel_off,2024);
    LCD_Show_Image_Internal_Flash(145,138,46,22,gImage_channel_off,2024);
    LCD_Show_Image_Internal_Flash(205,138,46,22,gImage_channel_off,2024);
}

void icon_beat(uint8_t pic_code , uint8_t beat_switch )
{
    if( gui_beat.beat_start_flag == 1 )
    {
        delay_ms(1);
        gui_beat.beat_clear = 1 -  gui_beat.beat_clear;
        switch (pic_code)
        {
            case POWER_ICON:
                power_beat();
                break;

            case FAN_ICON:
                fan_beat();
                break;

            case MODE_ICON:
                mode_beat();
                break;

            case DRY_ICON:
                dry_beat();
                break;

            case TEMP1_ALARM:
                temp1_alarm_beat();
                break;

            case TEMP2_ALARM:
                temp2_alarm_beat();
                break;

            case TEMP3_ALARM:
                temp3_alarm_beat();
                break;

            default:
                break;
        }
    }

    gui_beat.beat_start_flag = 0; 
}

void icon_refresh( void )
{
    fan_dis();
    mode_dis();
    power_dis();
    temp_dis();
    alarm_icon_dis();
    sync_dis();
    dht11_dis();
    dry_dis();
}

void sync_dis( void )
{
    if( gui_info.sync_switch == 1 )
    {
        LCD_Show_Image_Internal_Flash(55,3,30,30,gImage_sync_on,1800);
    }else
    {
        LCD_Fill(55,3,85,33,BACK_COLOR);
    }
}

void slave_statu_update( void )
{
    if( gui_beat.beat_switch == 0 )
    {
        if( modbus.modbus_04_scan_flag == 1 )
        {
            get_slave_statu_04(&huart1);
            get_slave_statu_04(&huart2);
            //get_slave_statu_04(&huart3);
            modbus.modbus_04_scan_flag = 0;
        }
    } 
}

void GUI_Icon_Init( void )
{
     /*              connect icon                */
    LCD_Show_Image_Internal_Flash(13,3,30,30,gImage_connect_off,1740);

    /*              sync icon                */
    LCD_Show_Image_Internal_Flash(55,3,30,30,gImage_sync_on,1800);

    /*              temp alarm                */
    LCD_Show_Image_Internal_Flash(97,3,29,29,gImage_temp_alarm_red,1682);

    /*              temp && humidity                 */
    dht11_dis();
    PutChinese_12(17,255,"度",BACK_COLOR,POINT_COLOR);
    LCD_ShowString(295,16,12,12,12,"RH",POINT_COLOR,BACK_COLOR);
    
    /*            dry  channel  icon                */
    dry_dis();
    channel_dis();
    
    /*              temp  num                */
    temp_dis();
    PutChinese_12(60,300,"度",BACK_COLOR,POINT_COLOR);
    PutChinese_12(103,300,"度",BACK_COLOR,POINT_COLOR);
    PutChinese_12(144,300,"度",BACK_COLOR,POINT_COLOR);
    
    /*              power num %            */
    power_dis();
    LCD_Show_Image_Internal_Flash(25,193,32,32,gImage_power,2048);
    LCD_ShowChar(103,195,'%',24,POINT_COLOR,BACK_COLOR);
    
    /*              fan num                    */
    fan_dis();
    LCD_Show_Image_Internal_Flash(138,193,32,32,gImage_fan,2048);

    /*              mode num                 */
    mode_dis();
    LCD_Show_Image_Internal_Flash(233,193,42,31,gImage_mode,2604);
    
    /*              draw line                */
    LCD_DrawLine(1,36,320,36,GRAY);
    LCD_DrawLine(64,45,64,160,BROWN);
    LCD_DrawLine(20,179,300,179,GRAY);
}




