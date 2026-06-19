#include <stdint.h>

#include "RGFW.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int32_t main(void) {
    RGFW_window *win = RGFW_createWindow("Eh(ditor)", 0, 0, 1920/2, 1080/2, RGFW_windowCenter);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_pollEvents();
    }

    RGFW_window_close(win);
    return 0;
}
