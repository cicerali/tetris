//
// Created by alcicer on 8/4/2022.
//

#include "rest_service.h"

void event_service::wait_event(httplib::DataSink *sink) {
    std::unique_lock<std::mutex> lk(m);
    using namespace std::chrono_literals;
    cv.wait_for(lk, 1000ms);
    if (sink->is_writable()) { sink->write(("data: " + message + "\n\n").data(), message.size() + 8); }
}

void event_service::send_event(const std::string &msg) {
    std::lock_guard<std::mutex> lk(m);
    message = msg;
    cv.notify_all();
}

void event_service::process_command(const char *key) const {

    SDL_Event event;
    SDL_zero(event);
    event.type = commandEvent;
    std::string data{key};
    std::transform(data.begin(), data.end(),
                   data.begin(), ::tolower);
    if ("a" == data) {
        event.key.keysym.scancode = SDL_SCANCODE_A;
    } else if ("s" == data) {
        event.key.keysym.scancode = SDL_SCANCODE_S;
    } else if ("n" == data) {
        event.key.keysym.scancode = SDL_SCANCODE_N;
    } else if ("esc" == data) {
        event.key.keysym.scancode = SDL_SCANCODE_ESCAPE;
    } else if ("space" == data) {
        event.key.keysym.scancode = SDL_SCANCODE_SPACE;
    } else if ("up" == data) {
        event.key.keysym.scancode = SDL_SCANCODE_UP;
    } else if ("down" == data) {
        event.key.keysym.scancode = SDL_SCANCODE_DOWN;
    } else if ("left" == data) {
        event.key.keysym.scancode = SDL_SCANCODE_LEFT;
    } else if ("right" == data) {
        event.key.keysym.scancode = SDL_SCANCODE_RIGHT;
    } else {
        return;
    }
    SDL_PushEvent(&event);
}

rest_service::rest_service(const char *host, int port) : host(host), port(port) {
    server.Get(status_endpoint, [this](const httplib::Request &req, httplib::Response &res) {
        res.set_chunked_content_provider("text/event-stream",
                                         [&](size_t /*offset*/, httplib::DataSink &sink) {
                                             ev.wait_event(&sink);
                                             return true;
                                         });
    });
    server.Post(command_endpoint, [this](const httplib::Request &req, httplib::Response &res) {
        nlohmann::json data = nlohmann::json::parse(req.body);
        input cm = data.get<input>();
        ev.process_command(cm.cmd.data());
    });
}

void rest_service::start() {
    listen_thread = std::thread([&]() {
        server.listen(host, port);
    });
}

rest_service::~rest_service() {
    server.stop();
    listen_thread.detach();
}