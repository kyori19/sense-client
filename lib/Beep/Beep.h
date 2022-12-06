#ifndef SENSE_CLIENT_BEEP_H
#define SENSE_CLIENT_BEEP_H

#define BEEP_PIN 14

namespace Beep {
    void offer(unsigned long length);
    void setup();
    void loop();
}

#endif //SENSE_CLIENT_BEEP_H
