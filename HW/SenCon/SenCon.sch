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
LIBS:SenCon-cache
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
L CONN_01X16 P1
U 1 1 581269E1
P 5825 1525
F 0 "P1" H 5825 2375 50  0000 C CNN
F 1 "BUS" V 5925 1525 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_2x08" H 5825 1525 50  0001 C CNN
F 3 "" H 5825 1525 50  0000 C CNN
	1    5825 1525
	1    0    0    -1  
$EndComp
Wire Bus Line
	5125 875  5125 2475
Entry Wire Line
	5125 875  5225 775 
Entry Wire Line
	5125 975  5225 875 
Entry Wire Line
	5125 1075 5225 975 
Entry Wire Line
	5125 1175 5225 1075
Entry Wire Line
	5125 1275 5225 1175
Entry Wire Line
	5125 1375 5225 1275
Entry Wire Line
	5125 1475 5225 1375
Entry Wire Line
	5125 1575 5225 1475
Entry Wire Line
	5125 1675 5225 1575
Entry Wire Line
	5125 1775 5225 1675
Entry Wire Line
	5125 1875 5225 1775
Entry Wire Line
	5125 1975 5225 1875
Entry Wire Line
	5125 2075 5225 1975
Entry Wire Line
	5125 2175 5225 2075
Entry Wire Line
	5125 2275 5225 2175
Entry Wire Line
	5125 2375 5225 2275
Text Label 5225 775  0    60   ~ 0
RESET
Text Label 5225 875  0    60   ~ 0
TXD
Text Label 5225 975  0    60   ~ 0
ADC
Text Label 5225 1075 0    60   ~ 0
RXD
Text Label 5225 1175 0    60   ~ 0
GPIO4
Text Label 5225 1275 0    60   ~ 0
GPIO16
Text Label 5225 1375 0    60   ~ 0
GPIO5
Text Label 5225 1475 0    60   ~ 0
GPIO14
Text Label 5225 1575 0    60   ~ 0
GPIO0
Text Label 5225 1675 0    60   ~ 0
GPIO12
Text Label 5225 1775 0    60   ~ 0
GPIO2
Text Label 5225 1875 0    60   ~ 0
GPIO13
Text Label 5225 1975 0    60   ~ 0
GPIO15
Text Label 5225 2075 0    60   ~ 0
VCC
Text Label 5225 2175 0    60   ~ 0
VDD
Text Label 5225 2275 0    60   ~ 0
GND
Wire Wire Line
	5225 775  5625 775 
Wire Wire Line
	5625 875  5225 875 
Wire Wire Line
	5225 975  5625 975 
Wire Wire Line
	5225 1075 5625 1075
Wire Wire Line
	5225 1175 5625 1175
Wire Wire Line
	5225 1275 5625 1275
Wire Wire Line
	5225 1375 5625 1375
Wire Wire Line
	5625 1475 5225 1475
Wire Wire Line
	5225 1575 5625 1575
Wire Wire Line
	5225 1675 5625 1675
Wire Wire Line
	5225 1775 5625 1775
Wire Wire Line
	5625 1875 5225 1875
Wire Wire Line
	5225 1975 5625 1975
Wire Wire Line
	5625 2075 5225 2075
Wire Wire Line
	5225 2175 5625 2175
Wire Wire Line
	5625 2275 5225 2275
Wire Bus Line
	6050 875  6050 2475
Entry Wire Line
	6050 875  6150 775 
Entry Wire Line
	6050 975  6150 875 
Entry Wire Line
	6050 1075 6150 975 
Entry Wire Line
	6050 1175 6150 1075
Entry Wire Line
	6050 1875 6150 1775
Entry Wire Line
	6050 1975 6150 1875
Entry Wire Line
	6050 2175 6150 2075
Entry Wire Line
	6050 2275 6150 2175
Entry Wire Line
	6050 2375 6150 2275
Text Label 6150 2175 0    60   ~ 0
GPIO4
Text Label 6150 775  0    60   ~ 0
GPIO14
Text Label 6150 875  0    60   ~ 0
GPIO12
Text Label 6150 975  0    60   ~ 0
GPIO13
Text Label 6150 2075 0    60   ~ 0
VCC
Text Label 6150 1075 0    60   ~ 0
GND
Wire Wire Line
	6150 775  6850 775 
Wire Wire Line
	6850 875  6150 875 
Wire Wire Line
	6150 975  6850 975 
Wire Wire Line
	6150 1075 6850 1075
Wire Wire Line
	6150 1775 6850 1775
Wire Wire Line
	6150 2075 6850 2075
Wire Wire Line
	6150 2175 6850 2175
Wire Wire Line
	6150 2275 6850 2275
$Comp
L CONN_01X04 P2
U 1 1 5814678C
P 7050 925
F 0 "P2" H 7050 1200 50  0000 C CNN
F 1 "Control" V 7150 925 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x04" H 7050 925 50  0001 C CNN
F 3 "" H 7050 925 50  0000 C CNN
	1    7050 925 
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 5847D0A7
P 7050 1825
F 0 "P3" H 7050 1975 50  0000 C CNN
F 1 "Switch" V 7150 1825 50  0000 C CNN
F 2 "suf_connector_ncw:CONN_NCW254-02S" H 7050 1825 50  0001 C CNN
F 3 "" H 7050 1825 50  0000 C CNN
	1    7050 1825
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P4
U 1 1 5847D0F0
P 7050 2175
F 0 "P4" H 7050 2375 50  0000 C CNN
F 1 "TSensor" V 7150 2175 50  0000 C CNN
F 2 "suf_connector_ncw:CONN_NCW254-03S" H 7050 2175 50  0001 C CNN
F 3 "" H 7050 2175 50  0000 C CNN
	1    7050 2175
	1    0    0    -1  
$EndComp
Text Label 6150 1775 0    60   ~ 0
VCC
Text Label 6150 2275 0    60   ~ 0
GND
$Comp
L R_Small R1
U 1 1 5847D2CD
P 6450 1575
F 0 "R1" H 6480 1595 50  0000 L CNN
F 1 "3,3K" H 6480 1535 50  0000 L CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" H 6450 1575 50  0001 C CNN
F 3 "" H 6450 1575 50  0000 C CNN
	1    6450 1575
	1    0    0    -1  
$EndComp
$Comp
L R_Small R2
U 1 1 5847D344
P 6800 1575
F 0 "R2" H 6830 1595 50  0000 L CNN
F 1 "3,3K" H 6830 1535 50  0000 L CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" H 6800 1575 50  0001 C CNN
F 3 "" H 6800 1575 50  0000 C CNN
	1    6800 1575
	1    0    0    -1  
$EndComp
$Comp
L C_Small C1
U 1 1 5847D37B
P 6450 2650
F 0 "C1" H 6460 2720 50  0000 L CNN
F 1 "1nF" H 6460 2570 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 6450 2650 50  0001 C CNN
F 3 "" H 6450 2650 50  0000 C CNN
	1    6450 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5847D920
P 6450 2825
F 0 "#PWR01" H 6450 2575 50  0001 C CNN
F 1 "GND" H 6450 2675 50  0000 C CNN
F 2 "" H 6450 2825 50  0000 C CNN
F 3 "" H 6450 2825 50  0000 C CNN
	1    6450 2825
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR02
U 1 1 5847D946
P 6450 1400
F 0 "#PWR02" H 6450 1250 50  0001 C CNN
F 1 "VCC" H 6450 1550 50  0000 C CNN
F 2 "" H 6450 1400 50  0000 C CNN
F 3 "" H 6450 1400 50  0000 C CNN
	1    6450 1400
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 5847D96C
P 6800 1400
F 0 "#PWR03" H 6800 1250 50  0001 C CNN
F 1 "VCC" H 6800 1550 50  0000 C CNN
F 2 "" H 6800 1400 50  0000 C CNN
F 3 "" H 6800 1400 50  0000 C CNN
	1    6800 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1400 6450 1475
Wire Wire Line
	6800 1400 6800 1475
Wire Wire Line
	6800 1675 6800 2175
Connection ~ 6800 2175
Wire Wire Line
	6450 2750 6450 2825
Wire Bus Line
	6050 2475 5125 2475
Wire Wire Line
	6150 1875 6850 1875
Wire Wire Line
	6450 1675 6450 2550
Connection ~ 6450 1875
Text Label 6150 1875 0    60   ~ 0
GPIO5
$EndSCHEMATC
