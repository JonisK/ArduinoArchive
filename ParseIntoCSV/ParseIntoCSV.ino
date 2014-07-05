/*
 *  This example reads a simple CSV, comma-separated values, file.
 *  Each line of the file has three values, a long and two floats.
 */
#include <SdFat.h>

enum {TIME, ACC, MAG, WRITE, FAILURE};
	
uint8_t task;
uint8_t e;
uint8_t crlf;	
	
uint32_t time_current;
uint8_t counter = 0, overflow = 0;
uint8_t time_1, time_2, time_3;	
	
int16_t acc_x, acc_y, acc_z;
uint8_t acc_1, acc_2, acc_3, acc_4, acc_5, acc_6;
uint8_t ACC_present = 0;

int16_t mag_x, mag_y, mag_z;
uint8_t mag_1, mag_2, mag_3, mag_4, mag_5, mag_6;
uint8_t MAG_present = 0;

char IN_fileName[] = "PARSE.LOG";
char ACC_fileName[] = "ACC.CSV";
char MAG_fileName[] = "MAG.CSV";

// SD chip select pin
const uint8_t chipSelect = SS;

// file system object
SdFat sd;

// create or open and truncate output file
ofstream sdouta(ACC_fileName);
ofstream sdoutm(MAG_fileName);

// open input file
ifstream sdin(IN_fileName);

// create Serial stream
ArduinoOutStream cout(Serial);

//------------------------------------------------------------------------------
// store error strings in flash to save RAM
#define error(s) sd.errorHalt_P(PSTR(s))
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  while (!Serial) {} // wait for Leonardo
  cout << pstr("This is the Parse Module");
//   while (Serial.read() <= 0) {}
  
  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance
  if (!sd.begin(chipSelect, SPI_FULL_SPEED)) sd.initErrorHalt();
  

	
	// check for any errors
// 	if (!sdouta) error("writeFile");
// 	
// 	
// 	if (!sdoutm) error("writeFile");
	
	
	
	// check for open error
	if (!sdin.is_open()) error("open");
	
	// first read a character
	sdin >> e;

	cout << pstr("Initialization complete");
}
void loop() {
	
	
	// decide what to do with that character. State machine
	switch (task) {
		case TIME:
			if ((e>>4)!=0x09) {
				// our assumption was wrong
				task = FAILURE;
				break;
			}
			// we are now fairly sure to have a TIME value here
			if ((e & 0x0F ) != ((++counter) & 0x0F )) {
				// we seem to have missed at least one iteration of the logger
				// let's see how much we have missed
				overflow += (e & 0x0F) - ((counter - 1) & 0x0F);
			}
			// read in the following 3 Bytes, separated by CRLFs
			sdin >> crlf >> time_1 >> crlf >> time_2 >> crlf >> time_3 >> crlf;
			
			// now we now the time of our sample 
			time_current = (time_1 << 16) | (time_2 << 8) | time_3;
			
			// let's move on to the ACC state
			task = ACC;
			// but not without making sure a new character is read at first
			sdin >> e;
			break;
			
		case ACC:
			if (( e >> 4 ) != 0x0A) {
				// our assumption was wrong
				// maybe we have a MAG reading here?
				if (( e >> 4 ) == 0x0E) {
					// yes, it's a MAG!
					task == MAG;
					break;
				}
				// it's not a MAG. So we give up
				task = FAILURE;
				break;
			}
			// We have an ACC reading!
			ACC_present = 1;
			sdin >> crlf >> acc_1 >> crlf >> acc_2 >> crlf >> acc_3 >> crlf >> acc_4 >> crlf >> acc_5 >> crlf >> acc_6 >> crlf;
			acc_x = acc_1 | (acc_2 << 8);
			acc_y = acc_3 | (acc_4 << 8);
			acc_z = acc_5 | (acc_6 << 8);
			
			// let's move on to the MAG state
			task = MAG;
			// but not without making sure a new character is read at first
			sdin >> e;
			break;
			
		case MAG:
			if (( e >> 4 ) != 0x0E) {
				// our assumption was wrong
				// we came from an ACC reading
				// most probably our sample is over and we should write it
				task = WRITE;
				break;
			}
			// We have a MAG reading!
			MAG_present = 1;
			sdin >> crlf >> mag_1 >> crlf >> mag_2 >> crlf >> mag_3 >> crlf >> mag_4 >> crlf >> mag_5 >> crlf >> mag_6 >> crlf;
			mag_x = mag_2 | (mag_1 << 8);
			mag_y = mag_4 | (mag_3 << 8);
			mag_z = mag_6 | (mag_5 << 8);
			
			// let's move on to the MAG state
			task = MAG;
			// but not without making sure a new character is read at first
			sdin >> e;
			break;
			
		case WRITE:
			if (ACC_present) {
				sdouta << time_current << "," << acc_x << "," << acc_y << "," << acc_z << overflow << endl << flush;
				if (!sdouta) error("writeACCFile");
				ACC_present = 0;
			}
			if (MAG_present) {
				sdoutm << time_current << "," << mag_x << "," << mag_y << "," << mag_z << overflow << endl << flush;
				if (!sdoutm) error("writeMAGFile");
				MAG_present = 0;
			}
			task = TIME;
			break;
		case FAILURE:
			// somehow we got stuck
			// try to find the init code of TIME again
			end();
			break;
	}
	
}

void end() {
	// Ending our program
	sdouta.close();
	sdoutm.close();
		
	cout << endl << "\nDone!" << endl;
}