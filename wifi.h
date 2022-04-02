#ifndef _WIFI_H_
#define _WIFI_H_

#define ARRAY_SIZE 4

bool connectToWiFi(String ssid, String password);
bool connectToMultiWiFi(const String ssids[ARRAY_SIZE], const String passwords[ARRAY_SIZE]);

#endif
