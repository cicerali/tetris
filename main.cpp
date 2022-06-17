#include "window.h"
#include "media_sdl2_release.h"

int main(int argc, char *argv[]) {

    window &wnd = window::getInstance(new media_sdl2_release);
    wnd.start();
    return 0;
}