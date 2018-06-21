/* loadSPIFlash_AS7265X_Dragonfly.ino
 *  
Sketch by Kris Winer January 14, 2018

License: Use this sketch any way you choose; if you like it, buy me a beer sometime

Purpose: Reads 16 MByte SPI NOR flash on LoRa SensorTile and reconstructs bytes into 
spreadsheet-readable scaled sensor data

Sketch takes advantage of the SPI.beginTransaction/SPI.EndTransaction protocol for efficiency
and maximum speed.

Sketch based on the work of Pete (El Supremo) as follows:
 * Copyright (c) 2014, Pete (El Supremo), el_supremo@shaw.ca
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 */

#include <SPI.h>
#include <FS.h>
#include "SPIFlash.h"

// Highest page number is 0xFFFF = 65535 for 128 Mbit flash
// Highest page number is 0x7FFF = 32767 for  64 Mbit flash
// Highest page number is 0x0FFF =  4095 for   8 Mbit flash
// Highest page number is 0x07FF =  2047 for   4 Mbit flash
uint16_t max_page_number = 0x07FF;
unsigned char flashPage[256];
unsigned char r_page[256];
uint16_t page_number = 0, numbytes = 0;

#define csPin 10
#define myLed 26

SPIFlash SPIFlash(csPin);

File file;

void setup(void)
{ 
  DOSFS.begin();
  delay(1000);

  file = DOSFS.open("/AS7265.2.fw", "r"); 

  // Set up LED pin
  pinMode (myLed, OUTPUT);
  digitalWrite(myLed, HIGH);
  delay(100);
 
  Serial.begin(115200);
  delay(4000);
  Serial.println("Serial enabled!");

  if(file)
  {
    Serial.println("File Open!");
  } 
  else
  {
    Serial.println("File Open Failed!");
    while(1) { };
  }

  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);

  // check SPI Flash ID
  SPIFlash.SPIFlashinit();
  SPIFlash.powerUp();
  SPIFlash.getChipID();

  SPIFlash.flash_chip_erase(true); // erase the SPI flash before writing firmware
  delay(100);
  

  for (page_number = 0; page_number < 2048; page_number++)
  {
  numbytes = file.read(flashPage, 256); // 256 bytes per page, 2047 pages
  Serial.print("first two bytes: "); Serial.print("0x"); Serial.print(flashPage[0], HEX); Serial.print("  0x"); Serial.println(flashPage[1], HEX);
  Serial.print("Number of bytes = "); Serial.println(numbytes);  // print number of bytes read

  SPIFlash.flash_page_program(flashPage, page_number);
  Serial.print("Wrote flash page: "); Serial.println(page_number);
  digitalWrite(myLed, LOW); delay(1); digitalWrite(myLed, HIGH); // indicate when flash page is written
  }

  
  // read AS7265X SPI flash
  for(page_number = 0; page_number < 2048; page_number++)  
  {

  //  Serial.print("Read Page 0x"); Serial.println(page_number, HEX);
  SPIFlash.flash_read_pages(r_page, page_number, 1);
      
  for(uint16_t i = 0; i < 256; i++) 
  {
  Serial.print(" 0x"); Serial.print(r_page[i], HEX);
  if (i % 16==0) Serial.println();
  }
  
  Serial.println("");
  }

}

void loop(void)
{
}


