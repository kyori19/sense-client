#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include "TimeSync.h"

namespace TimeSync {
    Status status_v = NOT_SYNCED;
    time_t last_synced_at = 0;
    unsigned long last_tried_at;
    int retry_count = 0;
    byte packet[48];
    WiFiUDP udp;

    Status status() {
        return status_v;
    }

    boolean shouldSync() {
        return last_synced_at == 0 || now() - last_synced_at > 60 * 2;
    }

    void createPacket() {
        memset(packet, 0, 48);
        packet[0] = 0b11100011;
        packet[1] = 0;
        packet[2] = 6;
        packet[3] = 0xec;
        packet[12] = 49;
        packet[13] = 0x4e;
        packet[14] = 49;
        packet[15] = 52;
    }

    void startSync() {
        createPacket();
        udp.begin(8888);
        udp.beginPacket(NTP_HOST, 123);
        udp.write(packet, 48);
        udp.endPacket();
    }

    boolean shouldTry() {
        return last_tried_at - millis() > 500;
    }

    void trySync() {
        if (!udp.parsePacket()) {
            return;
        }

        udp.read(packet, 48);
        const unsigned long higher = word(packet[40], packet[41]);
        const unsigned long lower = word(packet[42], packet[43]);
        const unsigned long secs = higher << 16 | lower;
        const unsigned long years = 2208988800UL;
        const unsigned long time = secs - years;

        if (time <= 0) {
            status_v = FAILED;
            return;
        }

        status_v = SYNCED;
        setTime(time);

        udp.stop();
    }

    void loop() {
        switch (status_v) {
            case SYNCING: {
                if (retry_count == 0) {
                    status_v = FAILED;
                    break;
                }

                if (!shouldTry()) {
                    break;
                }

                last_tried_at = millis();
                retry_count--;

                trySync();
            }
            default: {
                if (!shouldSync()) {
                    break;
                }

                if (last_synced_at != 0) {
                    last_synced_at = now();
                }

                if (!WiFi.isConnected()) {
                    status_v = NOT_SYNCED;
                    break;
                }

                if (last_synced_at == 0) {
                    last_synced_at = now();
                }

                status_v = SYNCING;
                startSync();
                retry_count = 10;
            }
        }
    }
}
