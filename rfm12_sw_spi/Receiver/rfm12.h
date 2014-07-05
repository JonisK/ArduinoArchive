/**
 * @file rfm12.h
 * 
 * Header file of RFM12-868MHz-Band FSK Module
 * 
 * Message block has been designed as follows:
 * 
 * +----------------------------------------+
 * |  dev  |  command  |  value  |  chksum  |
 * +----------------------------------------+
 * 
 *  dev : 8  -> receiver device number
 *  cmd : 8  -> command
 *  val : 16 -> value regarding command
 *  cs  : 8  -> checksum of the message
 */

#ifndef RFM12_H
#define RFM12_H

// port mapping
#define SDI   RB1
#define SDO   RB2
#define SCK   RB4
#define nSEL  RB3
#define nIRQ  RB0

// configure ports (input/output)
#define SDI_IN()    TRISB1=1
#define SDO_OUT()   TRISB2=0
#define SCK_OUT()   TRISB4=0
#define nSEL_OUT()  TRISB3=0
#define nIRQ_IN()   TRISB0=1

// Timeout values
#define RFM12_TOUT  (1000)    // 100ms
#define TOUT_1s     (10000)

/**
 * external interface
 */
extern void rfm12_init(void);
extern void rfm12_ena_rx(void);
extern void rfm12_dis_rx(void);
extern unsigned char rfm12_snd_msg(unsigned char *msg,int len);
extern unsigned char rfm12_rcv_msg(unsigned char *msg,int len);


#endif