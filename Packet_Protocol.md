File: Command Packet Structure

Version = .1 

Byte,		Description
0 = Destination segment number (1-8).  Zero (0) is a broadcast packet processed by all 8 segments.
1 = Mode: 10=binary, 11=font1, 12=font2, etc, 20=Horizontal Line Position, 21=Vertical Line pos., etc. 
2 = Red Color Level  (10-255) For >= ASCII mode only.
3 = Green Color Level  (10-255) For >= ASCII mode only.
4 = Blue Color Level  (10-255) For >= ASCII mode only.
5 = First byte of data. Single byte if ASCII, 192 if binary. All bytes must be 10-255
...
n = Last byte in packet.  Must be a 9.  Terminator byte.   All bytes above must be 10-255.  Receipt of the 9 causes this packet to be transferred from the serial port buffer to the active buffer.
