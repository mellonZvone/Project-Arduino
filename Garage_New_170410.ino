#include <BlynkSimpleStream.h>
#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <NewPing.h>

char auth[] = "f077671f2aff4952b93904cf95553960";

#define DHTPIN 2          // What digital pin we're connected to
#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 
#define PING_INTERVAL 200 // Milliseconds between pings.
#define DHTTYPE DHT11     // DHT 11

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
WidgetLCD lcd(V0);
WidgetLED led1(V6);
WidgetLED led2(V9);
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

const int relaySwitch1 = V7;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void ultra()
{
  unsigned int uS = sonar.ping();
  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(1,1,"Distance:");
  lcd.print(10,1,(uS / US_ROUNDTRIP_CM));
}

BLYNK_WRITE (1){
  digitalWrite(relaySwitch1, HIGH);
  }

void checkPin()
{
  if (digitalRead(4)) // GPIO4
  {
    led1.off();
    led2.off();

  } else {
    led1.on();
    led2.on();
  }
}

void garageMagSensor ()
{
  int garageSensorSW = digitalRead(4); // GPIO4
  if (garageSensorSW == LOW)
  {
    Blynk.virtualWrite(0, "CLOSE"); 
    Blynk.virtualWrite(1, "CLOSE"); 
    lcd.print(1, 0, "GARAGE IS CLOSED"); // LCD print, column 1, row 0.
  }
  else
  {
    Blynk.virtualWrite(0, "OPEN"); 
    Blynk.virtualWrite(1, "OPEN"); 
    lcd.print(1, 0, "GARAGE IS OPEN"); // LCD print, column 1, row 0
    
  }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, ultra);
  timer.setInterval(1000L, garageMagSensor);
  pinMode(relaySwitch1, OUTPUT);
  pinMode(4, INPUT_PULLUP);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}

