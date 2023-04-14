#pragma once

#include "ArduinoJson.h"
#include "SPI.h"
#include "esphome.h"

// There's probably a better way around this, but this seems to work okay...
#undef yield
#undef delay
#undef delayMicroseconds
#undef micros
#undef millis
#include "rtl_433_ESP.h"

#define JSON_MSG_BUFFER 512

int _id;
const char *_data;
int _cmd;

class RTL433 : public Component {

public:
  void setup() override {
    rf.initReceiver(RF_MODULE_RECEIVER_GPIO, 433.92);
    rf.setCallback(rtl_433_Callback, messageBuffer, JSON_MSG_BUFFER);
    rf.enableReceiver();
    rf.getModuleStatus();
  }

  void loop() override { 
    rf.loop();
  }

  bool matches(int id, char *data) {
    return (id == _id && strcmp(data, _data) == 0);
  }

  bool matches(int id, int cmd) {
    return (id == _id && cmd == _cmd);
  }

private:
  rtl_433_ESP rf;
  char messageBuffer[JSON_MSG_BUFFER];

  static void rtl_433_Callback(char *message) {
    ESP_LOGI("rtl433", "%s", message);

    DynamicJsonDocument doc(JSON_MSG_BUFFER);
    deserializeJson(doc, message);

    _id = doc["id"];
    _data = doc["data"];
    _cmd = doc["cmd"];

    // I find that it's common to receive multiple signals from a device, with
    // the last one not always being correct. The delay helps mitigate this by
    // leaving enough time for each signals to be processed
    esphome::delay(50);
  }
};
