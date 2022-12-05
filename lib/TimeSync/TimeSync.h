#ifndef SENSE_CLIENT_TIMESYNC_H
#define SENSE_CLIENT_TIMESYNC_H

#ifndef NTP_HOST
#define NTP_HOST "ntp.nict.jp"
#endif

namespace TimeSync {
    enum Status {
        NOT_SYNCED,
        SYNCING,
        SYNCED,
        FAILED,
    };

    Status status();
    void loop();
}

#endif //SENSE_CLIENT_TIMESYNC_H
