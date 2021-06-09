#define LUA_LIB

#include <core.h>


LUAMOD_API int luaopen_lkcp(lua_State *L) {
  luaL_checkversion(L);
  luaL_Reg lxlsx_libs[] = {
    {NULL, NULL},
  };
  luaL_newlib(L, lxlsx_libs);
  return 1;
}