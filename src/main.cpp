#include <Arduino.h>
#include <ApiServer.h>
#include <Beep.h>
#include <BrightSense.h>
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
    Beep::setup();
    BrightSense::setup();
}

void loop() {
    Screen::loop();
    TimeSync::loop();
    ApiServer::loop();
    Beep::loop();
}
