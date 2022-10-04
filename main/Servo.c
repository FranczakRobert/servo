#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <sdkconfig.h>
#include <driver/gpio.h>
#include <driver/ledc.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define pinServo 18
#define ServoMsMin 0.06
#define ServoMsMax 2.1
#define ServoMsAvg ((ServoMsMax-ServoMsMin)/2.0)

void servoDeg0() {
  ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .freq_hz          = 50,  
        .clk_cfg          = LEDC_AUTO_CLK
  };
  ledc_timer_config(&ledc_timer);
  ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = pinServo,
        .duty           = 0,
        .hpoint         = 0
  };
  ledc_channel_config(&ledc_channel);  
  int duty = (int)(100.0*(ServoMsMin/20.0)*81.91);
  printf("%fms, duty = %f%% -> %d\n",ServoMsMin, 100.0*(ServoMsMin/20.0), duty);
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);  
  vTaskDelay( 2000/portTICK_PERIOD_MS ); 
  ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
}

void servoDeg90() {
  ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .freq_hz          = 50,  
        .clk_cfg          = LEDC_AUTO_CLK
  };
  ledc_timer_config(&ledc_timer);
  ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = pinServo,
        .duty           = 0,
        .hpoint         = 0
  };
  ledc_channel_config(&ledc_channel);  
  int duty = (int)(100.0*(ServoMsAvg/20.0)*81.91);
  printf("%fms, duty = %f%% -> %d\n",ServoMsAvg, 100.0*(ServoMsAvg/20.0), duty);
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);  
  vTaskDelay( 2000/portTICK_PERIOD_MS ); 
  ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
}

void servoDeg180() {
  ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .freq_hz          = 50,  
        .clk_cfg          = LEDC_AUTO_CLK
  };
  ledc_timer_config(&ledc_timer);
  ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = pinServo,
        .duty           = 0, 
        .hpoint         = 0
  };
  ledc_channel_config(&ledc_channel);  
  int duty = (int)(100.0*(ServoMsMax/20.0)*81.91);
  printf("%fms, duty = %f%% -> %d\n",ServoMsMax, 100.0*(ServoMsMax/20.0), duty);
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);  
  vTaskDelay( 2000/portTICK_PERIOD_MS ); 
  ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
}

void manualServo() {
  printf("  0 degree:");
  servoDeg0();
  printf(" 90 degree:");
  servoDeg90();
  printf("180 degree:");
  servoDeg180();
  printf(" 90 degree:");
  servoDeg90();
}

void app_main(void)
{ 
  printf("EP10 : LEDC&Servo Motor\n");
  while (1) {
    manualServo();
  }
}