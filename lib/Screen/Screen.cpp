#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include "ApiServer.h"
#include "MotionDetect.h"
#include "Screen.h"
#include "TimeSync.h"

namespace Screen {
    Adafruit_SSD1306 display(128, 64, &Wire, 2); // NOLINT(cppcoreguidelines-interfaces-global-init)

    String lines[8];

    void setup() {
        display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
        display.fillScreen(WHITE);
        display.setTextSize(1);
        display.setTextColor(WHITE);

        for (auto & line : lines) {
            line = "                     ";
        }
    }

    void update_text(int x, int y, const char c) {
        lines[y][x] = c;
    }

    void update_text(int x, int y, const String& text) {
        for (auto & c : text) {
            lines[y][x++] = c;
        }
    }

    char time_status_indicator() {
        switch (TimeSync::status()) {
            case TimeSync::NOT_SYNCED:
                return 'X';
            case TimeSync::SYNCING:
                return '?';
            case TimeSync::SYNCED:
                return 'O';
            default:
                return '!';
        }
    }

    void set_clock() {
        char result[14];
        sprintf(result, "%02d/%02d %02d:%02d %c", month(), day(), hour(), minute(), time_status_indicator());
        update_text(POS_CLOCK, result);
    }

    void set_md() {
        char result[10];
        sprintf(result, "MD: %-5s", MotionDetect::current() ? "true" : "false");
        update_text(POS_MD, result);
    }

    char server_status_indicator() {
        switch (ApiServer::status()) {
            case ApiServer::NOT_CONNECTED:
                return 'X';
            case ApiServer::CONNECTED:
                return 'O';
            default:
                return '!';
        }
    }

    void set_server() {
        update_text(POS_SERVER, server_status_indicator());
    }

    char wifi_status_indicator() {
        switch (WiFi.status()) {
            case WL_CONNECTED: {
                return 'O';
            }
            case WL_IDLE_STATUS: {
                return '_';
            }
            case WL_DISCONNECTED: {
                return 'X';
            }
            case WL_NO_SSID_AVAIL: {
                return '?';
            }
            default: {
                return '!';
            }
        }
    }

    void set_wifi() {
        char result[19];
        sprintf(result, "%c %-16s", wifi_status_indicator(), WiFi.SSID().c_str());
        update_text(POS_WIFI, result);
    }

    void set_dot() {
        update_text(POS_DOT, millis() % 1000 < 500 ? '.' : ' ');
    }

    void render_lines() {
        display.setCursor(0, 0);
        for (auto & line : lines) {
            display.println(line);
        }
    }

    void loop() {
        set_clock();
        set_md();
        set_server();
        set_wifi();
        set_dot();

        display.clearDisplay();
        render_lines();
        display.display();
    }
}
