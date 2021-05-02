
#include "LedControl.h"

/*
 pin 12 DataIn 
 pin 11 CLK 
 pin 10 CS
 */
LedControl lc=LedControl(12,11,10,2);
int counter = 0;
int value = 0;
byte buffer[16] = { 
  0 };
int lastvalue = 0;

void setup() {
  //inicio y apagado del led
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  //intensidad del led
  lc.setIntensity(0,4);
  lc.setIntensity(1,4);
  //limpiar pantalla led
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  Serial.begin(115200);
}

//setear columnas
void Set(int index, int value)
{
  int device = index / 8; //calcular dispositivo
  int row = index - (device * 8); //calcular fila
  int leds = map(value, 0, 255, 0, 9); //mapa de valores de los leds.
  //display data
  switch (leds)
  {
  case 0:
    lc.setRow(device,row, 0x00);
    return;
  case 1:
    lc.setRow(device,row, 0x80);
    return;
  case 2:
    lc.setRow(device,row, 0xc0);
    return;
  case 3:
    lc.setRow(device,row, 0xe0);
    return;
  case 4:
    lc.setRow(device,row, 0xf0);
    return;
  case 5:
    lc.setRow(device,row, 0xf8);
    return;
  case 6:
    lc.setRow(device,row, 0xfc);
    return;
  case 7:
    lc.setRow(device,row, 0xfe);
    return;
  case 8:
    lc.setRow(device,row, 0xff);
    return;
  }
}

void loop()
{
  if (Serial.available() >= 15)
  {
    value = Serial.read();
    Set(counter, value);
    counter++;
    if (counter > 15) counter = 0;
  }
}
