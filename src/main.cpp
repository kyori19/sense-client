#include <Arduino.h>
#include <Screen.h>
#include <Net.h>
#include <TimeSync.h>

void setup() {
    Screen::setup();
    Net::setup();
}

void loop() {
    Screen::loop();
    TimeSync::loop();
}
