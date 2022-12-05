#include <Arduino.h>
#include <Screen.h>
#include <Net.h>

void setup() {
    Screen::setup();
    Net::setup();
}

void loop() {
    Screen::loop();
}
