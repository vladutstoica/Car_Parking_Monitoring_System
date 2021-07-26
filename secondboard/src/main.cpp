#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#include "wifiSecrets.h"

// Define HC-SR04 A pins
const int triggerPinA = D1;
const int echoPinA = D2;

// Define HC-SR04 B pins
const int triggerPinB = D5;
const int echoPinB = D6;

// Define LEDs A
const int rLEDA = D3;
const int vLEDA = D4;

// Define LEDs B
const int rLEDB = D7;
const int vLEDB = D8;

// Define variables
int DISTANCE_A;
int DISTANCE_B;
long DURATION_A;
long DURATION_B;
bool slotStatusA;
bool slotStatusB;

void sensorSetupA();
void sensorSetupB();
void statusA();
void statusB();

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message
{
  int id;
  int distanceA;
  int distanceB;
  bool slotStatusA;
  bool slotStatusB;
} struct_message;

// Create a struct_message to store variables to be sent
struct_message senderData;

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus)
{
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0)
  {
    Serial.println("Delivery success\r\n");
  }
  else
  {
    Serial.println("Delivery fail\r\n");
  }
}

void WiFiSetup()
{
  // Config WiFi as STATION
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Set ESP-NOW role
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  // Once ESPNow is successfully init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void WiFiConfig()
{
  if ((millis() - lastTime) > timerDelay)
  {
    // Set values to send
    senderData.id = BOARD_ID;
    senderData.distanceA = DISTANCE_A;
    senderData.distanceB = DISTANCE_B;
    senderData.slotStatusA = slotStatusA;
    senderData.slotStatusB = slotStatusB;

    // Send message via ESP-NOW
    esp_now_send(0, (uint8_t *)&senderData, sizeof(senderData));
    lastTime = millis();
  }
}

void setup()
{
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Define HC-SR04 A pins status
  pinMode(triggerPinA, OUTPUT);
  pinMode(echoPinA, INPUT);

  // Define HC-SR04 B pins status
  pinMode(triggerPinB, OUTPUT);
  pinMode(echoPinB, INPUT);

  // Define LEDs A pins status
  pinMode(rLEDA, OUTPUT);
  pinMode(vLEDA, OUTPUT);

  // Define LEDs B pins status
  pinMode(rLEDB, OUTPUT);
  pinMode(vLEDB, OUTPUT);

  WiFiSetup();
}

void loop()
{
  sensorSetupA();
  sensorSetupB();

  statusA();
  statusB();

  WiFiConfig();

  delay(4000);
}

void sensorSetupA()
{
  // Clears the triggerPinA
  digitalWrite(triggerPinA, LOW);
  delayMicroseconds(2);

  // Sets the triggerPinA on HIGH state for 10 micro seconds
  digitalWrite(triggerPinA, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPinA, LOW);

  // Reads the echoPinA, returns the sound wave travel time in microseconds
  DURATION_A = pulseIn(echoPinA, HIGH);

  // Calculating the distance for HC-SR04 A
  DISTANCE_A = DURATION_A * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Sensor A distance: ");
  Serial.print(DISTANCE_A);
  Serial.println(" cm.");
}

void sensorSetupB()
{
  // Clears the triggerPinB
  digitalWrite(triggerPinB, LOW);
  delayMicroseconds(2);

  // Sets the triggerPinB on HIGH state for 10 micro seconds
  digitalWrite(triggerPinB, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPinB, LOW);

  // Reads the echoPinB, returns the sound wave travel time in microseconds
  DURATION_B = pulseIn(echoPinB, HIGH);

  // Calculating the distance for HC-SR04 B
  DISTANCE_B = DURATION_B * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Sensor B distance: ");
  Serial.print(DISTANCE_B);
  Serial.println(" cm.");
}

void statusA()
{
  if (DISTANCE_A > 10)
  {
    // Slot A is available
    slotStatusA = true;

    // Power OFF red light
    digitalWrite(rLEDA, LOW);
    // Power ON green light
    digitalWrite(vLEDA, HIGH);
  }
  else
  {
    // Slot A is busy
    slotStatusA = false;

    // Power ON red light
    digitalWrite(rLEDA, HIGH);
    // Power OFF green light
    digitalWrite(vLEDA, LOW);
  }
}

void statusB()
{
  if (DISTANCE_B > 10)
  {
    // Slot B is available
    slotStatusB = true;

    // Power OFF red light
    digitalWrite(rLEDB, LOW);
    // Power ON green light
    digitalWrite(vLEDB, HIGH);
  }
  else
  {
    // Slot B is busy
    slotStatusB = false;

    // Power ON red light
    digitalWrite(rLEDB, HIGH);
    // Power OFF green light
    digitalWrite(vLEDB, LOW);
  }
}