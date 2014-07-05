'Commands:
'
'Type up to the Payload length number of keys followed by <enter> to transmit data.
'<esc> Enter command mode.
'<c> Input a HEX command WORD value to send to RFM12. For example enter: c0e0 <enter> will set the ouput CLK to 10MHZ.
'<e> Toggle Echo. Useful for testing the range of a set of modules. Setup one module to echo and the other to Transmit a beacon. The code will not allow both echo and beacon to be on at the same time.
'<b> Toggle the Beacon. Transmit a test signal continuously and check for a reply.
'<u> Upload a new program to the uC. Only works if you are using a bootloader.
'Good Luck and if you have any question please feel free to comment.
'
'************************ TxRx_1.05.bas ***********************
'
'Test program for using the RFM12 or RFM12B
'433MHz Radio Data Transceivers.
'These transceivers sell for about $8.00 US.
'from: http://www.futurlec.com/Radio.shtml
'
'This code + hardware takes serial data from a PC and converts
'it to RF. A second indentical device receives the RF signal and
'converts it back to serial.
'
'This code is not ment to be a complete RF serial link. It is
'for testing and evaluating the RFM12 modules only. However with
'the addition of error detection and correction, I beleve a
'reliable RF link could be relized.
'
'July 28, 2008
'By: David Carr
'***************************************************************

$regfile = "m88def.dat"
$hwstack = 32
$swstack = 10
$framesize = 40

$crystal = 8000000
$baud = 19200

const File = "TxRx 1.05 .bas"
const Description = "RFM12 monitor program"

print
print Description
print File
print version()

RFM12_rst alias portc.5
config RFM12_rst = input

config portb = &b0010_1101

Test_pin alias portb.0

RFM12_cs alias Portb.2
set RFM12_cs

RFM12_sdi alias Portb.3

RFM12_sdo alias Pinb.4
set portb.4

RFM12_sck alias portb.5

RX_LED alias portd.5
config pind.5 = output

TX_LED alias portd.6
config pind.6 = output

Error_LED alias PORTd.7
config pind.7 = output

config Spi = Hard , Interrupt = Off , Data Order = Msb , Master = Yes , _
Polarity = Low , Phase = 0 , Clockrate = 4 , Noss = 1
spiinit

declare sub RFM12_SPI_wrt
declare sub RFM12_Tx(TxArray as byte)
declare sub RFM12_Rx(RxArray as byte)
declare sub RFM12_Tx_ready
declare sub RFM12_Rx_wait
declare sub RFM12_Get_Status_bit
declare sub SaveFlags
declare sub RFM12_Clear_FIFO
declare sub RFM12_Rx_on
declare sub RFM12_Init
declare sub PrintFlags

'From: RF12 Programing Guide
'Min Freq 430.24
'Max Freq 439.75
'in 2.5KHz steps
'
'That makes 3800 possible frequencies
'to choose from.

'Fc = the center Freq. in MHz
'Fr = the Freq. register value.
'Fc = 430 + Fr * 0.0025 (MHz)
'Fr = (Fc - 430) * 400
const Fc = 435.00
const Fr =(Fc - 430) * 400
const Fcmnd = &hA000 + Fr

'Payload can be up to 254 bytes.
'I have tested up to 128 bytes only.
'const Payload_Size = 128
const Payload_Size = 32
'const Payload_Size = 16
const PLS_plus1 = Payload_Size + 1

'make the test beacon length Payload_Size - 2
const Beacon = "123456789012345678901234567890"

dim Tempbit as bit
dim Temp as byte
dim TempW as word

dim SPI_Tx_wrd as word
dim SPI_Tx_L as byte at SPI_Tx_wrd overlay
dim SPI_Tx_H as byte at SPI_Tx_wrd + 1 overlay
dim SPI_Rx_wrd as word
dim SPI_Rx_L as byte at SPI_Rx_wrd overlay
dim SPI_Rx_H as byte at SPI_Rx_wrd + 1 overlay

dim Rx_Status_bit as bit
dim RxBuffer(PLS_plus1) as byte
dim RxString as string * Payload_Size at RxBuffer(1) overlay
RxBuffer(PLS_plus1) = 0

dim TxIndex as byte
dim TxBuffer(PLS_plus1) as byte
dim TxString as string * Payload_Size at TxBuffer(1) overlay
TxBuffer(PLS_plus1) = 0

dim Timeout as word
dim Cmnd as string * 4
dim Flags as byte

EchoFlag alias Flags.0
BeaconFlag alias Flags.1
SerMsgFlag alias Flags.2
RxOnFlag alias Flags.3
TxOnFlag alias Flags.4

'I have read somewhere that eram address 0 has a bug
'so I don't use it.
dim Dummy as eram word at 0
'ProgCntr must be at eram address 2.
'ProgCntr is incramented by the bootloader
'each time the chip is flashed.
dim ProgCntr as eram word at 2
dim SavedFlags as eram byte


TempW = ProgCntr
print "uC flashed " ; TempW ; " times."
print

'kill some time here while
'rfm12 does a power on reset.
reset RX_LED
reset TX_LED
reset Error_LED
waitms 500
set RX_LED
set TX_LED
set Error_LED

RFM12_Init
RFM12_Rx_on

Flags = SavedFlags
print "Echo = " ; EchoFlag
print "Beacon = " ; BeaconFlag
Cmnd = ""

do
   if BeaconFlag = 1 then
      'Tx a test beacon about once a second.
      TxString = Beacon
      print "Tx: " ; TxString
      RFM12_Tx TxBuffer(1)
      'now loop waiting for a reply msg.
      for temp = 1 to 255
         'poll RFM12 for Rx data.
         RFM12_Get_Status_bit
         if Rx_Status_bit = 1 then
            'Rx RxBuffer
            RFM12_Rx RxBuffer(1)
            print "Rx: " ; RxString
            if RxString <> TxString then
               reset Error_LED
               print "<>"
            endif
             RxString = ""
             exit for
          endif
          if temp = 255 then
            reset Error_LED
            print "no echo"
          endif
          'this delay gives the other module time to echo
          'back the beacon.
          'waitus 50        'at 38.3kbps, 32 byte payload
          'waitus 350       'at 19.2kbps, 128 bytes
          waitus 150       'at 19.2kbps, 32 bytes
          set Error_LED
      next temp
   else
      'poll RFM12 for Rx data.
      RFM12_Get_Status_bit
      if Rx_Status_bit = 1 then
         'reset RX_LED
         'Rx RxBuffer
         RFM12_Rx RxBuffer(1)
         print "Rx: " ; RxString
         if EchoFlag = 1 then
            print "Ec: " ; RxString
            'Tx RxBuffer.
            RFM12_Tx RxBuffer(1)
         endif
         'set RX_LED
       endif
    endif

    temp = inkey()
    if temp <> 0 then

      if temp = 27 then
         'press "esc" to get a command prompt.
         SPI_Tx_wrd = 0
         RFM12_SPI_wrt
         print
         print Description
         print File
         print version()
         print
         TempW = ProgCntr
         print "uC flashed " ; TempW ; " times."
         'print
         'print "Status word = " ; bin(SPI_Rx_H) ; "_" ; bin(SPI_Rx_L)
         PrintFlags
         print
         input "Command >" , Cmnd
         print
         RFM12_Rx_on
      elseif temp = 13 then
         print
         print "Tx: " ; TxString
         'Tx TxBuffer.
         RFM12_Tx TxBuffer(1)
         TxString = ""
         TxIndex = 0
      else
         'fill the TxBuffer until <cr> or full.
         if TxIndex < Payload_Size then
            print chr(temp);
            incr TxIndex
            TxBuffer(TxIndex) = temp
            Temp = TxIndex + 1
            TxBuffer(Temp) = 0
         endif
      endif
   endif


   if Cmnd <> "" then
      Select Case Cmnd
          case "u"
            'To start the bootloader without using the reset button.
            'Press "u <CR>"
            'then within 2+3=5 seconds press F4 to start the programer.
            print
            print "Press F4 to start upload."
             Waitms 3000
             'address of boot loader.
             'for mega168
             'goto &H1C00

             'for mega88
             goto &hC00

          case "c"
            'Input a hex command word value to send to RFM12.
            'For example enter: c0e0 <enter> will set the
            'ouput CLK to 10MHZ.
            'see the RFM12 Programing guide for commands.
            print
            input "Enter a Command Word in HEX >" , Cmnd
            SPI_Tx_wrd = hexval(Cmnd)
            RFM12_SPI_wrt
            print "RFM12 returned >" ; hex(SPI_Rx_wrd)

          case "b"
            toggle BeaconFlag
            if BeaconFlag = 1 then EchoFlag = 0
            SaveFlags
            PrintFlags

          case "e"
            toggle EchoFlag
            if EchoFlag = 1 then BeaconFlag = 0
            SaveFlags
            PrintFlags

          case else
            print "Unknown Command"

      end select
      print
      Cmnd = ""
   endif
loop

sub PrintFlags
   if BeaconFlag = 1 then
      print "Beacon ON"
   else
      print "Beacon OFF"
   endif
   if EchoFlag = 1 then
      print "Echo ON"
   else
      print "Echo OFF"
   endif
end sub

sub SaveFlags
   'save to eram
   Flags = Flags and 3
   SavedFlags = Flags
end sub

sub RFM12_Init
   local i as byte
   print "Init values:"
   'Initialize RFM12
   Restore Init_data
   for i = 1 to 14
      read SPI_Tx_wrd
      print hex(SPI_Tx_wrd)
      'send init data to RFM12.
      RFM12_SPI_wrt
      'waitms 100
   next i
   print
end sub

'***********************************************************************
'The following data lines are RFM12 commands used to initialize the device.
'read the RFM12 progamming guide and data sheets for a complete
'description of these commands.
'
'Configuration settings:
'
'&h80D8 = Configure module for 433Mhz band.
'
'RF center Freq. setting
'select freq with const "Fc" above.
'Fcmnd is a constant that holds the Freq command.
'see the "const" statments at the top of this code.
'example: &hA000 + Fr = &hA7D0 for 435MHz
'
'To change the data rate the following values will need to be adjusted.
'
'bit rate
'&hC611 = 19.2kbps works well at 8MHz
'&hC608 = 38.3kbps works at 8MHz
'
'Rx band width
'&h94A0 = Rx BW = 134KHz works at 8MHz
'&h9480 = 200kHz works at 8MHz
'
'Tx deviation
'&h9850  = 90kHz  works at 8MHz
'&h9870  = 120kHz  works at 8MHz

Init_data:
data &h80D8% , &h8298% , Fcmnd% , &hC611% , &h94A0% , &hC2AC% , &hCA81%
data &hCED4% , &hC483% , &h9850% , &hCC17% , &hE000% , &hC800% , &hC040%
'*************************************************************************

sub RFM12_Clear_FIFO
   'Clear FIFO
   SPI_Tx_wrd = &hCA81
   RFM12_SPI_wrt
   SPI_Tx_wrd = &hCA83
   RFM12_SPI_wrt
end sub

sub RFM12_Tx(TxArray as byte)
   local i as byte
   reset TX_LED
   'turn on Tx
   SPI_Tx_wrd = &h8239
   RFM12_SPI_wrt
   TxOnFlag = 1
   waitus 150
   'Send Preamble.
   restore TxPreamble_data
   for i = 1 to 5
      read SPI_Tx_wrd
      RFM12_Tx_ready
      if Timeout = 0 then exit for
      RFM12_SPI_wrt
   next i
   'Send payload.
   for i = 1 To Payload_Size
      RFM12_Tx_ready
      if Timeout = 0 then exit for
      SPI_Tx_wrd = &hB800 + TxArray(i)
      RFM12_SPI_wrt
   next i
   RFM12_Tx_ready
   RFM12_Rx_on
   set TX_LED
end sub

TxPreamble_data:
data &hB8AA% , &hB8AA% , &hB8AA% , &hB82D% , &hB8D4%

sub RFM12_Tx_ready
   Reset RFM12_cs
   Timeout = 65500
   While RFM12_sdo = 0
      decr Timeout
      waitus 6
      if Timeout = 0 then
         print "Tx Timeout"
         exit while
      endif
   Wend
end sub

sub RFM12_Rx_on
   'Start Rx
   SPI_Tx_wrd = &h8299
   RFM12_SPI_wrt
   RFM12_Clear_FIFO
   RxOnFlag = 1
   waitus 80
end sub

sub RFM12_Rx(RxArray as byte)
   local i as byte
   timeout = 1
   reset RX_LED
   SPI_Tx_wrd = &hB000
   for i = 1 To Payload_Size
      RFM12_Rx_wait
      if Timeout = 0 then
         set RX_LED
         set Error_LED
         exit for
      endif
      RFM12_SPI_wrt
      RxArray(i) = SPI_Rx_L
   next i
   RxArray(i) = 0
   RFM12_Clear_FIFO
   set RX_LED
end sub

sub RFM12_Rx_wait
   Timeout = 35500
   do
      RFM12_Get_Status_bit
      'timeout if nothing happens.
      decr Timeout
      if Timeout = 0 then
         reset Error_LED
         print "Rx Timeout"
         exit do
      endif
   loop until Rx_Status_bit = 1
end sub

sub RFM12_Get_Status_bit
   reset RFM12_sdi
   reset RFM12_cs
   set RFM12_sck
   Rx_Status_bit = RFM12_sdo
   reset RFM12_sck
   set RFM12_cs
end sub

sub RFM12_SPI_wrt
   'Send word (SPI_Tx_wrd) to RFM12.
   'Also receive word (SPI_Rx_wrd).
   'RFM12 Chip select
   reset RFM12_cs
   'send hi byte.
   SPI_Rx_H = spimove(SPI_Tx_H)
   'send lo byte.
   SPI_Rx_L = spimove(SPI_Tx_L)
   'deselect chip.
   set RFM12_cs
end sub