#define GET_BIT(byte, index) (((unsigned)(byte) >> (index)) & 1)
#include "skymotors.h"
#include <Arduino.h>

typedef bool boolt_2[2];
typedef uint32_t  uint32_t2[2];
typedef int32_t  int32_t2[2];
extern uint32_t2 position, goto_target, goto_target_inc, brakep_inc, step_lg_period, step_period, brake_steps, cpr;
extern int32_t2 dir ;
extern volatile uint32_t2 counter, target;
extern char response[20];
uint8_t gt_mode;
void toHex(uint32_t data, char* output, int len) {

  u8 b6, b5, b4, b3, b2, b1;
  data += 0x800000;
  b6 = (data & 0xF00000) >> 20;
  b5 = (data & 0xF0000) >> 16;
  b4 = (data & 0xF000) >> 12;
  b3 = (data & 0xF00) >> 8;
  b2 = (data & 0xF0) >> 4;
  b1 = (data & 0xF);


  if (len == 6) {
    sprintf(output, "%X%X%X%X%X%X", b2, b1, b4, b3, b6, b5);
  } else if (len == 4) {
    sprintf(output, "%X%X%X%X", b2, b1, b4, b3);
  } else if (len == 2) {
    sprintf(output, "%X%X", b2, b1);
  }
}

int set_position  (uint32_t value, uint8_t axis) {
  if (--axis == 2)  position[0] = position[1] = value;
  else  position[axis] = value;
  sprintf(response, "=\r");
 
  return 0 ;
}

int init_done (uint8_t axis) {
  sprintf(response, "=\r");
 
  return 0 ;
}

int set_motion_mode (uint32_t m_mode,uint8_t axis ) {
  axis--;
  if (GET_BIT(m_mode,0)) dir[axis]=-1;else dir[axis]=1;
//  if (GET_BIT(m_mode,1)) dir[1]=-1 ;else dir[1]=1;
  //if (GET_BIT(n_mode,2) dir[1]=-1:else dir[1]=1;
  gt_mode= (GET_BIT(m_mode,3)) ;
 
  sprintf(response, "=\r");
  Serial.println(dir[0]);
  return 0 ;
}

int set_goto_target_increment (uint32_t value, uint8_t axis) {
  if (--axis == 2) goto_target_inc[0] = goto_target_inc[1] = value;
  else   goto_target_inc[axis] = value;
  sprintf(response, "=\r");
 
  return 0;
}

int set_brake_point_increment (uint32_t br_inc, uint8_t axis) {
  if (--axis == 2)brakep_inc[0] = brakep_inc[1] = br_inc;
  else  brakep_inc[axis] = br_inc;
  sprintf(response, "=\r");
  
  return 0;
}
int set_goto_target (uint32_t value, uint8_t axis) {
  if (--axis == 2) goto_target[0] = goto_target[1] = value;
  else  goto_target[axis] = value;
  sprintf(response, "=\r");
 
  return 0;
}
int set_step_period (uint32_t value, uint8_t axis) {

  if (--axis == 2) target[0] = target[1] = value;
  else  target[axis] = value;
  sprintf(response, "=\r");
 
  return 0;
}

int set_long_goto_step_period (uint32_t value, uint8_t axis) {
  if (--axis == 2) step_lg_period[0] = step_lg_period[1] = value;
  else step_lg_period[axis] = value;
  sprintf(response, "=\r");
 
  return 0;
}

int set_brake_steps (uint32_t br_stp, uint8_t axis) {
  if (--axis == 2) brake_steps[0] = brake_steps[1] = br_stp;
  else brake_steps[axis] = br_stp;
  sprintf(response, "=\r");
  
  return 0;
}
int start_motion(uint8_t axis) {
  sprintf(response, "=\r");
  Serial.print("=\r");
  return 0;
}
int stop_motion(uint8_t axis) {
  sprintf(response, "=\r");
  axis--;
 if (axis==1){dir[axis]=1;target[axis]=0x0004DB;}
 else{ dir[0]=1;target[0]=0x0004DB;}
 
  return 0;
}
int instant_stop(uint8_t axis) {
  sprintf(response, "=\r");
  
  return 0;
}
int set_sleep (uint8_t axis) {
  sprintf(response, "=\r");
  
  return 0;
}

int set_aux_switch (uint32_t value, uint8_t axis)
{ sprintf(response, "=\r");
  
  return 0;
}
int set_autoguide_speed (uint32_t value, uint8_t axis) {
  sprintf(response, "=\r");
  
  return 0;
}

int set_polar_LED (uint32_t value , uint8_t val) {
  sprintf(response, "=\r");
  
  return 0;
}
int set_debug_flag (uint32_t value , uint8_t axis) {
  sprintf(response, "=\r");
 
  return 0;
}
int get_cpr (uint32_t axis) {
  sprintf(response, "=007869\r");
 
  return cpr[axis];
}
int get_timer_int_frec (uint32_t frec) {
  sprintf(response, "=A08501\r");

  return 100000;
}
int get_brake_steps (uint8_t axis) {
  sprintf(response, "50C300\r");

  return 0;
}
int get_goto_target_position (uint8_t axis) {
  sprintf(response, "=\r");
  return goto_target[axis] ;
}
int get_step_period (uint8_t axis) {
 char output[15] ;
  toHex(target[--axis],  output, 6) ;
  sprintf(response, "=%s\r", output);

  return step_period[axis];
}
int get_position (uint8_t axis)
{ char output[15] ;
  toHex(position[--axis],  output, 6) ;
  sprintf(response, "=%s\r", output);
  
return position[axis];
}
int get_increment (uint8_t axis) {
  sprintf(response, "=\r");
  return 0;
}
int get_brake_point (uint8_t axis) {
  sprintf(response, "=\r");
  return 0;
}
int get_status (uint8_t axis) {
  if (axis == 1)
    sprintf(response, "=101\r");
  else
    sprintf(response, "=501\r");
 
  return 0;
}
int get_high_speed_ratio (uint8_t axis) {
  sprintf(response, "=02\r");
   return 0;
}
int get_1x_tracking_period (uint8_t axis) {
  return 0;
}
int get_tele_axis_position (uint8_t axis) {
  char output[15] ;
  toHex(position[--axis],  output, 6) ;
  Serial.print(output);
  sprintf(response, "=%s\r", output);
  return position[axis];
}

int get_motor_board_version (uint8_t axis) {

  //Serial.print("=205100\r");
  sprintf(response, "=205100\r");

  return 0;
}
int get_PEC_period (uint8_t axis) {
  sprintf(response, "=205100\r");

  return 0;
}
int getextended(uint32_t value, uint8_t axis)
{
  sprintf(response, "=800000\r");
  ;
  return 0;
}

void getXcommand(uint8 chan)
{ sprintf(response, "=0\r");
 
}

int setcommand(char cmd, char chan, uint32_t value)
{
  switch (cmd)
  {
    case 'E': set_position(value, chan); break;
    case 'F': init_done(chan); break;
    case 'G': set_motion_mode(value,chan) ; break;
    case 'H': set_goto_target_increment(value, chan); break;
    case 'M': set_brake_point_increment(value, chan) ; break;
    case 'S': set_goto_target(value, chan); break;
    case 'I': set_step_period(value, chan) ; break;
    case 'T': set_long_goto_step_period(value, chan); break;
    case 'U': set_brake_steps(value, chan); break;
    case 'J': start_motion(chan); break;
    case 'K': stop_motion(chan); break;
    case 'L': instant_stop(chan); break;
    case 'B': set_sleep(chan); break;
    case 'O': set_aux_switch(value, chan); break;
    case 'P': set_autoguide_speed(value, chan); break;
    case 'V': set_polar_LED(value, chan); break;
    case 'z': set_debug_flag(value, chan); break;
    case 'q': getextended(value, chan); break;
    case 'X': getXcommand(chan); break;
    default: break;
    
  }
  return 0;
}

int getcommand (char cmd, char chan)
{
  switch (cmd) {
    case 'a' : get_cpr(chan); break;
    case 'b': get_timer_int_frec(chan); break;
    case 'c': get_brake_steps(chan); break;
    case 'h': get_goto_target_position(chan); break;
    case 'i': get_step_period(chan); break;
    case 'j': get_position(chan); break;
    case 'k': get_increment(chan); break;
    case 'm': get_brake_point(chan); break;
    case 'f': get_status(chan); break;
    case 'g': get_high_speed_ratio(chan); break;
    case 'D' : get_1x_tracking_period(chan); break;
    case 'd': get_tele_axis_position(chan); break;
    case 'e': get_motor_board_version(chan); break;
    case 's' : get_PEC_period(chan); break;
    default: break;
  }


  return 0;


}
