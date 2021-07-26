#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#include "wifiSecrets.h"
#include "thingProperties.h"

// Define HC-SR04
const int triggerPin = D1;
const int echoPin = D2;

// Define SG90
Servo servo;
int servoAngle;
const int controlPin = D3;

// Define LED
const int bLED = D5;

// Define variables
long DURATION;

void sensorSetup();
void transferDataToVariables(int id);

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message
{
  int id;
  int distanceA;
  int distanceB;
  bool slotStatusA;
  bool slotStatusB;
} struct_message;

// Create a struct_message called receiverData
struct_message receiverData;

// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;

// Create an array with all the structures
struct_message boardsStruct[2] = {board1, board2};

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t *mac_addr, uint8_t *incomingData, uint8_t len)
{
  char macStr[18];
  Serial.print("\r\nPacket received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&receiverData, incomingData, sizeof(receiverData));
  Serial.printf("Board ID %u: %u bytes\n", receiverData.id, len);

  // Update the structures with the new incoming data
  boardsStruct[receiverData.id - 1].distanceA = receiverData.distanceA;
  boardsStruct[receiverData.id - 1].distanceB = receiverData.distanceB;
  boardsStruct[receiverData.id - 1].slotStatusA = receiverData.slotStatusA;
  boardsStruct[receiverData.id - 1].slotStatusB = receiverData.slotStatusB;

  transferDataToVariables(receiverData.id);
}

void WiFiSetup()
{
  // Config WiFi as AP STATION
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void setup()
{
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Define HC-SR04 pins status
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Define SG90 pin status
  servo.attach(controlPin);

  // Define LED pin status
  pinMode(bLED, OUTPUT);

  WiFiSetup();

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop()
{
  ArduinoCloud.update();

  sensorSetup();

  if (DISTANCE < 20 && 1 < DISTANCE)
  {
    servo.write(180);
  }
  else
  {
    servo.write(0);
  }

  delay(1000);
}

void sensorSetup()
{
  // Clears the triggerPin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // Sets the triggerPin on HIGH state for 10 micro seconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  DURATION = pulseIn(echoPin, HIGH);

  // Calculating the distance for HC-SR04
  DISTANCE = DURATION * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Sensor distance: ");
  Serial.print(DISTANCE);
  Serial.println(" cm.");
}

void transferDataToVariables(int id)
{
  switch (id)
  {
  case 1:
  {
    Serial.printf("Slot A status: %d \n", boardsStruct[id - 1].slotStatusA);
    Serial.printf("Slot A distance: %d \n", boardsStruct[id - 1].distanceA);
    Serial.printf("Slot B status: %d \n", boardsStruct[id - 1].slotStatusB);
    Serial.printf("Slot B distance: %d \n", boardsStruct[id - 1].distanceB);
    Serial.println();

    DISTANCE_1_A = boardsStruct[id - 1].distanceA;
    DISTANCE_1_B = boardsStruct[id - 1].distanceB;
    SLOT_STATUS_1_A = boardsStruct[id - 1].slotStatusA;
    SLOT_STATUS_1_B = boardsStruct[id - 1].slotStatusB;

    break;
  }

  case 2:
  {
    Serial.printf("Slot A status: %d \n", boardsStruct[id - 1].slotStatusA);
    Serial.printf("Slot A distance: %d \n", boardsStruct[id - 1].distanceA);
    Serial.printf("Slot B status: %d \n", boardsStruct[id - 1].slotStatusB);
    Serial.printf("Slot B distance: %d \n", boardsStruct[id - 1].distanceB);
    Serial.println();

    DISTANCE_2_A = boardsStruct[receiverData.id - 1].distanceA;
    DISTANCE_2_B = boardsStruct[receiverData.id - 1].distanceB;
    SLOT_STATUS_2_A = boardsStruct[receiverData.id - 1].slotStatusA;
    SLOT_STATUS_2_B = boardsStruct[receiverData.id - 1].slotStatusB;

    break;
  }

  default:
  {
    Serial.printf("ID out of range.");
    Serial.printf("Please make sure the stations boards ids match this board ids.");

    break;
  }
  }
}
