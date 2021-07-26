// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char THING_ID[] = "46b79b52-9a0e-405d-b45b-8cfe3fce2aa3";
const char DEVICE_LOGIN_NAME[] = "ceacd869-3489-4269-a7ab-28e7b9c78ce6";

const char SSID[] = SECRET_SSID;             // Network SSID (name)
const char PASS[] = SECRET_PASS;             // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[] = SECRET_DEVICE_KEY; // Secret device password

int DISTANCE;

int DISTANCE_1_A;
int DISTANCE_1_B;
bool SLOT_STATUS_1_A;
bool SLOT_STATUS_1_B;

int DISTANCE_2_A;
int DISTANCE_2_B;
bool SLOT_STATUS_2_A;
bool SLOT_STATUS_2_B;

void initProperties()
{
    ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
    ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
    ArduinoCloud.setThingId(THING_ID);
    ArduinoCloud.addProperty(DISTANCE, READ, 1 * SECONDS, NULL);

    ArduinoCloud.addProperty(DISTANCE_1_A, READ, 1 * SECONDS, NULL);
    ArduinoCloud.addProperty(DISTANCE_1_B, READ, 1 * SECONDS, NULL);
    ArduinoCloud.addProperty(SLOT_STATUS_1_A, READ, ON_CHANGE, NULL, 1);
    ArduinoCloud.addProperty(SLOT_STATUS_1_B, READ, ON_CHANGE, NULL, 1);

    ArduinoCloud.addProperty(DISTANCE_2_A, READ, 1 * SECONDS, NULL);
    ArduinoCloud.addProperty(DISTANCE_2_B, READ, 1 * SECONDS, NULL);
    ArduinoCloud.addProperty(SLOT_STATUS_2_A, READ, ON_CHANGE, NULL, 1);
    ArduinoCloud.addProperty(SLOT_STATUS_2_B, READ, ON_CHANGE, NULL, 1);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);