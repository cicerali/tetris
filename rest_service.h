//
// Created by alcicer on 8/4/2022.
//

#ifndef TETRIS_REST_SERVICE_H
#define TETRIS_REST_SERVICE_H

#include "httplib.h"
#include "SDL_events.h"
#include "nlohmann/json.hpp"
#include <cctype>

class event_service {
public:

    event_service() : commandEvent(SDL_RegisterEvents(1)) {
    }

    void wait_event(httplib::DataSink *sink);

    void send_event(const std::string &msg);

    void process_command(const char *key) const;

    const Uint32 commandEvent;
private:
    std::mutex m;
    std::condition_variable cv;
    std::string message;
};

struct input {
    std::string cmd;
};

inline void to_json(nlohmann::json &j, const input &c) {
    j = nlohmann::json{{"cmd", c.cmd}};
}

inline void from_json(const nlohmann::json &j, input &c) {
    j.at("cmd").get_to(c.cmd);
}

class rest_service {
public:
    rest_service() : rest_service("0.0.0.0", 8080) {};

    rest_service(const char *host, int port);

    void start();

    ~rest_service();

    event_service ev{};
private:
    const char *status_endpoint = "/tetris/status";
    const char *command_endpoint = "/tetris/command";
    httplib::Server server{};
    const char *host;
    int port;
    std::thread listen_thread;
};

#endif //TETRIS_REST_SERVICE_H
