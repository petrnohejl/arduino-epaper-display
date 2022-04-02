#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <EEPROM.h>
#include <Fonts/FreeMonoBold9pt7b.h> // fonts: https://github.com/adafruit/Adafruit-GFX-Library/tree/master/Fonts

#include "main.h"
#include "wifi.h"
#include "display.h"

const String SPREADSHEET_URL = "https://sheets.googleapis.com/v4/spreadsheets/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/values/Arduino?alt=json&valueRenderOption=FORMATTED_VALUE&key=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
const String WIFI_SSIDS[ARRAY_SIZE] = {"wifi1", "wifi2"};
const String WIFI_PASSWORDS[ARRAY_SIZE] = {"pass1", "pass2"};

void runProgram() {
  //connectToWiFi(WIFI_SSIDS[0], WIFI_PASSWORDS[0]);
  connectToMultiWiFi(WIFI_SSIDS, WIFI_PASSWORDS);
  loadData(SPREADSHEET_URL);
}

void loadData(String url) {
  Serial.println("Loading data from: " + url);
  
  WiFiClientSecure wifiClient;
  wifiClient.setInsecure();
  wifiClient.connect(url, 80);

  HTTPClient httpClient;
  httpClient.begin(wifiClient, url);

  int httpStatus = httpClient.GET();
  String payload = httpClient.getString();

  Serial.print("HTTP status code: ");
  Serial.println(httpStatus);
  Serial.print("Payload: ");
  Serial.println(payload);

  if (httpStatus == 200) {
    StaticJsonDocument<JSON_BUFFER_SIZE> jsonBuffer;
    DeserializationError parseError = deserializeJson(jsonBuffer, payload);
    
    if (parseError) {
      Serial.println("JSON parse error");
    } else {
      Serial.println("Parsing JSON data");
      parseData(jsonBuffer);
    }    
  } else {
    Serial.println("HTTP response error");
  }
  
  httpClient.end();
}

void parseData(StaticJsonDocument<JSON_BUFFER_SIZE>& jsonBuffer) {
  String header = jsonBuffer["values"][0][0].as<String>();

  String symbol1 = jsonBuffer["values"][1][0].as<String>();
  String value1 = jsonBuffer["values"][1][1].as<String>();
  String change1 = jsonBuffer["values"][1][2].as<String>();
  String item1 = alignText(symbol1, 7, true) + alignText(value1, 7, false) + alignText(change1, 9, false);

  String symbol2 = jsonBuffer["values"][2][0].as<String>();
  String value2 = jsonBuffer["values"][2][1].as<String>();
  String change2 = jsonBuffer["values"][2][2].as<String>();
  String item2 = alignText(symbol2, 7, true) + alignText(value2, 7, false) + alignText(change2, 9, false);

  String symbol3 = jsonBuffer["values"][3][0].as<String>();
  String value3 = jsonBuffer["values"][3][1].as<String>();
  String change3 = jsonBuffer["values"][3][2].as<String>();
  String item3 = alignText(symbol3, 7, true) + alignText(value3, 7, false) + alignText(change3, 9, false);

  String portfolioValue = jsonBuffer["values"][4][0].as<String>();
  String portfolioReturn = jsonBuffer["values"][4][1].as<String>();
  String portfolioGain = jsonBuffer["values"][4][2].as<String>();
  String footer = portfolioValue + "  " + portfolioReturn + "  " + portfolioGain;

  displayData(header, item1, item2, item3, footer);
}

void displayData(String header, String item1, String item2, String item3, String footer) {
  display.init(115200);
  display.setRotation(3); // landscape
  display.setFullWindow();
  display.firstPage();

  int16_t textBoundsX, textBoundsY;
  uint16_t textBoundsWidth, textBoundsHeight;

  uint16_t displayWidth = display.width() - 1;
  uint16_t displayHeight = display.height() - 1;
  uint16_t paddingHorizontal = 8;
  uint16_t paddingTop = 21;
  uint16_t lineHeight = 24;
  uint16_t linePadding = 4;

  do {
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMonoBold9pt7b);

    // header text
    display.setTextColor(GxEPD_RED);
    display.getTextBounds(header, 0, 0, &textBoundsX, &textBoundsY, &textBoundsWidth, &textBoundsHeight);
    uint16_t headerX = ((display.width() - textBoundsWidth) / 2) - textBoundsX;
    display.setCursor(headerX, paddingTop);
    display.print(header);

    // header line
    uint16_t headerLineY = lineHeight + linePadding;
    display.drawLine(paddingHorizontal, headerLineY, displayWidth - paddingHorizontal, headerLineY, GxEPD_RED);

    // text 1
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(paddingHorizontal, paddingTop + lineHeight);
    display.print(item1);

    // text 2
    display.setCursor(paddingHorizontal, paddingTop + lineHeight * 2);
    display.print(item2);

    // text 3
    display.setCursor(paddingHorizontal, paddingTop + lineHeight * 3);
    display.print(item3);

    // footer line
    uint16_t footerLineY = (lineHeight * 4) + linePadding;
    display.drawLine(paddingHorizontal, footerLineY, displayWidth - paddingHorizontal, footerLineY, GxEPD_RED);

    // footer text
    display.setTextColor(GxEPD_RED);
    display.getTextBounds(footer, 0, 0, &textBoundsX, &textBoundsY, &textBoundsWidth, &textBoundsHeight);
    uint16_t footerX = ((display.width() - textBoundsWidth) / 2) - textBoundsX;
    display.setCursor(footerX, paddingTop + lineHeight * 4);
    display.print(footer);

    // rectangle
    display.drawLine(0, 0, displayWidth, 0, GxEPD_BLACK);
    display.drawLine(0, 0, 0, displayHeight, GxEPD_BLACK);
    display.drawLine(displayWidth, 0, displayWidth, displayHeight, GxEPD_BLACK);
    display.drawLine(0, displayHeight, displayWidth, displayHeight, GxEPD_BLACK);

  } while (display.nextPage());
}

String alignText(String text, int length, bool toLeft) {
  while (text.length() < length) {
    if (toLeft) {
      text = text + " ";
    } else {
      text = " " + text;
    }
  }
  return text;
}

long eepromExample(long val1, long val2, long val3) {
  long previousVal1 = 0;
  long previousVal2 = 0;
  long previousVal3 = 0;

  EEPROM.begin(sizeof(long) * 10);

  EEPROM.get(0, previousVal1);
  EEPROM.get(sizeof(long), previousVal2);
  EEPROM.get(sizeof(long) * 2, previousVal3);

  EEPROM.put(0, val1);
  EEPROM.put(sizeof(long), val2);
  EEPROM.put(sizeof(long) * 2, val3);

  EEPROM.commit();

  return val1 + val2 + val3;
}
