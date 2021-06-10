#include "lxlsx.h"

int lwopen(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx || ctx->reader)
    return luaL_error(L, "[LUA_XLSX ERROR]: The file is open for the current object.");

  const char* filename = luaL_checkstring(L, 2);
  if (!filename)
    return luaL_error(L, "[LUA_XLSX ERROR]: Invalid filename.");

  ctx->writer = xlsxiowrite_open(filename, lua_tostring(L, 3));
  if (ctx->writer) {
    lua_pushboolean(L, 0);
    lua_pushstring(L, "[LUA_XLSX ERROR]: Open failed.");
    return 2;
  }

  return 1;
}