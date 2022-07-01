#include "HX711.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0X27,16,2);
// HX711.DOUT  - pin #A1
// HX711.PD_SCK - pin #A0
float KL = 0;
HX711 scale(A1, A0);    
int relay = 7;
int nut1 = 8;
int nut2 = 9;
int nut3 = 10;
int nut4 = 11;
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(38400);
  Serial.println("HX711 bắt đầu đọc");

  scale.set_scale(223.f);                      // chỉnh sai số đơn vị đo
  scale.tare();                                // reset đơn vị đo về 0
  pinMode(relay,OUTPUT);
  pinMode(nut1,INPUT);
  pinMode(nut2,INPUT);
  pinMode(nut3,INPUT);
  pinMode(nut4,INPUT);
  digitalWrite(relay,LOW);
  Serial.println("Bắt đầu:");
}

void loop() {
  Serial.print("Khối lượng đo là:\t ");
  Serial.print(scale.get_units(1),0);
  Serial.println("  g");
  KL=scale.get_units();                       //LẤY Giá trị cần để kích relay
int nut1Status = digitalRead(nut1);
int nut2Status = digitalRead(nut2);
int nut3Status = digitalRead(nut3);
int nut4Status = digitalRead(nut4);
  if (nut1Status == HIGH)
  {
    if (KL>85)
    {
    digitalWrite(relay,HIGH);
    Serial.println("==> ngắt điện 100g");
    lcd.setCursor(1,1);
    lcd.print("Da du 100g");
    } 
  else
   {
    digitalWrite(relay,LOW);
    Serial.println("==> mở điện");
    lcd.setCursor(1,1);
    lcd.print("..................");
   }
  
  }
  if (nut2Status == HIGH)
  {
    if (KL>185)
    {
    digitalWrite(relay,HIGH);
    Serial.println("==> ngắt điện 200g");
    lcd.setCursor(1,1);
    lcd.print("Da du 200g");
    } 
  else
   {
    digitalWrite(relay,LOW);
    Serial.println("==> mở điện");
    lcd.setCursor(1,1);
    lcd.print("..................");
   }
   if (nut3Status == HIGH)
  {
    if (KL>485)
    {
    digitalWrite(relay,HIGH);
    Serial.println("==> ngắt điện 500g");
    lcd.setCursor(1,1);
    lcd.print("Da du 500g");
    } 
  else
   {
    digitalWrite(relay,LOW);
    Serial.println("==> mở điện");
    lcd.setCursor(1,1);
    lcd.print("..................");
   }
  
  }
  if (nut4Status == HIGH)
  {
    if (KL>985)
    {
    digitalWrite(relay,HIGH);
    Serial.println("==> ngắt điện 1000g");
    lcd.setCursor(1,1);
    lcd.print("Da du 1000g");
    
    } 
  else
   {
    digitalWrite(relay,LOW);
    Serial.println("==> mở điện");
    lcd.setCursor(1,1);
    lcd.print("..................");
   }
  
  }
  scale.power_down();                       // đưa ADC in sleep mode
  delay(1);
  scale.power_up();
  lcd.setCursor(1,0);
  lcd.print("KL:");
  lcd.setCursor(6,0);
  lcd.print(scale.get_units() );
  lcd.setCursor(13,0);
  lcd.print("g");
}
}
