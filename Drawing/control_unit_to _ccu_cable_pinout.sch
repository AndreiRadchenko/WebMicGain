EESchema Schematic File Version 4
EELAYER 30 0
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
L Connector:DB25_Male Control_Unit
U 1 1 5F0EE4E7
P 1650 4300
F 0 "Control_Unit" H 1568 2808 50  0000 C CNN
F 1 "DB25_Male" H 1568 2899 50  0000 C CNN
F 2 "" H 1650 4300 50  0001 C CNN
F 3 " ~" H 1650 4300 50  0001 C CNN
	1    1650 4300
	-1   0    0    1   
$EndComp
Text Label 4950 2000 0    50   ~ 0
GND
Text Label 4850 1300 0    50   ~ 0
CONT2
Text Label 4850 1100 0    50   ~ 0
CONT1
Text Label 4850 900  0    50   ~ 0
CONT0
Text Label 4750 800  0    50   ~ 0
MIC2CTRL
Text Label 4750 700  0    50   ~ 0
MIC1CTRL
$Comp
L Connector:DB15_Male CCU1
U 1 1 5F0F63DE
P 5450 1400
F 0 "CCU1" H 5605 1446 50  0000 L CNN
F 1 "DB15_Male" H 5605 1355 50  0000 L CNN
F 2 "" H 5450 1400 50  0001 C CNN
F 3 " ~" H 5450 1400 50  0001 C CNN
	1    5450 1400
	1    0    0    -1  
$EndComp
Text Label 4950 3700 0    50   ~ 0
GND
Text Label 4850 3000 0    50   ~ 0
CONT2
Text Label 4850 2800 0    50   ~ 0
CONT1
Text Label 4850 2600 0    50   ~ 0
CONT0
Text Label 4750 2500 0    50   ~ 0
MIC2CTRL
Text Label 4750 2400 0    50   ~ 0
MIC1CTRL
$Comp
L Connector:DB15_Male CCU2
U 1 1 5F117791
P 5450 3100
F 0 "CCU2" H 5605 3146 50  0000 L CNN
F 1 "DB15_Male" H 5605 3055 50  0000 L CNN
F 2 "" H 5450 3100 50  0001 C CNN
F 3 " ~" H 5450 3100 50  0001 C CNN
	1    5450 3100
	1    0    0    -1  
$EndComp
Text Label 5850 5650 0    50   ~ 0
GND
Text Label 5750 4950 0    50   ~ 0
CONT2
Text Label 5750 4750 0    50   ~ 0
CONT1
Text Label 5750 4550 0    50   ~ 0
CONT0
Text Label 5650 4450 0    50   ~ 0
MIC2CTRL
Text Label 5650 4350 0    50   ~ 0
MIC1CTRL
$Comp
L Connector:DB15_Male CCU3
U 1 1 5F1189F7
P 6350 5050
F 0 "CCU3" H 6505 5096 50  0000 L CNN
F 1 "DB15_Male" H 6505 5005 50  0000 L CNN
F 2 "" H 6350 5050 50  0001 C CNN
F 3 " ~" H 6350 5050 50  0001 C CNN
	1    6350 5050
	1    0    0    -1  
$EndComp
Text Label 5850 7450 0    50   ~ 0
GND
Text Label 5750 6750 0    50   ~ 0
CONT2
Text Label 5750 6550 0    50   ~ 0
CONT1
Text Label 5750 6350 0    50   ~ 0
CONT0
Text Label 5650 6250 0    50   ~ 0
MIC2CTRL
Text Label 5650 6150 0    50   ~ 0
MIC1CTRL
$Comp
L Connector:DB15_Male CCU4
U 1 1 5F11A66C
P 6350 6850
F 0 "CCU4" H 6505 6896 50  0000 L CNN
F 1 "DB15_Male" H 6505 6805 50  0000 L CNN
F 2 "" H 6350 6850 50  0001 C CNN
F 3 " ~" H 6350 6850 50  0001 C CNN
	1    6350 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 3100 2850 3100
Wire Wire Line
	2850 3100 2850 700 
Wire Wire Line
	2850 700  5150 700 
Wire Wire Line
	1950 3300 2900 3300
Wire Wire Line
	2900 3300 2900 800 
Wire Wire Line
	2900 800  5150 800 
Wire Wire Line
	1950 3500 2950 3500
Wire Wire Line
	2950 3500 2950 900 
Wire Wire Line
	2950 900  5150 900 
Wire Wire Line
	1950 3700 3000 3700
Wire Wire Line
	3000 3700 3000 1100
Wire Wire Line
	3000 1100 5150 1100
Wire Wire Line
	1950 3900 3050 3900
Wire Wire Line
	3050 3900 3050 1300
Wire Wire Line
	3050 1300 5150 1300
Wire Wire Line
	1950 4100 3100 4100
Wire Wire Line
	3100 4100 3100 2000
Wire Wire Line
	3100 2000 5150 2000
Wire Wire Line
	1950 4300 3300 4300
Wire Wire Line
	3300 2400 5150 2400
Wire Wire Line
	1950 4500 3350 4500
Wire Wire Line
	3350 2500 5150 2500
Wire Wire Line
	1950 4700 3400 4700
Wire Wire Line
	3400 2600 5150 2600
Wire Wire Line
	1950 4900 3450 4900
Wire Wire Line
	3450 2800 5150 2800
Wire Wire Line
	1950 5100 3500 5100
Wire Wire Line
	3500 3000 5150 3000
Wire Wire Line
	1950 5300 3550 5300
Wire Wire Line
	1950 3200 4550 3200
Wire Wire Line
	4550 3200 4550 4350
Wire Wire Line
	4550 4350 6050 4350
Wire Wire Line
	1950 3400 4500 3400
Wire Wire Line
	4500 3400 4500 4450
Wire Wire Line
	4500 4450 6050 4450
Wire Wire Line
	1950 3600 4450 3600
Wire Wire Line
	4450 3600 4450 4550
Wire Wire Line
	4450 4550 6050 4550
Wire Wire Line
	4400 3800 4400 4750
Wire Wire Line
	4400 4750 6050 4750
Wire Wire Line
	3300 2400 3300 4300
Wire Wire Line
	3350 2500 3350 4500
Wire Wire Line
	3400 2600 3400 4700
Wire Wire Line
	3450 2800 3450 4900
Wire Wire Line
	3500 3000 3500 5100
Wire Wire Line
	1950 3800 4400 3800
Wire Wire Line
	3550 5300 3550 3700
Wire Wire Line
	3550 3700 5150 3700
Wire Wire Line
	1950 4000 4350 4000
Wire Wire Line
	4350 4000 4350 4950
Wire Wire Line
	4350 4950 6050 4950
Wire Wire Line
	1950 4200 4300 4200
Wire Wire Line
	4300 4200 4300 5650
Wire Wire Line
	4300 5650 6050 5650
Wire Wire Line
	1950 4400 4100 4400
Wire Wire Line
	4100 4400 4100 6150
Wire Wire Line
	4100 6150 6050 6150
Wire Wire Line
	1950 4600 4050 4600
Wire Wire Line
	4050 4600 4050 6250
Wire Wire Line
	4050 6250 6050 6250
Wire Wire Line
	1950 4800 4000 4800
Wire Wire Line
	4000 4800 4000 6350
Wire Wire Line
	4000 6350 6050 6350
Wire Wire Line
	1950 5000 3950 5000
Wire Wire Line
	3950 5000 3950 6550
Wire Wire Line
	3950 6550 6050 6550
Wire Wire Line
	1950 5200 3900 5200
Wire Wire Line
	3900 6750 6050 6750
Wire Wire Line
	3900 5200 3900 6750
Wire Wire Line
	1950 5400 3850 5400
Wire Wire Line
	3850 5400 3850 7450
Wire Wire Line
	3850 7450 6050 7450
Text Label 1950 3100 0    39   ~ 0
CCU1(8)
Text Label 1950 3300 0    39   ~ 0
CCU1(15)
Text Label 1950 3500 0    39   ~ 0
CCU1(7)
Text Label 1950 3700 0    39   ~ 0
CCU1(6)
Text Label 1950 3900 0    39   ~ 0
CCU1(5)
Text Label 1950 4100 0    39   ~ 0
CCU1(9)
Text Label 1950 4300 0    39   ~ 0
CCU2(8)
Text Label 1950 4500 0    39   ~ 0
CCU2(15)
Text Label 1950 4700 0    39   ~ 0
CCU2(7)
Text Label 1950 4900 0    39   ~ 0
CCU2(6)
Text Label 1950 5100 0    39   ~ 0
CCU2(5)
Text Label 1950 5300 0    39   ~ 0
CCU2(9)
Text Label 1950 3200 0    39   ~ 0
CCU3(8)
Text Label 1950 3400 0    39   ~ 0
CCU3(15)
Text Label 1950 3600 0    39   ~ 0
CCU3(7)
Text Label 1950 3800 0    39   ~ 0
CCU3(6)
Text Label 1950 4000 0    39   ~ 0
CCU3(5)
Text Label 1950 4200 0    39   ~ 0
CCU3(9)
Text Label 1950 4400 0    39   ~ 0
CCU4(8)
Text Label 1950 4600 0    39   ~ 0
CCU4(15)
Text Label 1950 4800 0    39   ~ 0
CCU4(7)
Text Label 1950 5000 0    39   ~ 0
CCU4(6)
Text Label 1950 5200 0    39   ~ 0
CCU4(5)
Text Label 1950 5400 0    39   ~ 0
CCU4(9)
Text Notes 7250 6850 0    118  ~ 0
Control Unit to Sony CCU cable pinout
$EndSCHEMATC
