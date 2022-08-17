# Arduino Motion Sensing Doorbell
 
# Description
The system starts in an “idle” state, constantly checking from the ultrasonic sensor if there is someone approaching the doorbell. When someone approaches within 10 inches of the sensor (can be easily changed in code), the LCD will display a motion alert, along with the distance the object is with the sensor in inches. When the person is within 10 inches of the sensor, the doorbell can be pressed. If the motion sensor does not detect anyone and the button is pressed, the system will treat the button as a fall alarm and will not do anything, When a valid button press is detected, 2 LEDs will light up and the LCD will display an alert for the front door. The tune and alert will continue displaying and playing regardless of the motion sensor and button presses. Pressing the button multiple times in a row will be treated as one press until the tune is finished playing. The tunes are on a rotating basis, with 6 tunes currently programmed. They will play in order and then cycle back to the beginning when all the tunes have been played. 

# Components
- UNO R3 Controller Board 
- 830 Tie-Points Breadboard 
- Ultrasonic Sensor
- Button
- LCD1602 Module
- 10k Potentiometer 
- Breadboard Jumper Wire 
- Female to Male Dupont Wire 
- Passive Buzzer
- LEDs
- Resistors

# Schematics

## LCD1602 
<img src="https://user-images.githubusercontent.com/81611522/185217345-4fc0a30e-3dcc-4c50-82d8-f44660faa9fe.png" width="500">

## Passive Buzzer
<img src="https://user-images.githubusercontent.com/81611522/185217366-e3eef31d-e566-487a-adf4-034766b3fb34.png" width="500">

## General Overview
<img src="https://user-images.githubusercontent.com/81611522/185217351-de97702b-97e8-4d2e-aa9f-c58a8a421a22.png" width="500">

# Pins Info
- 2: Button
- 3 to 4: Ultrasonic Sensor 
- 5: Passive Buzzer
- 6 to 7: LEDs
- 8 to 13: LCD 1602
