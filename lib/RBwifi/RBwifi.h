#ifndef rbwifi_h
#define rbwifi_h

#include "Arduino.h"
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


extern WiFiClient wifiClient;


void printMacAddress(byte mac[]);
void printCurrentNet();
void printWifiData();

void connectToWifi(char ssid[], char pass[]);
void reconnectToWifi(char ssid[], char pass[]);

extern WiFiUDP  ntpUDP;
extern NTPClient timeClient;
unsigned long get_internet_epochTime();
#endif