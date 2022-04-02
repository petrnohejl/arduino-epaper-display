#ifndef _MAIN_H_
#define _MAIN_H_

#include <ArduinoJson.h>

#define JSON_BUFFER_SIZE 1024 // buffer size: https://arduinojson.org/assistant/

void runProgram();
void loadData(String url);
void parseData(StaticJsonDocument<JSON_BUFFER_SIZE>& jsonBuffer);
void displayData(String header, String item1, String item2, String item3, String footer);
String alignText(String text, int length, bool toLeft);
long eepromExample(long val1, long val2, long val3);

#endif
