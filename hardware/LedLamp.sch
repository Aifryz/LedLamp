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
LIBS:prezent2-cache
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
L USB_OTG P2
U 1 1 56D7310A
P 1350 1000
F 0 "P2" H 1675 875 50  0000 C CNN
F 1 "USB_OTG" H 1350 1200 50  0000 C CNN
F 2 "microusb:10118192-0001LF" V 1300 900 60  0001 C CNN
F 3 "" V 1300 900 60  0000 C CNN
	1    1350 1000
	1    0    0    -1  
$EndComp
$Comp
L ATMEGA16-A IC1
U 1 1 5724DBB6
P 6250 3350
F 0 "IC1" H 5300 5230 40  0000 L BNN
F 1 "ATMEGA16-A" H 6750 1400 50  0000 L BNN
F 2 "Housings_QFP:LQFP-44_10x10mm_Pitch0.8mm" H 6250 3350 30  0000 C CIN
F 3 "" H 6250 3350 60  0000 C CNN
	1    6250 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5724DE91
P 5950 5450
F 0 "#PWR01" H 5950 5200 50  0001 C CNN
F 1 "GND" H 5950 5300 50  0000 C CNN
F 2 "" H 5950 5450 60  0000 C CNN
F 3 "" H 5950 5450 60  0000 C CNN
	1    5950 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5724DF70
P 1550 1500
F 0 "#PWR02" H 1550 1250 50  0001 C CNN
F 1 "GND" H 1550 1350 50  0000 C CNN
F 2 "" H 1550 1500 60  0000 C CNN
F 3 "" H 1550 1500 60  0000 C CNN
	1    1550 1500
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P7
U 1 1 5724E119
P 9700 3750
F 0 "P7" H 9700 4100 50  0000 C CNN
F 1 "CONN_01X06" V 9800 3750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 9700 3750 60  0001 C CNN
F 3 "" H 9700 3750 60  0000 C CNN
	1    9700 3750
	1    0    0    1   
$EndComp
$Comp
L CONN_01X06 P4
U 1 1 5724E180
P 8700 3100
F 0 "P4" H 8700 3450 50  0000 C CNN
F 1 "CONN_01X06" V 8800 3100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 8700 3100 60  0001 C CNN
F 3 "" H 8700 3100 60  0000 C CNN
	1    8700 3100
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 5724E2CF
P 6050 1000
F 0 "#PWR03" H 6050 850 50  0001 C CNN
F 1 "VCC" H 6050 1150 50  0000 C CNN
F 2 "" H 6050 1000 60  0000 C CNN
F 3 "" H 6050 1000 60  0000 C CNN
	1    6050 1000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR04
U 1 1 5724E41F
P 900 950
F 0 "#PWR04" H 900 800 50  0001 C CNN
F 1 "VCC" H 900 1100 50  0000 C CNN
F 2 "" H 900 950 60  0000 C CNN
F 3 "" H 900 950 60  0000 C CNN
	1    900  950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5724E496
P 9350 3500
F 0 "#PWR05" H 9350 3250 50  0001 C CNN
F 1 "GND" H 9350 3350 50  0000 C CNN
F 2 "" H 9350 3500 60  0000 C CNN
F 3 "" H 9350 3500 60  0000 C CNN
	1    9350 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5724E4B2
P 8500 3450
F 0 "#PWR06" H 8500 3200 50  0001 C CNN
F 1 "GND" H 8500 3300 50  0000 C CNN
F 2 "" H 8500 3450 60  0000 C CNN
F 3 "" H 8500 3450 60  0000 C CNN
	1    8500 3450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR07
U 1 1 5724E549
P 9300 4000
F 0 "#PWR07" H 9300 3850 50  0001 C CNN
F 1 "VCC" H 9300 4150 50  0000 C CNN
F 2 "" H 9300 4000 60  0000 C CNN
F 3 "" H 9300 4000 60  0000 C CNN
	1    9300 4000
	1    0    0    -1  
$EndComp
NoConn ~ 1250 1300
NoConn ~ 1350 1300
NoConn ~ 1450 1300
$Comp
L VCC #PWR08
U 1 1 5724EA29
P 8500 2750
F 0 "#PWR08" H 8500 2600 50  0001 C CNN
F 1 "VCC" H 8500 2900 50  0000 C CNN
F 2 "" H 8500 2750 60  0000 C CNN
F 3 "" H 8500 2750 60  0000 C CNN
	1    8500 2750
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5724EA96
P 5000 1500
F 0 "R1" V 5080 1500 50  0000 C CNN
F 1 "10k" V 5000 1500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4930 1500 30  0001 C CNN
F 3 "" H 5000 1500 30  0000 C CNN
	1    5000 1500
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR09
U 1 1 5724EC71
P 5000 1250
F 0 "#PWR09" H 5000 1100 50  0001 C CNN
F 1 "VCC" H 5000 1400 50  0000 C CNN
F 2 "" H 5000 1250 60  0000 C CNN
F 3 "" H 5000 1250 60  0000 C CNN
	1    5000 1250
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5724EF1F
P 2300 1100
F 0 "C1" H 2325 1200 50  0000 L CNN
F 1 "10uF" H 2325 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2338 950 30  0001 C CNN
F 3 "" H 2300 1100 60  0000 C CNN
	1    2300 1100
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5724FEFE
P 5700 1150
F 0 "C2" H 5725 1250 50  0000 L CNN
F 1 "220nf" H 5725 1050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5738 1000 30  0001 C CNN
F 3 "" H 5700 1150 60  0000 C CNN
	1    5700 1150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 57250174
P 5700 1300
F 0 "#PWR010" H 5700 1050 50  0001 C CNN
F 1 "GND" H 5700 1150 50  0000 C CNN
F 2 "" H 5700 1300 60  0000 C CNN
F 3 "" H 5700 1300 60  0000 C CNN
	1    5700 1300
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR011
U 1 1 5725032A
P 2300 900
F 0 "#PWR011" H 2300 750 50  0001 C CNN
F 1 "VCC" H 2300 1050 50  0000 C CNN
F 2 "" H 2300 900 60  0000 C CNN
F 3 "" H 2300 900 60  0000 C CNN
	1    2300 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5725034A
P 2300 1300
F 0 "#PWR012" H 2300 1050 50  0001 C CNN
F 1 "GND" H 2300 1150 50  0000 C CNN
F 2 "" H 2300 1300 60  0000 C CNN
F 3 "" H 2300 1300 60  0000 C CNN
	1    2300 1300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 P3
U 1 1 572506A9
P 8150 4400
F 0 "P3" H 8150 4650 50  0000 C CNN
F 1 "CONN_01X04" V 8250 4400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 8150 4400 60  0001 C CNN
F 3 "" H 8150 4400 60  0000 C CNN
	1    8150 4400
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR013
U 1 1 57250786
P 7950 4200
F 0 "#PWR013" H 7950 4050 50  0001 C CNN
F 1 "VCC" H 7950 4350 50  0000 C CNN
F 2 "" H 7950 4200 60  0000 C CNN
F 3 "" H 7950 4200 60  0000 C CNN
	1    7950 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 572507A9
P 7900 4600
F 0 "#PWR014" H 7900 4350 50  0001 C CNN
F 1 "GND" H 7900 4450 50  0000 C CNN
F 2 "" H 7900 4600 60  0000 C CNN
F 3 "" H 7900 4600 60  0000 C CNN
	1    7900 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 5450 5950 5350
Wire Wire Line
	5950 5350 6350 5350
Connection ~ 6050 5350
Connection ~ 6150 5350
Connection ~ 5950 5350
Wire Wire Line
	1550 1300 1550 1500
Wire Wire Line
	1750 900  1750 1400
Wire Wire Line
	5950 1350 6350 1350
Connection ~ 6050 1350
Connection ~ 6150 1350
Wire Wire Line
	6050 1000 6050 1350
Wire Wire Line
	900  1300 1150 1300
Wire Wire Line
	8500 3350 8500 3450
Wire Wire Line
	7550 3700 9500 3700
Wire Wire Line
	7450 3800 9500 3800
Wire Wire Line
	9350 3500 9500 3500
Wire Wire Line
	9300 4000 9500 4000
Wire Wire Line
	9500 4000 9500 3900
Connection ~ 9500 4000
Wire Wire Line
	5150 800  8250 800 
Wire Wire Line
	5150 800  5150 1650
Wire Wire Line
	5150 1650 5000 1650
Wire Wire Line
	5000 1250 5000 1350
Connection ~ 5150 1650
Wire Wire Line
	6050 1000 5700 1000
Wire Wire Line
	2300 900  2300 950 
Wire Wire Line
	2300 1250 2300 1300
Wire Wire Line
	7950 4200 7950 4250
Wire Wire Line
	7550 3700 7550 3450
Wire Wire Line
	7550 3450 7350 3450
Wire Wire Line
	7350 3550 7450 3550
Wire Wire Line
	7450 3550 7450 3800
Text Notes 8350 4350 0    60   ~ 0
SERCOM
Text Notes 9900 3850 0    60   ~ 0
LED DRV\n
Text Notes 8900 2950 0    60   ~ 0
PROG
Text Notes 9000 1550 0    60   ~ 0
ENC
Text Notes 9050 2050 0    60   ~ 0
BTN
$Comp
L GND #PWR015
U 1 1 57254F12
P 8550 2300
F 0 "#PWR015" H 8550 2050 50  0001 C CNN
F 1 "GND" H 8550 2150 50  0000 C CNN
F 2 "" H 8550 2300 60  0000 C CNN
F 3 "" H 8550 2300 60  0000 C CNN
	1    8550 2300
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 572556F6
P 7500 1250
F 0 "R2" V 7580 1250 50  0000 C CNN
F 1 "10k" V 7500 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7430 1250 30  0001 C CNN
F 3 "" H 7500 1250 30  0000 C CNN
	1    7500 1250
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 572557AB
P 7650 1250
F 0 "R3" V 7730 1250 50  0000 C CNN
F 1 "10k" V 7650 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7580 1250 30  0001 C CNN
F 3 "" H 7650 1250 30  0000 C CNN
	1    7650 1250
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 57255880
P 7800 1250
F 0 "R4" V 7880 1250 50  0000 C CNN
F 1 "10k" V 7800 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7730 1250 30  0001 C CNN
F 3 "" H 7800 1250 30  0000 C CNN
	1    7800 1250
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 572558F8
P 7950 1250
F 0 "R5" V 8030 1250 50  0000 C CNN
F 1 "10k" V 7950 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7880 1250 30  0001 C CNN
F 3 "" H 7950 1250 30  0000 C CNN
	1    7950 1250
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 5725596B
P 8100 1250
F 0 "R6" V 8180 1250 50  0000 C CNN
F 1 "10k" V 8100 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8030 1250 30  0001 C CNN
F 3 "" H 8100 1250 30  0000 C CNN
	1    8100 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 800  8250 3250
Wire Wire Line
	7500 1400 7500 1650
Connection ~ 7500 1650
Wire Wire Line
	7650 1400 7650 1750
Connection ~ 7650 1750
Wire Wire Line
	7800 1400 7800 1850
Connection ~ 7800 1850
Wire Wire Line
	7950 1400 7950 1950
Wire Wire Line
	8100 1400 8100 2050
Connection ~ 8100 2050
Connection ~ 7950 1950
Wire Wire Line
	7500 1100 8100 1100
Connection ~ 7950 1100
Connection ~ 7800 1100
Connection ~ 7650 1100
$Comp
L VCC #PWR016
U 1 1 572570A7
P 7500 1050
F 0 "#PWR016" H 7500 900 50  0001 C CNN
F 1 "VCC" H 7500 1200 50  0000 C CNN
F 2 "" H 7500 1050 60  0000 C CNN
F 3 "" H 7500 1050 60  0000 C CNN
	1    7500 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 1050 7500 1100
Connection ~ 7500 1100
$Comp
L CONN_01X02 P1
U 1 1 57259F23
P 700 1100
F 0 "P1" H 700 1250 50  0000 C CNN
F 1 "CONN_01X02" V 800 1100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 700 1100 60  0001 C CNN
F 3 "" H 700 1100 60  0000 C CNN
	1    700  1100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	900  950  900  1050
Wire Wire Line
	900  1150 900  1300
NoConn ~ 7350 2150
NoConn ~ 7350 2250
NoConn ~ 7350 2350
NoConn ~ 7350 2550
NoConn ~ 7350 2650
NoConn ~ 7350 2750
NoConn ~ 7350 2850
NoConn ~ 7350 2950
NoConn ~ 7350 3650
NoConn ~ 7350 3750
NoConn ~ 7350 3850
NoConn ~ 7350 3950
NoConn ~ 7350 4050
NoConn ~ 7350 4150
NoConn ~ 7350 4550
NoConn ~ 7350 4650
NoConn ~ 7350 4750
NoConn ~ 7350 4850
NoConn ~ 7350 4950
NoConn ~ 7350 5050
NoConn ~ 5150 2050
NoConn ~ 5150 2450
NoConn ~ 5150 2850
NoConn ~ 9500 3600
Wire Wire Line
	7950 4550 7900 4550
Wire Wire Line
	7900 4550 7900 4600
Wire Wire Line
	1750 1400 1550 1400
Connection ~ 1550 1400
Wire Wire Line
	8250 3250 8500 3250
Wire Wire Line
	8500 3150 7800 3150
Wire Wire Line
	7800 3150 7800 3250
Wire Wire Line
	7800 3250 7350 3250
Wire Wire Line
	8500 3050 7700 3050
Wire Wire Line
	7700 3050 7700 3150
Wire Wire Line
	7700 3150 7350 3150
Wire Wire Line
	8500 2950 7600 2950
Wire Wire Line
	7600 2950 7600 3050
Wire Wire Line
	7600 3050 7350 3050
Wire Wire Line
	7350 4450 7700 4450
Wire Wire Line
	7700 4450 7700 4350
Wire Wire Line
	7700 4350 7950 4350
Wire Wire Line
	7950 4450 7750 4450
Wire Wire Line
	7750 4450 7750 4500
Wire Wire Line
	7750 4500 7650 4500
Wire Wire Line
	7650 4500 7650 4350
Wire Wire Line
	7650 4350 7350 4350
$Comp
L CONN_01X04 P5
U 1 1 572B8B9B
P 8850 1600
F 0 "P5" H 8850 1850 50  0000 C CNN
F 1 "CONN_01X04" V 8950 1600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 8850 1600 50  0001 C CNN
F 3 "" H 8850 1600 50  0000 C CNN
	1    8850 1600
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P6
U 1 1 572B8BF6
P 8850 2150
F 0 "P6" H 8850 2350 50  0000 C CNN
F 1 "CONN_01X03" V 8950 2150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 8850 2150 50  0001 C CNN
F 3 "" H 8850 2150 50  0000 C CNN
	1    8850 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 1650 7350 1650
Wire Wire Line
	8300 1450 8300 1650
Wire Wire Line
	8400 1750 7350 1750
Wire Wire Line
	8400 1550 8400 1750
Wire Wire Line
	8500 1650 8500 1850
Wire Wire Line
	8500 1850 7350 1850
Wire Wire Line
	8300 2050 8300 2150
Wire Wire Line
	8300 2150 8650 2150
Wire Wire Line
	8400 1950 8400 2050
Wire Wire Line
	7350 1950 8400 1950
Wire Wire Line
	7350 2050 8300 2050
Wire Wire Line
	8400 2050 8650 2050
Wire Wire Line
	8300 1450 8650 1450
Wire Wire Line
	8400 1550 8650 1550
Wire Wire Line
	8500 1650 8650 1650
Wire Wire Line
	8650 1750 8550 1750
Wire Wire Line
	8550 1750 8550 2300
Wire Wire Line
	8550 2250 8650 2250
Connection ~ 8550 2250
Wire Wire Line
	8500 2750 8500 2850
$EndSCHEMATC