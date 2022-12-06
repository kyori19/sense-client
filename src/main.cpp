#include <Arduino.h>
#include <ApiServer.h>
#include <IDSwitch.h>
#include <Screen.h>
#include <MotionDetect.h>
#include <Net.h>
#include <TimeSync.h>

void setup() {
    Screen::setup();
    Net::setup();
    MotionDetect::setup();
    IDSwitch::setup();
}

void loop() {
    Screen::loop();
    TimeSync::loop();
    ApiServer::loop();
}
