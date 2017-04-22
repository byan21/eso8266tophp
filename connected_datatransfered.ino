#include <SoftwareSerial.h> 
 
const byte rxPin = 0; // Wire this to Tx Pin of ESP8266 
const byte txPin = 1; // Wire this to Rx Pin of ESP8266 
int sensorPin = A0;
int sensorValue = 0;
 
// We'll use a software serial interface to connect to ESP8266 
SoftwareSerial ESP8266 (rxPin, txPin); 
 
void setup() { 
 pinMode(sensorPin, INPUT);
 ESP8266.begin(115200); // Change this to the baudrate used by ESP8266 
 //Serial.begin(115200);

  delay(1000); // Let the module self-initialize 
  ESP8266.write("AT+CWQAP\r\n"); 
  delay(10000);
  ESP8266.write("AT+RST\r\n"); 
  delay(5000); 
  ESP8266.write("AT+CWJAP=\"dwa\",\"sendokayu96\"\r\n"); 
  delay(10000); 

} 
 
void loop() {  
 sensorValue = analogRead(sensorPin);
 String data = String (sensorValue,DEC);

  ESP8266.write("AT+CIPSTART=\"TCP\",\"192.168.43.178\",80\r\n"); 
  delay(10000); 
  ESP8266.write("AT+CIPSEND=28\r\n"); 
  delay(4000); 
  ESP8266.println("GET /TA/kadar.php?kadar=" + data + "\r\n"); 
  delay(10000); 
    if (ESP8266.available()){ 
     ESP8266.write("Notifikasi telah terkirim!");   
  } 
}
