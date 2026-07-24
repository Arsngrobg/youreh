#include <stdint.h>
#include <stdio.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

// https://www.lua.org/manual/5.1/manual.html#3
// https://www.codingwiththomas.com/blog/a-lua-c-api-cheat-sheet
int32_t main(void) {
    printf("Yoreh-ditor!\n");
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "test/factorial.lua") == 0) {
        printf("[C] Executed factorial.lua\n");
    } else {
        printf("[C] Error reading script\n");
        luaL_error(L, "Error: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
    return 0;
}
