EESchema Schematic File Version 2
LIBS:stm32
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
LIBS:test-device-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
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
L LD1117S33TR U2
U 1 1 5A240D8B
P 2250 1200
F 0 "U2" H 2250 1500 50  0000 C CNN
F 1 "LD1117S33TR" H 2250 1400 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-223-3_TabPin2" H 2250 1300 50  0001 C CNN
F 3 "" H 2250 1200 50  0001 C CNN
	1    2250 1200
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5A240D8C
P 2700 1300
F 0 "C3" H 2725 1400 50  0000 L CNN
F 1 "C" H 2725 1200 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 2738 1150 50  0001 C CNN
F 3 "" H 2700 1300 50  0001 C CNN
	1    2700 1300
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5A240D8D
P 1800 1300
F 0 "C2" H 1825 1400 50  0000 L CNN
F 1 "C" H 1825 1200 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 1838 1150 50  0001 C CNN
F 3 "" H 1800 1300 50  0001 C CNN
	1    1800 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1150 1850 1150
Connection ~ 1800 1150
Connection ~ 2700 1150
Connection ~ 1800 1450
Connection ~ 2250 1450
Wire Wire Line
	1250 1450 2700 1450
Wire Wire Line
	2700 1150 2700 1000
Wire Wire Line
	2700 1000 1250 1000
Wire Wire Line
	2650 1150 2700 1150
Text HLabel 1250 1000 0    60   Input ~ 0
OUT_3.3V
Text HLabel 1250 1150 0    60   Input ~ 0
IN_5V
Text HLabel 1250 1450 0    60   Input ~ 0
GND
Text Label 1250 1000 0    60   ~ 0
3.3V
Text Label 1250 1150 0    60   ~ 0
5V
Text Label 1250 1450 0    60   ~ 0
GND
$EndSCHEMATC
