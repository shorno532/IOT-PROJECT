#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleDHT.h>
#include <Servo.h> // servo library  
 Servo s1; 
 
char auth[] = "WwlUqaMIlpbSZQ_ISNJBhrav_g67j7ds";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Galaxy A22 5G8a66";
char pass[] = "01318875292";
int pinDHT11 = 12;
 
//#define DHTPIN 12 
// D5-->nodemcu
SimpleDHT11 dht11(pinDHT11);


//DHT dht(DHTPIN,DHTTYPE);
BlynkTimer timer;
 

void sendSensor()
{
  float humidity = dht11.readHumidity();
  float temperature = dht11.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V5, temperature);
  Blynk.virtualWrite(V6, humidity);
}
 
void setup()
{
  s1.attach(5); // D1
  // Debug console
  Serial.begin(115200);
 
  Blynk.begin(auth, ssid, pass);
  
  dht11.begin();
 

  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  // working Servo 
  for(int i =0; i<=180;i++) 
  {
   s1.write(i);  
  delay(10);
  }
  for(int i =180; i>=0;i--) 
  {
   s1.write(i);  
  delay(10 );
  }
  
  Blynk.run();
  timer.run();
}
