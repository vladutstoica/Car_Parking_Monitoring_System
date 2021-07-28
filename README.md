# Car_Parking_Monitoring_System
The idea behind this project proposes the development of a parking command and control system, in order to facilitate the management of parking spaces and reduce the number of illegally parked vehicles. The project is divided into three systems: the management system, the parking place system and the barrier system. These systems are interconnected and transmit information in real time to act as soon as possible when a vehicle enters the parking lot.

![Illustration](https://user-images.githubusercontent.com/23508982/127334027-4eaaeb42-460e-4bc8-9b8d-3034e31e2fa8.png)

## Documentation

  Components used:
  - NodeMCU
  - HC-SR04
  - Relay
  - LED Bulbs
  - Nema 42
  - DM2282T
  - Logic converter

### Management system

The system consists of a NodeMCU ESP-12E development board and 8 LEDs to inform the user how many stations are connected. The role of the system is to manage the information received by the plates on the parking spaces and to send them to the IoT platform.
The NodeMCU development board supports a number of eight stations that can be connected. When a station transmits data to the management system, the station-specific LED flashes for three seconds.

![Management system representation](https://user-images.githubusercontent.com/23508982/127331276-263be392-733d-4591-ad71-87b0df09a625.png)

### Parking place system

Each parking space has two ultrasonic sensors, two bulbs, two relays and a Wi-Fi module.
The NodeMCU ESP8266 ESP-12E Wi-Fi module will be located in each parking space and will manage the data transmitted by the sensors.
Ultrasonic sensors have the role of detecting whether or not there is a vehicle on the parking lot and will be placed as follows: a sensor will be placed in front of the car occupying the parking space, and another will be under the car in the center of the parking lot. parking. Two sensors are used to reduce the risk of human interference. The parking space is considered occupied when both sensors detect an object. If this condition is met, then the microcontroller sends a high signal to the relay that activates the red light and will turn it on, indicating the occupancy of the parking space. If the condition cannot be met, then the microcontroller sends a high signal to the green light relay and will illuminate, indicating that the parking space is vacant. The two ultrasonic sensors will be connected to the microcontroller with the Wi-Fi mode that will transmit the data to the platform.

![Parking place system representation](https://user-images.githubusercontent.com/23508982/127331889-0f078e9d-c373-4646-bd2b-76cda7b80051.png)

### Barrier system

The car park has two barriers that include: a light bulb, a motor, a unit, two ultrasound sensors, a relay and a microcontroller with Wi-Fi mode.
The NodeMCU ESP8266 ESP-12E microcontroller will be located at both barriers and will handle the data transmitted by the sensors.
The bulb will be connected to the NodeMCU and will have the role of signaling the raising or lowering of the barrier. It is powered by an AC power source and operated by NodeMCU via a relay. Powered by an alternating current source is also the unit that controls the motor.
Ultrasonic sensors have the role of detecting if a car is waiting in front of the barrier and will be placed as follows: one sensor will be placed in front of the waiting place, on a dedicated side panel, and the other sensor will be in the center waiting and will be embedded in the asphalt, in a housing resistant to weathering and overtaking vehicles. Two sensors are used to reduce the risk of human interference. In the side panel, in addition to the ultrasonic sensor, there is also the NodeMCU development board, but also the actuator that operates the barrier. On its surface will be found the yellow light bulb that will signal the operation of the barrier.

![Barrier system representation](https://user-images.githubusercontent.com/23508982/127332214-2f393a6b-610c-482f-872d-c871323de722.png)

#### Motor connections

![Motor connections](https://user-images.githubusercontent.com/23508982/127332329-85de7540-bae2-4ead-941e-d8d72e1cfc09.png)


## Schematics

### Management system Schematics
![Management system Schematics](https://user-images.githubusercontent.com/23508982/127332767-bb9f3d47-32e8-4785-ba91-7ecb1006edf1.png)

#### 3D
![3D](https://user-images.githubusercontent.com/23508982/127332863-2a61b37e-ac58-4961-a680-bcf87864274e.png)

### Parking place system Schematics
![Parking space system Schematics](https://user-images.githubusercontent.com/23508982/127332930-aea085bd-e7a6-4667-b2ad-bf6f307bc45d.png)

#### 3D
![3D](https://user-images.githubusercontent.com/23508982/127332974-7293fbfb-de2f-44db-bbfd-91ef97211c5d.png)

### Barrier system Schematics
![Barrier system Schematics](https://user-images.githubusercontent.com/23508982/127333083-8fe94b8c-4298-4711-ab2c-cca25129c253.png)

#### 3D
![Picture11](https://user-images.githubusercontent.com/23508982/127333128-459d7d98-91e6-4a22-911d-9ac163ad66e9.png)


## Arduino Cloud Platform
![Picture12](https://user-images.githubusercontent.com/23508982/127333155-fa1068a5-9551-4e06-ade2-2d516f3b83fe.png)
