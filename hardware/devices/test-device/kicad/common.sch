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
Sheet 3 4
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
L C C1
U 1 1 5A240981
P 1750 2200
F 0 "C1" H 1775 2300 50  0000 L CNN
F 1 "C" H 1775 2100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1788 2050 50  0001 C CNN
F 3 "" H 1750 2200 50  0001 C CNN
	1    1750 2200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J6
U 1 1 5A240982
P 2200 3150
F 0 "J6" H 2200 3300 50  0000 C CNN
F 1 "CONN_01X02" V 2300 3150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2200 3150 50  0001 C CNN
F 3 "" H 2200 3150 50  0001 C CNN
	1    2200 3150
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5A240983
P 2150 2750
F 0 "R2" V 2230 2750 50  0000 C CNN
F 1 "10k" V 2150 2750 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2080 2750 50  0001 C CNN
F 3 "" H 2150 2750 50  0001 C CNN
	1    2150 2750
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 5A240984
P 2150 2550
F 0 "R1" V 2230 2550 50  0000 C CNN
F 1 "10k" V 2150 2550 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2080 2550 50  0001 C CNN
F 3 "" H 2150 2550 50  0001 C CNN
	1    2150 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2300 2550 2350 2550
Wire Wire Line
	2300 2750 2350 2750
Wire Wire Line
	2300 2750 2300 2950
Wire Wire Line
	2300 2950 2250 2950
Wire Wire Line
	1750 1850 1750 2050
Wire Wire Line
	2150 2950 1900 2950
Wire Wire Line
	1900 2950 1900 2050
Wire Wire Line
	2000 2550 1900 2550
Connection ~ 1900 2550
Text HLabel 1750 1850 2    60   Input ~ 0
IN_3.3V
Wire Wire Line
	1900 2050 1750 2050
Wire Wire Line
	1750 2350 1750 2900
Wire Wire Line
	1750 2750 2000 2750
Connection ~ 1750 2750
Text HLabel 1750 2900 0    60   Input ~ 0
GND
Text HLabel 2350 2550 2    60   Input ~ 0
NRST
Text HLabel 2350 2750 2    60   Input ~ 0
BOOT0
$EndSCHEMATC
