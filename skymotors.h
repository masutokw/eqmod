
#ifndef SKYMOTORS_H_INCLUDED
#define SKYMOTORS_H_INCLUDED
#include <string.h>
#include <stdio.h>
   
  int set_position  (uint32_t value,uint8_t axis);
  int init_done (uint8_t axis);
  int set_motion_mode (uint32_t m_mode,uint8_t axis);
  int set_goto_target_increment (uint32_t value,uint8_t axis);
  int set_brake_point_increment (uint32_t value,uint8_t axis);  
  int set_goto_target (uint32_t value,uint8_t axis);
  int set_step_period (uint32_t value,uint8_t axis);
  int set_long_goto_step_period (uint32_t value,uint8_t axis);
  int set_brake_steps (uint32_t value,uint8_t axis);
  int start_motion(uint8_t axis);
  int stop_motion(uint8_t axis);
  int instant_stop(uint8_t axis);
  int set_sleep (uint8_t axis);
  int set_aux_switch (uint32_t value,uint8_t axis);
  int set_autoguide_speed (uint32_t value,uint8_t axis);
  int set_polar_LED (uint32_t value ,uint8_t val);

  int set_debug_flag (uint32_t value ,uint8_t axis);
  int get_cpr (uint32_t axis);
  int get_timer_int_frec (uint32_t frec);  ;
  int get_brake_steps (uint8_t axis); 
  int get_goto_target_position (uint8_t axis);
  int get_step_period (uint8_t axis);
  int get_position (uint8_t axis); 
  int get_increment (uint8_t axis);
  int get_brake_point (uint8_t axis);
  int get_status (uint8_t axis);
  int get_high_speed_ratio (uint8_t axis);
  int get_1x_tracking_period (uint8_t axis);
  int get_tele_axis_position (uint8_t axis);
  int get_motor_board_version (uint8_t axis);
  int get_PEC_period (uint8_t axis);
  int setcommand(char cmd, char chan, uint32_t value);
  int getcommand (char cmd,char chan);
  int getextended (uint32_t value,uint8_t axis);  
  #endif
