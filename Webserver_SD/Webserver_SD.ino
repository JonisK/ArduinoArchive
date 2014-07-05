//zoomkat 2/26/13
//SD server slider test code
//open serial monitor to see what the arduino receives
//browser address will look like http://192.168.1.102:84/servosld.htm when submited
//for use with W5100 based ethernet shields
//put the servosld.htm, slider.js, bluev_sl.gif,
//and bluev_bg.gif on the SD card
//download flies at:
// http://web.comporium.net/~shb/pix/servosld.htm
// http://web.comporium.net/~shb/pix/slider.js
// http://web.comporium.net/~shb/pix/bluev_bg.gif
// http://web.comporium.net/~shb/pix/bluev_sl.gif
// 

#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>


String readString, pos;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 1, 102 }; // ip in lan
byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(84); //server port

//////////////////////

void setup(){

  Serial.begin(9600);

  // disable w5100 while setting up SD
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  Serial.print("Starting SD..");
  if(!SD.begin(4)) Serial.println("failed");
  else Serial.println("ok");

  Ethernet.begin(mac, ip, gateway, gateway, subnet);

  //delay(2000);
  server.begin();
  Serial.println("Ready");


}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string 
          readString += c; 
          //Serial.print(c);
        } 
        //if HTTP request has ended
        if (c == '\n') {

          ///////////////
          Serial.println(readString); //print to serial monitor for debuging

            //select proper header for file to be sent to browser

          client.println("HTTP/1.1 200 OK"); //send new page
          if(readString.indexOf("servosld") >=0) {
            client.println("Content-Type: text/html");
            client.println(); 
          }

          if(readString.indexOf("slider") >=0) {
            client.println("Content-Type: application/x-javascript");
            client.println(); 
          }

          if(readString.indexOf("bluev") >=0) {
            client.println("Content-Type: image/gif");
            client.println(); 
          }

          //select file to send to browser
          if(readString.indexOf("servosld") >=0) {
            File myFile = SD.open("SERVOSLD.HTM");
            if (myFile) {

              byte clientBuf[64];
              int clientCount = 0;              

              while (myFile.available()) 
              {
                clientBuf[clientCount] = myFile.read();
                clientCount++;

                if(clientCount > 63)
                {
                  client.write(clientBuf,64);
                  clientCount = 0;
                }                
              }
              if(clientCount > 0) client.write(clientBuf,clientCount);            
              myFile.close();
            }
          }

          if(readString.indexOf("slider") >=0) {
            File myFile = SD.open("slider.js");
            if (myFile) {

              byte clientBuf[64];
              int clientCount = 0;              

              while (myFile.available()) 
              {
                clientBuf[clientCount] = myFile.read();
                clientCount++;

                if(clientCount > 63)
                {
                  client.write(clientBuf,64);
                  clientCount = 0;
                }                
              }
              if(clientCount > 0) client.write(clientBuf,clientCount); 
              myFile.close();
            }
          }

          if(readString.indexOf("bluev_sl") >=0) {
            File myFile = SD.open("bluev_sl.gif");
            if (myFile) {

              byte clientBuf[64];
              int clientCount = 0;              

              while (myFile.available()) 
              {
                clientBuf[clientCount] = myFile.read();
                clientCount++;

                if(clientCount > 63)
                {
                  client.write(clientBuf,64);
                  clientCount = 0;
                }                
              }
              if(clientCount > 0) client.write(clientBuf,clientCount); 
              myFile.close();
            }
          }

          if(readString.indexOf("bluev_bg") >=0) {
            File myFile = SD.open("bluev_bg.gif");
            if (myFile) {

              byte clientBuf[64];
              int clientCount = 0;              

              while (myFile.available()) 
              {
                clientBuf[clientCount] = myFile.read();
                clientCount++;

                if(clientCount > 63)
                {
                  client.write(clientBuf,64);
                  clientCount = 0;
                }                
              }
              if(clientCount > 0) client.write(clientBuf,clientCount); 
              myFile.close();
            }
          }

          delay(1);
          //stopping client
          client.stop();

          //process GET string request from client and and position servo

          pos = readString.substring(8, 12); //get the first four characters         
          //Serial.println(pos);
          int n = pos.toInt();  //convert readString into a number   
          Serial.println(n); 
          Serial.println();

          if(readString.indexOf("?0") >0) myservoa.writeMicroseconds(n);
          if(readString.indexOf("?1") >0) myservob.writeMicroseconds(n);
          if(readString.indexOf("?2") >0) myservoc.writeMicroseconds(n);
          if(readString.indexOf("?3") >0) myservod.writeMicroseconds(n);
          if(readString.indexOf("?4") >0) myservoe.writeMicroseconds(n);
          if(readString.indexOf("?5") >0) myservof.writeMicroseconds(n);
          if(readString.indexOf("?6") >0) myservog.writeMicroseconds(n);
          //only seven servo pins, so back to myservoa for testing
          if(readString.indexOf("?7") >0) myservoa.writeMicroseconds(n);

          //clearing string for next read
          readString="";
          pos="";
        }
      }
    }
  } 
}

