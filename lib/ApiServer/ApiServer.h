#ifndef SENSE_CLIENT_APISERVER_H
#define SENSE_CLIENT_APISERVER_H

#ifndef SERVER_HOST
#define SERVER_HOST ""
#endif

#ifndef SERVER_PORT
#define SERVER_PORT 0
#endif

namespace ApiServer {
    enum Status {
        NOT_CONNECTED,
        CONNECTED,
        FAILED,
        WAITING,
        ERROR,
    };

    Status status();
    void loop();
}

#endif //SENSE_CLIENT_APISERVER_H
