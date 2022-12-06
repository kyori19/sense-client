#ifndef SENSE_CLIENT_IDSWITCH_H
#define SENSE_CLIENT_IDSWITCH_H

#define ID_SWITCH_HIGH_PIN 12
#define ID_SWITCH_LOW_PIN 13

namespace IDSwitch {
    void setup();
    int current();
}

#endif //SENSE_CLIENT_IDSWITCH_H
