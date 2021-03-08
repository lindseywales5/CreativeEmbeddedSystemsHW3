#include <ESP32Servo.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "wifiname";
const char* password = "wifipass";
WiFiUDP Udp;
unsigned int localUdpPort = 4210; 
char incomingPacket[255];  
Servo myservo; 
int posVal = 0;
int servoPin = 15; 

void setup()
{
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 500, 2500);
  int status = WL_IDLE_STATUS;
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to wifi");
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  // we recv one packet from the remote so we can know its IP and port
  bool readPacket = false;
  while (!readPacket) {
    int packetSize = Udp.parsePacket();
    if (packetSize)
     {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      if (len > 0)
      {
        incomingPacket[len] = 0;
      }
      Serial.printf("UDP packet contents: %s\n", incomingPacket);
      readPacket = true;
    } 
  }
}

void loop()
{
  // once we know where we got the inital packet from, send data back to that IP address and port
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  // Just test touch pin - Touch0 is T0 which is on GPIO 4.
  Udp.printf(String(touchRead(T0)).c_str(),2);
  Udp.endPacket();
  delay(1000);

  bool readPacket = false;
  while (!readPacket) {
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      if (len > 0)
      {
        incomingPacket[len] = 0;
      }
      Serial.printf("UDP packet contents: %s\n", incomingPacket);
      if (strcmp(incomingPacket,"servo") == 0){
        for (posVal = 0; posVal <= 100; posVal += 1) { 
           myservo.write(posVal); 
           delay(15); 
        }
        for (posVal = 100; posVal >= 0; posVal -= 1) {
          myservo.write(posVal); 
          delay(15);                   
        }
      }
      readPacket = true;
    }
    else{
     readPacket = true;  
    }
  }
}
