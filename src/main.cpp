#include <Arduino.h>
#include <ApiServer.h>
#include <Screen.h>
#include <MotionDetect.h>
#include <Net.h>
#include <TimeSync.h>

void setup() {
    Screen::setup();
    Net::setup();
    MotionDetect::setup();
}

void loop() {
    Screen::loop();
    TimeSync::loop();
    ApiServer::loop();
}
