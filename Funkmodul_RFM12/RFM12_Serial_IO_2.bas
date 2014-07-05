'IMPORTANT NOTE:
'This code uses the FFIT signal from the RFM12 module.
'Add a connection from FFIT to PD.2 (pin 4).
'

'This program transmits rs232 data using RFM12 wireless Trasceivers.
'Type some text then press "Enter" to send it.
'The text will be output at the 2nd micro's rs232 uart.
'Errors are detected but for this example they are ingnored.

'change these to match your setup.
$regfile = "m168def.dat"
$crystal = 14745600
'$regfile = "m88def.dat"
'$regfile = "m328pdef.dat"
'$crystal = 8000000

'$baud = 19200
$baud = 115200
Print "Serial IO"

'These are for my bootloader.
'$loadersize = 2048
'$programmer = 13

Declare Sub Rfm12_tx_packet
Declare Sub Rfm12_rx_packet

Const Fc = 435.00
Const Fr =(fc - 430) * 400
Const Fcmnd = &HA000 + Fr

'LSB of CE command = Syncron address of RFM12 device. Must match target device.
Const Syncron = &HD4
Const Acmnd = &HCE00 + Syncron

'not used in this examaple.
Const Ackb = &H7F
Const Nackb = &H7E
'Number of retrys before LinkFails
Const Retrys = 10

Dim Timeout As Bit

Dim Temp1 As Byte
Dim Txid As Byte
Dim Crc As Byte
Dim Rxstatus As Byte
Dim Deviceaddr As Byte
Dim Txbyte As Byte
Dim Rxbyte As Byte
Dim Txpntr As Byte
Dim Rxpntr As Byte
Dim Key As Byte

'Packet format:
'Byte
'  1     Destination Address
'  2     Source Address
'  3     Message Length
'  4     Message ID
'  5     Function
'  6     Arg1
'  7     Arg2
'  8     data1
'  9     data2
'  .       .
'  .       .
'  23    data16
'  24    CRC - crc is for all bytes (1 thru 23).

Dim Rxbuf(40) As Byte
Dim Rxstr As String * 32 At Rxbuf(6) Overlay
Dim Txbuf(40) As Byte
Dim Strin As String * 32
Dim Strout As String * 32

Dim Spi_tx_wrd As Word
Dim Spi_tx_l As Byte At Spi_tx_wrd Overlay
Dim Spi_tx_h As Byte At Spi_tx_wrd + 1 Overlay
Dim Spi_rx_wrd As Word
Dim Spi_rx_l As Byte At Spi_rx_wrd Overlay
Dim Spi_rx_h As Byte At Spi_rx_wrd + 1 Overlay

'Error bits.
Rxnotmyaddr Alias Rxstatus.0
Rxid_err Alias Rxstatus.1
Rxcrcerr Alias Rxstatus.2
Rxtimeout Alias Rxstatus.3
Rxnack Alias Rxstatus.4
Comerr Alias Rxstatus.5

'1 = output, 0 = input
Config Portb = &B0010_1100

'these are pin assignments for the RFM12.
'change to match your system.
Rfm12_cs Alias Portb.2
Set Rfm12_cs

Rfm12_sdi Alias Portb.3

Rfm12_sdo Alias Pinb.4
Set Portb.4

Rfm12_sck Alias Portb.5

'RFM12_FFIT alias Pinb.1
'config pinb.1 = input
'set portb.1

'for Diecmila
Rfm12_ffit Alias Pind.2
Config Pind.2 = Input
Set Portd.2

'LED pin assignments
Rx_led Alias Portd.5
Config Pind.5 = Output

Tx_led Alias Portd.6
Config Pind.6 = Output

Error_led Alias Portd.7
Config Pind.7 = Output

'flash LEDs
Reset Rx_led
Reset Tx_led
Reset Error_led
Waitms 250
Set Rx_led
Set Tx_led
Set Error_led

'watchdog is used for RX timeout.
'it does not reset the micro.
'if it times out isrTimeOut is run.
'see: RFM12_Rx_Packet for how it is used.
Config Watchdog = 128
On Wdt Isrtimeout
Disable Wdt
Enable Interrupts

Config Spi = Hard , Interrupt = Off , Data Order = Msb , Master = Yes , _
Polarity = Low , Phase = 0 , Clockrate = 16 , Noss = 1
Spiinit

'redirect print #2
'to transmit data just use print #2, "your string"
$serialoutput1 = Myoutput
Open "com2:" For Binary As #2

Gosub Rfm12_init
Gosub Rfm12_restart_synchron

'Addresses:
'You can select any values for your device
'addresses. Just make sure that DeviceAddr matches
'MyAddr in the other micro.

'use these on one device
Const Myaddr = &HDC
Deviceaddr = &HAC

'And use these on the other device
'const MyAddr = &hAC
'DeviceAddr = &hDC

Txpntr = 5

Do
   'check for received data
   Gosub Inputstr
   If Rxstr <> "" Then
      Print Rxstr;
   End If

   Key = Inkey()
   If Key > 0 Then
      If Key = 13 Then
         'Transmit data
         Print #2 , Strout
         Print "Tx: " ; Strout
         Strout = ""
      Else
         'Buffer key strokes until a <CR>
         Strout = Strout + Chr(key)
      End If
   End If
Loop

'***** subroutines *****
Myoutput:
'the data arrives in R24
'store data in TxByte
!sts {TxByte} , r24
Pushall
Incr Txpntr
'send packet if length gets to long
If Txpntr > 38 Then Txbyte = 10
'print TxByte
Txbuf(txpntr) = Txbyte
'if data is a LF then send packet.
If Txbyte = 10 Then
 Incr Txid
   Txbuf(1) = Deviceaddr
   Txbuf(2) = Myaddr
   Txbuf(3) = Txpntr + 1
   Txbuf(4) = Txid
   Txbuf(5) = 0
   Txbuf(txbuf(3)) = Crc8(txbuf(1) , Txpntr)
   Rfm12_tx_packet
   Txpntr = 5
End If
Popall
Return

Inputstr:
 'FFIT is set when a byte of data has come into the receiver.
 If Rfm12_ffit = 1 Then
    'so go receive one complete packet.
    Gosub Rfm12_rx_packet
    'if Rx was good.
    'mask IdError
    Rxstatus = Rxstatus And &HFD
    If Rxstatus = 0 Then
      'check for boot uploader calling.
      'if it is jump to boot loader.
       If Rxbuf(5) = &H8F Then Goto &HC00
       'print "RX OK"
         Rxbuf(rxbuf(3)) = 0
    End If
 Else
   Rxstr = ""
 End If
Return

Rfm12_init:
   'Initialize RFM12
   Restore Init_data
   For Temp1 = 1 To 16
      Read Spi_tx_wrd
      'send init data to RFM12.
      Gosub Rfm12_spi_wrt
      'waitms 30
   Next Temp1
Return

Init_data:
'19.2kbps - This data is tested and works well.
Data &HCA81% , &HFE00% , &H80D8% , &H8298% , Fcmnd% , &HC611% , &H94C0% , &HC2AC%
Data &HCA81% , Acmnd% , &HC483% , &H9820% , &HCC17% , &HE000% , &HC800% , &HC040%

'38.3kbps - quick short range (~25') test - Some Errors - corrected
'data &hCA81% , &hFE00% , &h80D8% , &h8298% , Fcmnd% , &h9480% , &hC2AC% , &hCA81%
'data ACmnd% , &hC483% , &h9870% , &hCC17% , &hE000% , &hC800% , &hC040%

Sub Rfm12_tx_packet
   Local I As Byte
   Local L As Byte
   Reset Tx_led
   'get Packet Length and add a dummy byte to payload
   L = Txbuf(3) + 1
   'turn on Tx
   Spi_tx_wrd = &H8239
   Gosub Rfm12_spi_wrt
   'short delay for Tx startup.
   Waitus 150
   'Send Preamble.
   Restore Txpreamble_data
   For I = 1 To 5
      Read Spi_tx_wrd
      Gosub Rfm12_ready
      Gosub Rfm12_spi_wrt
   Next I
   'Send payload.
   For I = 1 To L
      Spi_tx_wrd = &HB800 + Txbuf(i)
      Gosub Rfm12_ready
      Gosub Rfm12_spi_wrt
   Next I
   Gosub Rfm12_ready
   'turn on Rx
   Spi_tx_wrd = &H8299
   Gosub Rfm12_spi_wrt
   Waitus 80
   Gosub Rfm12_restart_synchron
   Set Tx_led
End Sub
Txpreamble_data:
Data &HB8AA% , &HB8AA% , &HB8AA% , &HB82D% , &HB8D4%

Rfm12_ready:
   Reset Rfm12_cs
   Bitwait Rfm12_sdo , Set
Return

Sub Rfm12_rx_packet
   Local I As Byte
   Local L As Byte
   Reset Rx_led
   'reset RxOk
   Reset Timeout
   Rxstatus = 0
   I = 1
   L = 3
   Enable Wdt
   'read FIFO command word for RFM12
   Spi_tx_wrd = &HB000
   'loop until packet has been received.
   While I <= L
      'wait for data in FIFO.
      'if nothing the watchdog will timeout with Timeout set.
      Reset Watchdog
      While Rfm12_ffit = 0
         If Timeout = 1 Then
            Set Rxtimeout
            Goto Endrx
         End If
      Wend
      'get data from FIFO.
      'data in LSB of SPI_Rx_wrd ie SPI_Rx_l.
      Gosub Rfm12_spi_wrt
      'copy data to buffer.
      Rxbuf(i) = Spi_rx_l
      '1st byte - check for divice address
      If I = 1 Then
         If Spi_rx_l <> Myaddr Then
            Set Rxnotmyaddr
            Goto Endrx
         End If
      End If
      'third byte of packet is the length.
      'store length in l.
      If I = 3 Then L = Spi_rx_l
      'fourth byte is the message ID.
      If I = 4 Then
         If Spi_rx_l <> Txid Then Set Rxid_err
      End If
      'Fifth byte is ACK or NACK
      If I = 5 Then
         If Spi_rx_l = Nackb Then Set Rxnack
      End If

      'incrament index
      Incr I
   Wend
   Crc = Rxbuf(l)
   Decr L
   If Crc8(rxbuf(1) , L) <> Crc Then Set Rxcrcerr
   Endrx:
   Disable Wdt
   Set Rx_led
   Gosub Rfm12_restart_synchron
End Sub

Rfm12_restart_synchron:
   Spi_tx_wrd = &HCA81
   Gosub Rfm12_spi_wrt
   Spi_tx_wrd = &HCA83
   Gosub Rfm12_spi_wrt
Return

Rfm12_spi_wrt:
   'Send word (SPI_Tx_wrd) to RFM12.
   'Also receive word (SPI_Rx_wrd).
   'RFM12 Chip select
   Reset Rfm12_cs
   'send hi byte.
   Spi_rx_h = Spimove(spi_tx_h)
   'send lo byte.
   Spi_rx_l = Spimove(spi_tx_l)
   'deselect chip.
   Set Rfm12_cs
Return

Isrtimeout:
   Timeout = 1
   'print "isr"
Return