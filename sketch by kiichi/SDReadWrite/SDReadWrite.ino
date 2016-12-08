/*
  SD card read/write
 
 This example shows how to read and write data to and from an SD card file   
 The circuit:
 * SD card attached to SPI bus as follows:
 ** UNO:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 4 (CS pin can be changed)
  and pin #10 (SS) must be an output
 ** Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 4 (CS pin can be changed)
  and pin #52 (SS) must be an output
 ** Leonardo: Connect to hardware SPI via the ICSP header
 
 created   Nov 2010  by David A. Mellis
 modified 9 Apr 2012  by Tom Igoe
 
 This example code is in the public domain.
   
 */

#include <Bridge.h>
#include <Console.h>
#include <FileIO.h>

void setup()
{
  Bridge.begin();
  Console.begin();
  while( !Console );


  Console.print("Initializing SD card...");
   
  if (!FileSystem.begin()) {
    Console.println("initialization failed!");
    return;
  }
  Console.println("initialization done.");
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File myFile = FileSystem.open("/mnt/sd/test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Console.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
  // close the file:
    myFile.close();
    Console.println("done.");
  } else {
    // if the file didn't open, print an error:
    Console.println("error opening test.txt");
  }
  
  // re-open the file for reading:
  File myFile2 = FileSystem.open("/mnt/sd/test.txt", FILE_READ);
  if (myFile2) {
    Console.println("test.txt:");
    
    // read from the file until there's nothing else in it:
    while (myFile2.available()) {
      Console.write(myFile2.read());
    }
    // close the file:
    myFile2.close();
  } else {
    // if the file didn't open, print an error:
    Console.println("error opening test.txt");
  }
}

void loop()
{
  // nothing happens after setup
}
