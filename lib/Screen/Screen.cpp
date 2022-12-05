#include <TimeLib.h>
#include "Screen.h"

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

    void set_clock() {
        char result[12];
        sprintf(result, "%02d/%02d %02d:%02d", month(), day(), hour(), minute());
        update_text(POS_CLOCK, result);
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
        set_dot();

        display.clearDisplay();
        render_lines();
        display.display();
    }
}
