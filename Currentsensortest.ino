// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>
 
// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
 
// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27;
 
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

#define SensorPin A0
#define VrefPin A1
#define BattPin A2
#define Vcc 5.0
#define ADCBits 1024   // 10-bit 
#define sensorconversionfactor 0.020   // 20mV/1A
#define multimeterVrefvalue 1.52     // used as voltage calibration

int sensorraw;
int vrefraw;
int battvoltraw;
int zeroampsraw;
float sensorvolt;
float vrefvolt;
float battvolt;
float vcccorrected;
float zeroampsvolt;
float current;
float battvoltcorr;
 
void setup()
{
 
  // Set display type as 16 char, 2 rows
  lcd.begin(20,4);
  
  // Print on first row
  lcd.setCursor(0,0);
  lcd.print("Hello");
  
  // Wait 1 second
  delay(2000);

  lcd.clear();

  pinMode(SensorPin,INPUT);  
  pinMode(VrefPin,INPUT);
  pinMode(BattPin,INPUT);  

  zeroampsraw=analogRead(SensorPin);  
  zeroampsvolt=(Vcc/1024)*zeroampsraw;
}
 
 
void loop()
{

sensorraw=analogRead(SensorPin);
vrefraw=analogRead(VrefPin);
battvoltraw=analogRead(BattPin);  

sensorvolt=(Vcc/ADCBits)*sensorraw;
vrefvolt=(Vcc/ADCBits)*vrefraw;
battvolt=(Vcc/ADCBits)*battvoltraw;

vcccorrected=(multimeterVrefvalue/vrefvolt)*Vcc;

current=(sensorvolt-zeroampsvolt)/sensorconversionfactor;
battvoltcorr=(multimeterVrefvalue/vrefvolt)*battvolt;

  lcd.setCursor(0,0);
  lcd.print(sensorraw);
  lcd.print("  ");
  lcd.print(sensorvolt,2);
  lcd.print("V");
  
  lcd.setCursor(0,1);
  lcd.print(vrefraw);
  lcd.print("  ");
  lcd.print(vrefvolt,2);
  lcd.print("V    ");  
  lcd.print(battvolt,2);
  lcd.print("V");

  lcd.setCursor(0,2);
  lcd.print("corrected Vcc: ");    
  lcd.print(vcccorrected);
  lcd.print("V");

  lcd.setCursor(0,3);
  lcd.print("                    ");
  lcd.setCursor(0,3);  
  lcd.print("Curr: ");    
  lcd.print(current,2);
  lcd.print("A   ");
  lcd.print(battvoltcorr,2);
  lcd.print("V");
  


  delay(2000);

}
