#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include "ApiServer.h"
#include "MotionDetect.h"
#include "IDSwitch.h"

namespace ApiServer {
    Status status_v = NOT_CONNECTED;
    WiFiClient client;
    unsigned long last_tried_at = 0;
    time_t last_sent_at = 0;
    char data[1024];
    char message_v[20];

    Status status() {
        return status_v;
    }

    const char *message() {
        return message_v;
    }

    void createData() {
        StaticJsonDocument<48> json;
        json["id"] = IDSwitch::current();
        json["ts"] = now();
        json["md"] = MotionDetect::current();
        serializeJson(json, data);
    }

    void loop() {
        switch (status_v) {
            case NOT_CONNECTED:
            case FAILED: {
                if (!WiFi.isConnected()) {
                    status_v = NOT_CONNECTED;
                    break;
                }

                if (millis() - last_tried_at < 500) {
                    break;
                }

                last_tried_at = millis();

                if (!client.connect(SERVER_HOST, SERVER_PORT)) {
                    status_v = FAILED;
                    break;
                }

                status_v = CONNECTED;
                break;
            }
            case CONNECTED:
            case ERROR: {
                if (!client.connected()) {
                    status_v = NOT_CONNECTED;
                    client.stop();
                    break;
                }

                if (now() - last_sent_at < 1) {
                    break;
                }

                last_sent_at = now();

                createData();
                client.print(data);
                status_v = WAITING;
            }
            case WAITING: {
                if (now() - last_sent_at > 0) {
                    status_v = ERROR;
                    break;
                }

                memset(data, 0, 1024);
                if (!client.read(data, 1024)) {
                    break;
                }

                StaticJsonDocument<32> json;
                DeserializationError err = deserializeJson(json, data, 1024);
                if (err) {
                    status_v = ERROR;
                    sprintf(message_v, "%-19s", err.c_str());
                    break;
                }

                if (json.containsKey("message")) {
                    sprintf(message_v, "%-19s", json["message"].as<const char *>());
                } else {
                    message_v[0] = '\0';
                }

                if (!json["ok"].as<bool>()) {
                    status_v = ERROR;
                    break;
                }

                status_v = CONNECTED;
            }
        }
    }
}
