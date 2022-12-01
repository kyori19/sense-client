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

    void set_dot() {
        lines[POS_DOT] = millis() % 1000 < 500 ? '.' : ' ';
    }

    void render_lines() {
        display.setCursor(0, 0);
        for (auto & line : lines) {
            display.println(line);
        }
    }

    void loop() {
        set_dot();

        display.clearDisplay();
        render_lines();
        display.display();
    }
}
