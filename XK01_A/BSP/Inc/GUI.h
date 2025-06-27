#ifndef __GUI_H_
#define __GUI_H_

#include "sys.h"
#include "ST7789V2.h"
#include "modbus_rtu.h"
#include "KEY_CRL.h"

#define MOED_1          1
#define MOED_2          2
#define MOED_3          3

#define LEVEL_0         0
#define LEVEL_1         1
#define LEVEL_2         2
#define LEVEL_3         3
#define LEVEL_4         4
#define LEVEL_5         5
#define LEVEL_6         6

#define BEAT_ON         1
#define BEAT_OFF        0

#define SYNC_ON         1
#define SYNC_OFF        0

#define CONNECT         1
#define UNCONNECT       0
/*      需要跳动显示的内容   */
// #define AC220_SET_ICON      1
// #define NTC_TEMP1_STR       11
// #define NTC_TEMP2_STR       12
// #define NTC_TEMP3_STR       13
// #define AC220_SWITCH_ICON   2
// #define LED_ICON            3
// #define FAN_ICON            4
// #define FAN_LEVEL_STR       41
// #define BAKE_ICON           5
// #define BAKE_POWER_STR      51
// #define BAKE_WIND_STR       52

#define POWER_ICON      1
#define FAN_ICON        2
#define MODE_ICON       3
#define DRY_ICON        4
#define TEMP1_ALARM     5
#define TEMP2_ALARM     6
#define TEMP3_ALARM     7

typedef struct  
{       
    uint8_t  fan_level;
    uint8_t  mode_allow;
    uint8_t  mode_info;
    uint8_t  power_val;       
    uint8_t  dry_info;
    uint8_t  channel_info;
    uint8_t  sync_switch;
    uint8_t  temp1_val;
    uint8_t  temp2_val;
    uint8_t  temp3_val;
    uint8_t  temp1_alarm_val;
    uint8_t  temp2_alarm_val;
    uint8_t  temp3_alarm_val;
    uint8_t  envir_temp;
    uint8_t  envir_humidity;

    uint8_t connect_on_flag1;
    uint8_t connect_on_flag2;
    uint8_t connect_on_flag3;
    uint8_t ac_switch_slave1;
    uint8_t ac_switch_slave2;
    uint8_t ac_switch_slave3;
}GUI_INFO;

typedef struct 
{
    uint8_t  beat_start_flag;
    uint8_t  beat_clear;

    uint8_t  beat_select;
    uint8_t  beat_switch; 
}GUI_BEAT;

extern GUI_INFO gui_info;
extern GUI_BEAT gui_beat;

void icon_beat(uint8_t pic_code , uint8_t beat_switch );
void dis_ac220_switch( uint8_t on_off );
void dis_ac220_set( uint8_t on_off );
void dry_dis( void );
void dry_check( void );
void channel_dis( void );
void channel_undis( void );
void channel1_dis( void );
void channel2_dis( void );
void channel3_dis( void );

void channel1_undis( void );
void channel2_undis( void );
void channel3_undis( void );
void dis_fan( uint8_t on_off );
void dis_bake_power( uint8_t on_off );
void dis_bake_windspeed( uint8_t on_off );
void GUI_Icon_Init( void );
void check_icon( uint8_t icon_select );
void GUI_Init( void );
void icon_refresh( void );
void sync_dis( void );
void slave_statu_update( void );
void tmep_judge( void );

void fan_dis( void );
void led_dis( void );
void mode_dis( void );
void mode_write( void );
void power_dis( void );
void temp_alarm_dis( void );
void temp_dis( void );
void connect_dis( void );
void mode_select( void );
void alarm_icon_dis( void );
void dht11_dis( void );
void channel_switch( void );

#endif

