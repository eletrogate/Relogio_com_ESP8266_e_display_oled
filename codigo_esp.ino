#include <Wire.h>
#include "SSD1306Wire.h"

SSD1306Wire  display(0x3c, D5, D6);
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Nome da sua rede WIFI"
#define STAPSK  "Senha da sua rede WIFI"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiUDP udp;
NTPClient ntp(udp, "b.ntp.br" , -3 * 3600, 60000); // mude o fuso horário de acordo com a região onde você está


String hora;//armazena as horas

void setup()
{
   Serial.begin(115200);
   display.init();
   display.flipScreenVertically();


  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);//Conecta ao WiFi.
   delay(2000);//Espera a conexão.
   
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));




   ntp.begin();
   ntp.forceUpdate();
}

 void telainicial()
{
  //limpa o display
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  
  display.setFont(ArialMT_Plain_16);//escolhe a fonte 
  display.drawString(63, 26, hora); // escreve as horas no diplay
  display.display();
}


void loop()
{
   hora = ntp.getFormattedTime();
   Serial.println(hora);

 telainicial();
  

   delay(1000);
}