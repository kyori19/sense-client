#include "Screen.h"

namespace Screen {
    Adafruit_SSD1306 display(128, 64, &Wire, 2); // NOLINT(cppcoreguidelines-interfaces-global-init)

    void setup() {
        display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);

        display.print("test");
        display.display();
    }

    void loop() {

    }
}
