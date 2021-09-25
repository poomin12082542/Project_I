#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define DHTPIN   D4  // DHT22 Sensor            
#define DHTTYPE DHT22           // DHT22 if useDHT22
#define BLYNK_PRINT Serial

char auth[] = "DTXKhyTaUCbWVJbr2rojaPCEQ2GfRdz1";
char ssid[] = "Min'Laptop";
char pass[] = "12082542";

int MotorPin2 = D2;
int MotorPin3 = D3;
int Limswitch1 = D4;
int Limswitch2 = D5;
int Steam = D6;
int flag1 = 0;
int flag2 = 0;

BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorPin3, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  delay(500);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(" C ");   
  Blynk.run();
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, t);
  if ((h > 80) = (Limswitch1)==LOW) )
 {
  collect();
  flag2 = 1;
  if(((Limswitch2)==HIGH)&&( flag2 = 1) )
  {
    steam();
  }
 }
BLYNK_WRITE(V0) {
   if(param.asInt() == 1)
  {
   collect();
  }
}
BLYNK_WRITE(V1) {
   if(param.asInt() == 1)
  {
   dry();
  }
}
BLYNK_WRITE(V2) {
   if(param.asInt() == 1)
  {
    flag2 = 1;
    steam();
  }
}
} 

void collect(){
  digitalWrite(MotorPin2, HIGH); 
  digitalWrite(MotorPin3, LOW); 
  Blynk.virtualWrite(V4, "collecting");
  Serial.print("  เก็บผ้า\n");
  if ((digitalRead(Limswitch1)==HIGH)&&(flag1==0))
  {
    digitalWrite(MotorPin2, LOW); 
    digitalWrite(MotorPin3, LOW); 
    flag1 = 1;
  }
}

void dry(){
  digitalWrite(MotorPin2, LOW); 
  digitalWrite(MotorPin3, HIGH); 
  Blynk.virtualWrite(V4, "drying");
  Serial.print("  ตากผ้า\n");
   if ((digitalRead(Limswitch2)==HIGH)&&(flag1==1))
  {
    digitalWrite(MotorPin2, LOW); 
    digitalWrite(MotorPin3, LOW); 
    flag1 = 0;
  }
}

void steam(){
  digitalWrite(Steam, HIGH);
  Blynk.virtualWrite(V4, "Steaming");
  Serial.print("  อบผ้า\n"); 
  delay(3600000);
  digitalWrite(Steam, LOW); 
  flag2 = 0;
}
