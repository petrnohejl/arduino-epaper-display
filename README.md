Arduino E-Paper Display
=======================

Smart display IoT device based on Arduino and E-Paper display.

The program connects to Wi-Fi, loads JSON data from Google Spreadsheets API, parses the JSON, and displays the data on the screen. The spreadsheet provides financial data about watched stocks and personal stocks portfolio. Arduino board periodically goes to deep sleep to save the battery.

This project is a fork of [arduino-eink-display-workshop](https://github.com/Tuxilero/arduino-eink-display-workshop).


Hardware Components
-------------------

- NodeMCU V3 CH340G board with ESP8266 Wi-Fi Microchip
- MH-ET LIVE 2.9' E-Paper Module
- TP4056 USB-C Lithium Battery Charger Module
- LiitoKala 18650 HG2 3000 mAh Li-Ion Battery
- Push Button Switch 10 x 15 mm
- Plastic box printed on Prusa 3D printer


Hardware Connections
--------------------

- Connection of TP4056 module, NodeMCU board, button switch, battery:
  - TP4056.OUT+ -> Button 0
  - TP4056.B+ -> Battery +
  - TP4056.B- -> Battery -
  - TP4056.OUT- -> NodeMCU.G
  - NodeMCU.VIN -> Button 1

- Connection of E-Paper module with NodeMCU board:
  - BUSY -> D2
  - RST -> D4
  - DC -> D3
  - CS -> D8
  - SCLK -> D5
  - SDI -> D7
  - GND -> GND
  - VCC -> 3V

- NodeMCU board connections:
  - D0 -> RST for the deep sleep (disconnect when programming)
  - 3K3 pull-down resistor between D8 and GND


IDE Setup
---------

- Install CH340 driver
- Install Arduino IDE
- Install ESP8266 add-on in Arduino IDE
  - File -> Preferences
  - Add additional boards manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Tools -> Board -> Boards Manager
  - Search and install ESP8266 package
  - Tools -> Board -> ESP8266 Boards -> NodeMCU 1.0 (ESP-12E Module)
- Install libraries in Arduino IDE
  - Tools -> Manage Libraries
  - Search and install GxEPD2 and ArduinoJson
- Tools -> Upload Speed -> 921600
- Tools -> Serial Monitor


Developed by
------------

[Petr Nohejl](https://petrnohejl.cz)  
[Lukas Hermann](https://helu.cz/)


License
-------

    Copyright 2022 Petr Nohejl

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
