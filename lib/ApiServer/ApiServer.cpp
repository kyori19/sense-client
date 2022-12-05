#include <ESP8266WiFi.h>
#include "ApiServer.h"

namespace ApiServer {
    Status status_v = NOT_CONNECTED;
    WiFiClient client;
    unsigned long last_tried_at = 0;

    Status status() {
        return status_v;
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
                client.print("hello from client");
                break;
            }
            case CONNECTED: {
                if (!client.connected()) {
                    status_v = NOT_CONNECTED;
                }
            }
        }
    }
}
