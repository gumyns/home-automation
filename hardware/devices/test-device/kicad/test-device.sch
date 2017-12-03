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
Sheet 1 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 6500 1950 550  700 
U 5A23F7D8
F0 "RJ-12" 60
F1 "rj12.sch" 60
F2 "GND" I L 6500 2050 60 
F3 "RX" I L 6500 2550 60 
F4 "TX" I L 6500 2450 60 
F5 "INT" I L 6500 2350 60 
F6 "RDY" I L 6500 2250 60 
F7 "OUT_5V" I L 6500 2150 60 
$EndSheet
$Sheet
S 1384 566  566  484 
U 5A240937
F0 "common uc" 60
F1 "common.sch" 60
F2 "IN_3.3V" I R 1950 750 60 
F3 "GND" I R 1950 650 60 
F4 "NRST" I R 1950 850 60 
F5 "BOOT0" I R 1950 950 60 
$EndSheet
$Sheet
S 3400 600  900  300 
U 5A240D21
F0 "Power" 60
F1 "Power.sch" 60
F2 "OUT_3.3V" I L 3400 800 60 
F3 "IN_5V" I R 4300 700 60 
F4 "GND" I L 3400 700 60 
$EndSheet
$Comp
L STM32F030F4Px U1
U 1 1 5A24281C
P 3750 2250
F 0 "U1" H 2150 3175 50  0000 L BNN
F 1 "STM32F030F4Px" H 5350 3175 50  0000 R BNN
F 2 "Housings_SSOP:TSSOP-20_4.4x6.5mm_Pitch0.65mm" H 5350 3125 50  0001 R TNN
F 3 "" H 3750 2250 50  0001 C CNN
	1    3750 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 700  3400 700 
Wire Wire Line
	3400 800  3000 800 
Wire Wire Line
	3350 800  3350 1250
Wire Wire Line
	3350 1250 3750 1250
Connection ~ 3350 800 
Connection ~ 3650 1250
Wire Wire Line
	1950 650  3000 650 
Wire Wire Line
	3000 650  3000 700 
Wire Wire Line
	1950 750  3000 750 
Wire Wire Line
	3000 750  3000 800 
Wire Wire Line
	1950 850  2050 850 
Wire Wire Line
	2050 850  2050 1650
Wire Wire Line
	1950 950  2000 950 
Wire Wire Line
	2000 950  2000 1850
Wire Wire Line
	2000 1850 2050 1850
Wire Wire Line
	6500 2150 6400 2150
Wire Wire Line
	6400 2150 6400 700 
Wire Wire Line
	6400 700  4300 700 
Wire Wire Line
	3350 700  3350 500 
Wire Wire Line
	3350 500  4350 500 
Wire Wire Line
	4350 500  4350 650 
Wire Wire Line
	4350 650  6450 650 
Connection ~ 3350 700 
Wire Wire Line
	6450 650  6450 2050
Wire Wire Line
	6450 2050 6500 2050
Wire Wire Line
	2000 650  2000 550 
Wire Wire Line
	2000 550  1350 550 
Wire Wire Line
	1350 550  1350 3150
Wire Wire Line
	1350 3150 3750 3150
Connection ~ 2000 650 
Wire Wire Line
	6500 2550 5450 2550
Wire Wire Line
	6500 2450 5450 2450
Wire Wire Line
	6500 2350 6400 2350
Wire Wire Line
	6400 2350 6400 2650
Wire Wire Line
	6400 2650 5450 2650
Wire Wire Line
	6500 2250 6300 2250
Wire Wire Line
	6300 2250 6300 2750
Wire Wire Line
	6300 2750 5450 2750
$Comp
L CONN_02X04 J3
U 1 1 5A24BA56
P 5800 2000
F 0 "J3" H 5800 2250 50  0000 C CNN
F 1 "CONN_02X04" H 5800 1750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x04_Pitch2.54mm" H 5800 800 50  0001 C CNN
F 3 "" H 5800 800 50  0001 C CNN
	1    5800 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1850 5550 1850
Wire Wire Line
	5450 1950 5550 1950
Wire Wire Line
	5450 2050 5550 2050
Wire Wire Line
	5450 2150 5550 2150
Wire Wire Line
	5450 1750 6050 1750
Wire Wire Line
	6050 1750 6050 1850
Wire Wire Line
	5450 1650 6150 1650
Wire Wire Line
	6150 1650 6150 1950
Wire Wire Line
	6150 1950 6050 1950
Wire Wire Line
	5450 2250 6050 2250
Wire Wire Line
	6050 2250 6050 2150
Wire Wire Line
	5450 2350 6150 2350
Wire Wire Line
	6150 2350 6150 2050
Wire Wire Line
	6150 2050 6050 2050
$Comp
L CONN_01X02 J2
U 1 1 5A24C4DB
P 3100 1050
F 0 "J2" H 3100 1200 50  0000 C CNN
F 1 "CONN_01X02" V 3200 1050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3100 1050 50  0001 C CNN
F 3 "" H 3100 1050 50  0001 C CNN
	1    3100 1050
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X02 J1
U 1 1 5A24C5F1
P 1650 1400
F 0 "J1" H 1650 1550 50  0000 C CNN
F 1 "CONN_01X02" V 1750 1400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 1650 1400 50  0001 C CNN
F 3 "" H 1650 1400 50  0001 C CNN
	1    1650 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1350 1350 1350
Connection ~ 1350 1350
Wire Wire Line
	1450 1450 1350 1450
Connection ~ 1350 1450
Wire Wire Line
	3300 1000 3350 1000
Connection ~ 3350 1000
Wire Wire Line
	3350 1100 3300 1100
Connection ~ 3350 1100
$Comp
L CONN_01X02 J4
U 1 1 5A24CE47
P 6100 1100
F 0 "J4" H 6100 1250 50  0000 C CNN
F 1 "CONN_01X02" V 6200 1100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 6100 1100 50  0001 C CNN
F 3 "" H 6100 1100 50  0001 C CNN
	1    6100 1100
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 1050 6400 1050
Connection ~ 6400 1050
Wire Wire Line
	6300 1150 6400 1150
Connection ~ 6400 1150
$EndSCHEMATC
