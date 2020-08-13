EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
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
L arduino:Arduino_Mega2560_Shield XA?
U 1 1 5F1536B2
P 4600 6200
F 0 "XA?" H 4600 3819 60  0000 C CNN
F 1 "Mega2560_Master" H 4600 3713 60  0000 C CNN
F 2 "" H 5300 8950 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 5300 8950 60  0001 C CNN
	1    4600 6200
	1    0    0    -1  
$EndComp
$Comp
L power:+7.5V #PWR?
U 1 1 5F15A0F8
P 1600 7950
F 0 "#PWR?" H 1600 7800 50  0001 C CNN
F 1 "+7.5V" H 1615 8123 50  0001 C CNN
F 2 "" H 1600 7950 50  0001 C CNN
F 3 "" H 1600 7950 50  0001 C CNN
	1    1600 7950
	1    0    0    -1  
$EndComp
$Comp
L Device:CP 0.1F
U 1 1 5F161B86
P 2950 9000
F 0 "0.1F" H 3068 9046 50  0000 L CNN
F 1 "5.5V" H 3068 8955 50  0000 L CNN
F 2 "" H 2988 8850 50  0001 C CNN
F 3 "~" H 2950 9000 50  0001 C CNN
	1    2950 9000
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 5F16471D
P 2950 9250
F 0 "#PWR?" H 2950 9000 50  0001 C CNN
F 1 "GNDD" H 2954 9095 50  0000 C CNN
F 2 "" H 2950 9250 50  0001 C CNN
F 3 "" H 2950 9250 50  0001 C CNN
	1    2950 9250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 5F16B65A
P 2050 8600
F 0 "R" H 2118 8646 50  0000 L CNN
F 1 "65K" H 2118 8555 50  0000 L CNN
F 2 "" V 2090 8590 50  0001 C CNN
F 3 "~" H 2050 8600 50  0001 C CNN
	1    2050 8600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 5F16DA8B
P 2050 9000
F 0 "R" H 2118 9046 50  0000 L CNN
F 1 "33K" H 2118 8955 50  0000 L CNN
F 2 "" V 2090 8990 50  0001 C CNN
F 3 "~" H 2050 9000 50  0001 C CNN
	1    2050 9000
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 5F16E203
P 2050 9250
F 0 "#PWR?" H 2050 9000 50  0001 C CNN
F 1 "GNDD" H 2054 9095 50  0000 C CNN
F 2 "" H 2050 9250 50  0001 C CNN
F 3 "" H 2050 9250 50  0001 C CNN
	1    2050 9250
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 5F16E83A
P 2450 9250
F 0 "#PWR?" H 2450 9000 50  0001 C CNN
F 1 "GNDD" H 2454 9095 50  0000 C CNN
F 2 "" H 2450 9250 50  0001 C CNN
F 3 "" H 2450 9250 50  0001 C CNN
	1    2450 9250
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C
U 1 1 5F16EF5B
P 2450 9000
F 0 "C" H 2542 9046 50  0000 L CNN
F 1 "100n" H 2542 8955 50  0000 L CNN
F 2 "" H 2450 9000 50  0001 C CNN
F 3 "~" H 2450 9000 50  0001 C CNN
	1    2450 9000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C
U 1 1 5F16F706
P 2050 8200
F 0 "C" H 2142 8246 50  0000 L CNN
F 1 "100n" H 2142 8155 50  0000 L CNN
F 2 "" H 2050 8200 50  0001 C CNN
F 3 "~" H 2050 8200 50  0001 C CNN
	1    2050 8200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 5F16FE53
P 2050 7950
F 0 "#PWR?" H 2050 7700 50  0001 C CNN
F 1 "GNDD" H 2054 7795 50  0000 C CNN
F 2 "" H 2050 7950 50  0001 C CNN
F 3 "" H 2050 7950 50  0001 C CNN
	1    2050 7950
	1    0    0    1   
$EndComp
Wire Wire Line
	2050 7950 2050 8100
Wire Wire Line
	2050 8300 2050 8350
Wire Wire Line
	2050 8750 2050 8800
Wire Wire Line
	2050 9150 2050 9250
Wire Wire Line
	2450 9100 2450 9250
Wire Wire Line
	1600 7950 1600 8350
Wire Wire Line
	2950 9150 2950 9200
Wire Wire Line
	2450 8900 2450 8800
Wire Wire Line
	2450 4250 3300 4250
Connection ~ 2050 8800
Wire Wire Line
	2050 8800 2050 8850
Wire Wire Line
	2050 8800 2450 8800
Connection ~ 2450 8800
Wire Wire Line
	2450 8800 2450 4250
Text Label 2500 8750 0    50   ~ 0
4V
Text Label 1550 7800 0    50   ~ 0
+12V
$Comp
L arduino:Arduino_101_Shield XA?
U 1 1 5F1754BA
P 8250 5100
F 0 "XA?" H 8250 6487 60  0000 C CNN
F 1 "Ethernet shield" H 8250 6381 60  0000 C CNN
F 2 "" H 10050 8850 60  0001 C CNN
F 3 "https://store.arduino.cc/genuino-101" H 10050 8850 60  0001 C CNN
	1    8250 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3600 4350 2950
Wire Wire Line
	4350 2950 10400 2950
Wire Wire Line
	10400 2950 10400 5350
Wire Wire Line
	10400 5350 9550 5350
Wire Wire Line
	4450 3600 4450 3000
Wire Wire Line
	4450 3000 10350 3000
Wire Wire Line
	10350 3000 10350 5450
Wire Wire Line
	10350 5450 9550 5450
Wire Wire Line
	4550 3600 4550 3050
Wire Wire Line
	4550 3050 10300 3050
Wire Wire Line
	10300 3050 10300 5550
Wire Wire Line
	10300 5550 9550 5550
Wire Wire Line
	4750 3600 4750 3100
Wire Wire Line
	4750 3100 10250 3100
Wire Wire Line
	10250 3100 10250 5750
Wire Wire Line
	10250 5750 9550 5750
Wire Wire Line
	5900 4250 6450 4250
Wire Wire Line
	6450 4250 6450 3250
Wire Wire Line
	6450 3250 10000 3250
Wire Wire Line
	10000 3250 10000 4250
Wire Wire Line
	10000 4250 9550 4250
Wire Wire Line
	5900 4850 6550 4850
Wire Wire Line
	6550 4850 6550 3300
Wire Wire Line
	6550 3300 9950 3300
Wire Wire Line
	9950 3300 9950 4850
Wire Wire Line
	9950 4850 9550 4850
$Comp
L arduino:Arduino_Mega2560_Shield XA?
U 1 1 5F1AD433
P 12650 6150
F 0 "XA?" H 12650 3769 60  0000 C CNN
F 1 "Mega2560_Slave" H 12650 3663 60  0000 C CNN
F 2 "" H 13350 8900 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 13350 8900 60  0001 C CNN
	1    12650 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 5850 6350 5850
Wire Wire Line
	6350 5850 6350 3250
Wire Wire Line
	6350 3250 2600 3250
Wire Wire Line
	2600 3250 2600 7150
Wire Wire Line
	2600 7150 3300 7150
Wire Wire Line
	11350 7900 6750 7900
Wire Wire Line
	6750 7900 6750 5950
Wire Wire Line
	6750 5950 6950 5950
Wire Wire Line
	11350 8000 6600 8000
Wire Wire Line
	6600 8000 6600 6050
Wire Wire Line
	6600 6050 6950 6050
Wire Wire Line
	3300 7850 3200 7850
Wire Wire Line
	3200 7850 3200 8800
Wire Wire Line
	3200 8800 11000 8800
Wire Wire Line
	11000 8800 11000 7800
Wire Wire Line
	11000 7800 11350 7800
Wire Wire Line
	3200 8800 3200 9200
Wire Wire Line
	3200 9200 2950 9200
Connection ~ 3200 8800
Connection ~ 2950 9200
Wire Wire Line
	2950 9200 2950 9250
$Comp
L power:GNDD #PWR?
U 1 1 5F1D3831
P 11000 9250
F 0 "#PWR?" H 11000 9000 50  0001 C CNN
F 1 "GNDD" H 11004 9095 50  0000 C CNN
F 2 "" H 11000 9250 50  0001 C CNN
F 3 "" H 11000 9250 50  0001 C CNN
	1    11000 9250
	1    0    0    -1  
$EndComp
Wire Wire Line
	11000 8800 11000 9250
Connection ~ 11000 8800
Wire Wire Line
	3300 4850 3050 4850
Wire Wire Line
	3050 4850 3050 2650
Wire Wire Line
	3050 2650 11000 2650
Wire Wire Line
	11000 2650 11000 4800
Wire Wire Line
	11000 4800 11350 4800
Wire Wire Line
	3300 4950 2950 4950
Wire Wire Line
	2950 4950 2950 2550
Wire Wire Line
	2950 2550 10900 2550
Wire Wire Line
	10900 2550 10900 4900
Wire Wire Line
	10900 4900 11350 4900
Text Label 10650 7600 0    50   ~ 0
+12V
$Comp
L power:+7.5V #PWR?
U 1 1 5F1D9EF2
P 10750 7750
F 0 "#PWR?" H 10750 7600 50  0001 C CNN
F 1 "+7.5V" H 10765 7923 50  0001 C CNN
F 2 "" H 10750 7750 50  0001 C CNN
F 3 "" H 10750 7750 50  0001 C CNN
	1    10750 7750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11350 8300 10750 8300
Wire Wire Line
	10750 8300 10750 7750
$Comp
L Switch:SW_Push Reset_to_default
U 1 1 5F232A58
P 5800 3650
F 0 "Reset_to_default" H 5800 3935 50  0000 C CNN
F 1 "SW_Push" H 5800 3844 50  0000 C CNN
F 2 "" H 5800 3850 50  0001 C CNN
F 3 "~" H 5800 3850 50  0001 C CNN
	1    5800 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4350 6150 4350
Wire Wire Line
	6150 4350 6150 3650
Wire Wire Line
	6150 3650 6000 3650
$Comp
L power:GNDD #PWR?
U 1 1 5F236A1A
P 5400 3650
F 0 "#PWR?" H 5400 3400 50  0001 C CNN
F 1 "GNDD" H 5404 3495 50  0000 C CNN
F 2 "" H 5400 3650 50  0001 C CNN
F 3 "" H 5400 3650 50  0001 C CNN
	1    5400 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	5400 3650 5600 3650
Wire Wire Line
	1600 8350 2050 8350
Connection ~ 2050 8350
Wire Wire Line
	2050 8350 2050 8450
Wire Wire Line
	2950 8350 3300 8350
Wire Wire Line
	2950 8350 2950 8850
Text Label 2850 7800 0    50   ~ 0
+5V
$Comp
L power:+7.5V #PWR?
U 1 1 5F16F920
P 2950 7950
F 0 "#PWR?" H 2950 7800 50  0001 C CNN
F 1 "+7.5V" H 2965 8123 50  0001 C CNN
F 2 "" H 2950 7950 50  0001 C CNN
F 3 "" H 2950 7950 50  0001 C CNN
	1    2950 7950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 7950 2950 8350
Connection ~ 2950 8350
$EndSCHEMATC
