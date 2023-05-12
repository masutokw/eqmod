#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
typedef uint32_t  uint32_t2[2];
typedef int32_t  int32_t2[2];
volatile uint32_t2  position;
typedef bool boolt_2[2];
boolt_2 track,sense,runing,block;
uint32_t2 goto_target, goto_target_inc, brakep_inc, step_lg_period, step_period, brake_steps, cpr;
int32_t2 dir = {1, 0};
#include "skymotors.h"
#include "cmd/command.c"
volatile uint32_t2 counter, target;
volatile uint64_t counter1;
#define TIMER_FREC (1/5000000.0)*50.0
#include "wifipass.h"

#define LED 2  //On board LED
#ifndef STASSID
#define STASSID "MYWIFI"
#define STAPSK  "MYPASSS"
#endif
char response[20];
unsigned int localPort = 11880;      // local port to listen on

// buffers for receiving and sending data
char udp_input_buffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "=\r";       // a string to send back

WiFiUDP Udp;
bool udp_mode = true;

//=======================================================================
void IRAM_ATTR onTimerISR() {
  if (!counter[1] )digitalWrite(LED, 1);
  if (!counter[0] )digitalWrite(D3, 1);
  if (++counter[0] >= target[0]) {
    counter[0] = 0;
    if (dir[0]) {
      position[0] += dir[0];
      digitalWrite(D3, 0);
    }
  }
  if (++counter[1] >= target[1]) {
    counter[1] = 0;
    if (dir[1]) {
      position[1] += dir[1];
      digitalWrite(LED, 0);
    }
  };
  counter1++;
}
void udp_setup(void)
{ WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}

void setup()
{
  Serial.begin(115200);
  // Serial.println("");
  if (udp_mode) udp_setup();
  pinMode(LED, OUTPUT);
  pinMode(D3, OUTPUT);
  target[0] = 0x0004DB;
  dir[0]=1;dir[1]=0;
  target[1] = 0x0004DB;
  //Initialize Ticker every 0.5s
  timer1_attachInterrupt(onTimerISR);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(50); //10 us
}
float calticks(float freq)
{ float period = 1000000.0 / freq;
  float frac ;
  frac = modf(period, &period);
  return frac;
}
void loop()
{ char buff[200];
  String input;
  int tmp = 0;
  bool cmode = false;
  int udp_packet_len, n;
  /* if (Serial.available())
    {
     char n = 0;
     delay(2);
     while (Serial.available())  buff[n++] = (char) Serial.read() ;
     buff[n] = 0;
     input = String(buff+1);
     ticks=1000000/ input.toInt();
      if (buff[0]=='a')
     {target1 = ticks ;counter1=0;}
     else if (buff[0]=='b')
      {target2 = ticks ;counter2=0;}
     Serial.println(target1);
     Serial.println(1000000/ticks);
     Serial.println(1000000/ticks-input.toInt());

    }*/
  if  (!udp_mode)  {
    if (Serial.available()) {
      int n = 0;
      delay(50);
      while (Serial.available())  buff[n++] = (char) Serial.read() ;
      buff[n] = 0;
      //  input = String(buff);
      //  Serial.print("=\r");
      //  Serial.println(input);
      //   Serial.println(n);
      response[0] = 0;
      tmp = command(buff);
      Serial.println(response);

    }
  } else {
    while (true) {
     delay(30);
      udp_packet_len = Udp.parsePacket();
      if (udp_packet_len) {

        response[0] = 0;
        n = Udp.read(udp_input_buffer, UDP_TX_PACKET_MAX_SIZE);
        udp_input_buffer[n - 1] = 13;
        udp_input_buffer[n] = 0;
        tmp = command(udp_input_buffer);

        // reply udp client
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(response);
        Udp.endPacket();
           Serial.println( "  ");
        Serial.print( udp_packet_len);
        Serial.print( "  ");
        Serial.print(udp_input_buffer);
        Serial.print("->  ");
        Serial.print(response);
      }
    }
  }

}
