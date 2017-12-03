EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:rj12-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RJ12 J1
U 1 1 5A15E7EA
P 2100 1950
F 0 "J1" H 2300 2450 50  0000 C CNN
F 1 "RJ12" H 1950 2450 50  0000 C CNN
F 2 "conn-rj11:molex_95501-2641" H 2100 1950 50  0001 C CNN
F 3 "" H 2100 1950 50  0001 C CNN
	1    2100 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2400 2400 2650
Wire Wire Line
	2300 2400 2300 2950
Wire Wire Line
	2200 2400 2200 2950
Wire Wire Line
	2100 2400 2100 2950
Wire Wire Line
	2000 2400 2000 2950
Wire Wire Line
	2600 1350 2600 1650
Wire Wire Line
	2600 1350 1700 1350
Wire Wire Line
	1700 1350 1700 2400
Wire Wire Line
	1700 2400 1900 2400
Connection ~ 2600 1550
Wire Wire Line
	2650 2550 2650 1550
Wire Wire Line
	2650 1550 2600 1550
Text HLabel 2650 2550 2    60   Input ~ 0
GND
Text HLabel 2100 2950 3    60   Input ~ 0
RX
Text HLabel 2000 2950 3    60   Input ~ 0
TX
Text HLabel 2200 2950 3    60   Input ~ 0
INT
Text HLabel 2300 2950 3    60   Input ~ 0
RDY
Wire Wire Line
	2400 2650 2650 2650
Text HLabel 2650 2650 2    60   Input ~ 0
OUT_5V
$EndSCHEMATC
