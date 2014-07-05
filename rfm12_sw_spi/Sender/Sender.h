/**
 * @file Sender.h
 * 
 *
 */

#ifndef SENDER_H
#define SENDER_H

typedef struct {
  unsigned int len : 8;
  unsigned int dev : 8;
  unsigned char pl[20];
  unsigned int chksum : 8;
} msg_str;

#endif