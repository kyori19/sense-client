#include <ESP8266WiFi.h>
#include "Net.h"

namespace Net {
    void setup() {
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PASS);
    }
}
