#include <Wire.h>

#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C_ByVac.h>
#include <LiquidCrystal_SI2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR1W.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include <SI2CIO.h>
#include <SoftI2CMaster.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


void setup() {
 lcd.begin(16,3); 
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
 lcd.print("City: ");
    lcd.print("Stockholm");
    lcd.setCursor(0,1);
    lcd.print("Weather: ");
    lcd.print("Rain");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print("10 ");
    //för att få ut specialtecken.
    lcd.print((char) 223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Awesome :)");
    delay(2000);
    lcd.clear();
}
