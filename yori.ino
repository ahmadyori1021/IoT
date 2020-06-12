#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h> 
#include <Servo.h>  
#include <DHT.h>

char auth[] = "v0NljV9QT8tr9z7XWT4QyX9XuH2WkKuH";
char ssid[] = "MDR";                  
char pass[] = "iniprivasi";
#define EspSerial Serial1              
#define ESP8266_BAUD 115200
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


ESP8266 wifi(&EspSerial);

static const int servoPin = 10;
Servo servo;
BLYNK_WRITE(V3) {
servo.write(param.asInt());
}

void sendSensor(){
  float t = dht.readTemperature();
  if(isnan(t)){
    Serial.println("Sensor gk kebaca");
    return;
  }
  Blynk.virtualWrite(V6, t);
}

void setup()
{
 Serial.begin(9600);
 delay(10);
 servo.attach(servoPin);
 
 EspSerial.begin(ESP8266_BAUD);
 delay(10);
 Blynk.begin(auth, wifi, ssid, pass);
 dht.begin();
 timer.setInterval(1000L, sendSensor);   
}
void loop()
{
  Blynk.run();
  timer.run();

  if(sendSensor > 31){
    Blynk.notify("ALERT : Suhu diatas 31 C !");
 
}
} 
