/* Web_Image.pde - example sketch for Webduino library */
/* For webduino version 1.2 */

/* DISCLAIMER -- the Webduino server can only handle one web connection
 * at a time.  Because of this, loading the root page on this sketch may
 * not correctly show the LED icon if the browser starts requesting that
 * picture before the page has finished loading.
 *
 * This problem should be reduced greatly once the Ethernet library
 * has been modified to do proper packet buffering.  With the library
 * in Arduino 15, each character is sent in its own TCP/IP packet.
 * This is very inefficient and means that it takes much longer to
 * send a web page than it should.  When this bug is fixed, the web
 * server will have sent its last data and closed the connection by
 * the time the client reads the HTML, so it's ready to handle the
 * image request.
 */

#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "SD.h"

// CHANGE THIS TO YOUR OWN UNIQUE VALUE
static uint8_t mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
static uint8_t ip[] = { 192, 168, 0, 2 };

int var = 60;

Sd2Card card;
SdVolume volume;
SdFile root;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = 4; 


WebServer webserver("", 80);

/* The default page just returns HTML to show the image */
void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  if (type == WebServer::POST)
  {
    // ignore POST data
    server.httpFail();
    return;
  }

  /* for a GET or HEAD, send the standard "it's all OK headers" */
  server.httpSuccess();

  /* we don't output the body for a HEAD request */
  if (type == WebServer::GET)
  {
    /* store the HTML in program memory using the P macro */
    P(message) = 
      "<html><head><title>Webduino Image Example</title>"
      "<body>"
      "<h2>LED Image</h2>"
      "<img src='favicon22.ico' width=256 height=256>"
      "</body></html>";

    server.printP(message);
  }
}

void imageCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  /* this data was taken from a PNG file that was converted to a C data structure
   * by running it through the directfb-csource application. */
 
  if (type == WebServer::POST)
  {
    // ignore POST data
    server.httpFail();
    return;
  }

  /* for a GET or HEAD, send the standard "it's all OK headers" but identify our data as a PNG file */
  server.httpSuccess("image/ico");

  /* we don't output the body for a HEAD request */
  if (type == WebServer::GET)
  {

    
    File myFile = SD.open("favicon22.ico");
            if (myFile) {

              byte clientBuf[64];
              int clientCount = 0;              

              while (myFile.available()) 
              {
                clientBuf[clientCount] = myFile.read();
                clientCount++;

                if(clientCount > 63)
                {
                  server.write(clientBuf,64);
                  clientCount = 0;
                }                
              }
              if(clientCount > 0) server.write(clientBuf,clientCount); 
              myFile.close();
            }
  }
}

void setup()
{
   Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // setup the Ehternet library to talk to the Wiznet board
  Ethernet.begin(mac, ip);

  /* register our default command (activated with the request of
   * http://x.x.x.x/ */
  webserver.setDefaultCommand(&defaultCmd);

  /* register our image output command */
  webserver.addCommand("favicon22.ico", &imageCmd);

  /* start the server to wait for connections */
  webserver.begin();
  pinMode(10, OUTPUT);     // change this to 53 on a mega


  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
   Serial.println("Wiring is correct and a card is present."); 
  }
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }
}

void loop()
{
  // process incoming connections one at a time forever
  webserver.processConnection();
}
