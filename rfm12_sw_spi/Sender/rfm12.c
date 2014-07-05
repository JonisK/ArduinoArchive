/**
 * @file rfm12.c
 * 
 * Software interface to RFM12-868MHz-Band FSK Radio
 * Module offered by e.g. Pollin Electronic
 *
 */

#ifdef __16f628a
  #include <pic16f628a.h>
#endif
#ifdef __16f88
  #include <pic16f88.h>
#endif

#include <macros.h>
#include <delay.h>
#include <eeprom.h>
#include <rfm12.h>


/**
 * proto types intern
 */
unsigned char rfm12_wait(unsigned int tout);
void rfm12_init_tx(void);
void rfm12_init_rx(void);
unsigned int rfm12_spi16(unsigned int dout);


/**
 * @fn void rfm12_init
 * @brief initializes the rfm12 radio module
 * @brief 868,3MHz,4,8kbps, 0db power
 * @param 
 */
void rfm12_init(void){
  unsigned int d;

  // set port direction
  nSEL_OUT();
  SDI_IN();
  SDO_OUT();
  SCK_OUT();
  nIRQ_IN();

  // default signals
  nSEL=1;
  SDO=1;
  SCK=0;

  d=rfm12_spi16(0x80e7);          // El, Ef, 11.5pF, 868MHz band
  d=rfm12_spi16(0x82d9);          // !er, !ebb, Et, Es, Ex, !eb, !ew, Dc
  d=rfm12_spi16(0xa67c);          // 434,15MHz/868,3MHz
  d=rfm12_spi16(0xc647);          // 4,8kbps
  d=rfm12_spi16(0x94a0);          // Vdi, fast, 134kHz, 0db,-103dbm
  d=rfm12_spi16(0xc2ac);          // Al, !ml, Dig, Dqd4
  d=rfm12_spi16(0xca80);          // fifo8, sync, !ff, Dr
  d=rfm12_spi16(0xca83);          // fifo8, sync, !ff, Dr
  d=rfm12_spi16(0xc483);          // @pwr, no restrict, !st, !fi, Oe, En
  
  d=rfm12_spi16(0x9850);          // 90kHz, power - 0db
  
  d=rfm12_spi16(0xe000);          // not used (wake-up timer cmd)
  d=rfm12_spi16(0xc800);          // not used (low duty-cycle cmd)
  
  d=rfm12_spi16(0xc000);          // 1MHz, 2.2V (low bat detector and clk div)
  d=rfm12_spi16(0x0000);          // read status word to clear fifos
}


/**
 * @fn unsigned char rfm12_snd_msg
 * @brief send a message
 * @param msg message to be sent
 * @param len length of the message in bytes
 */
unsigned char rfm12_snd_msg(unsigned char *msg,int len){
  unsigned int d,chksum=0;
  unsigned char i;

  d=rfm12_spi16(0x8238);          // Tx on
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;
  d=rfm12_spi16(0xb8aa);          // Preamble
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;
  d=rfm12_spi16(0xb8aa);          // Preamble
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;
  d=rfm12_spi16(0xb8aa);          // Preamble
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;
  d=rfm12_spi16(0xb82d);          // Sync hi-byte
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;
  d=rfm12_spi16(0xb8d4);          // Sync low-byte
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;

  // message in tx fifo
  for(i=0;i<len;i++){
    d=rfm12_spi16(0xb800|(msg[i]));
    if(0==rfm12_wait(RFM12_TOUT))
      return 0;
    chksum+=msg[i];
  }
  chksum&=0x0ff;

  // checksum in tx fifo
  d=rfm12_spi16(0xb800|(chksum));
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;

  d=rfm12_spi16(0xb8aa);          // dummy bytes
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;
  d=rfm12_spi16(0xb8aa);
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;
  d=rfm12_spi16(0xb8aa);
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;
  
  d=rfm12_spi16(0x8208);          // Tx off
  
  RB5=1;
  delay_ms(100);
  RB5=0;
  return 1;
}


/**
 * @fn unsigned char rfm12_rcv_msg
 * @brief receive a message
 * @param msg message that has been received
 * @param len length of the message in bytes
 */
unsigned char rfm12_rcv_msg(unsigned char *msg,int len){
  unsigned int d, chksum=0;
  unsigned char i;

  nSEL=0;
  
  // read data bytes
  for(i=0;i<len;i++){
    d=rfm12_spi16(0xb000);
    if(0==rfm12_wait(RFM12_TOUT))
      return 0; 
    msg[i]=(unsigned char)d;
    chksum+=msg[i];
  }
  // read checksum
  d=rfm12_spi16(0xb000);
  if(0==rfm12_wait(RFM12_TOUT))
    return 0;
  
  chksum&=0x0ff;
  if(chksum!=(unsigned char)d){   // last byte is checksum
    RB7=1;                        // checksum error!!!
  }
  rfm12_dis_rx();
  delay_us(5);
  rfm12_ena_rx();
  //eeprom_write(0,msg,5);
  //eeprom_write(5,(unsigned char *)&d,1);
  //eeprom_write(6,(unsigned char *)&chksum,1);
}



/**
 * @fn void rfm12_ena_rx
 * @brief enable the rx module
 * @param
 */
void rfm12_ena_rx(void){
  nSEL=0;
  rfm12_spi16(0xca80);
  rfm12_spi16(0xca83);
  rfm12_spi16(0x82c8);
}


/**
 * @fn void rfm12_dis_rx
 * @brief disable the rx module
 * @param
 */
void rfm12_dis_rx(void){
  rfm12_spi16(0x8208);
  nSEL=1;
}



/**
 * @fn void rfm12_wait
 * @brief waits until tx/rx fifo is ready
 * @param tout Timeout value
 */
unsigned char rfm12_wait(unsigned int tout){
  unsigned int to=0;

  nSEL=0;
  do{
    to++;
    delay_us(100);
  }while((!SDI)&&(to<tout));
  
  if(to<tout){
    return 1;
  }else{
    return 0; 
  }
}


/**
 * @fn void rfm12_spi16
 * @brief write or read a data word by software SPI
 * @param dout data value
 */
unsigned int rfm12_spi16(unsigned int dout){
  unsigned int dsdo=0;
  unsigned char i;
 
  nSEL=0;               // activate rfm12
  for(i=0;i<16;i++){    // bit by bit...
    if(dout&0x8000){    // is data out lsb 1???
      SDO=1;            // yes, SDO high
    }else{
      SDO=0;            // no, SDO low
    }
    dsdo<<=1;           // next bit of data in!
    if(SDI){            // is SDI high (rfm12 has been received data)?
      dsdo|=1;          // set corresponding bit of data in
    }
    SCK=1;              // positive edge of clk
    dout<<=1;           // next bit of data out
    delay_us(5);
    SCK=0;              // negative edge of clk
  }
  nSEL=1;               // deactivate rfm12
  return dsdo;          // return data in
}
