#include "lxlsx.h"

int lwopen(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx || ctx->writer)
    return luaL_error(L, "[LUA_XLSX ERROR]: The file is open for the current object.");

  const char* filename = luaL_checkstring(L, 2);
  if (!filename)
    return luaL_error(L, "[LUA_XLSX ERROR]: Invalid filename.");

  ctx->writer = xlsxiowrite_open(filename, lua_tostring(L, 3));
  if (!ctx->writer) {
    lua_pushboolean(L, 0);
    lua_pushstring(L, "[LUA_XLSX ERROR]: Open failed.");
    return 2;
  }
  lua_pushboolean(L, 1);
  return 1;
}

int ladd_column(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx || !ctx->writer)
    return luaL_error(L, "[LUA_XLSX ERROR]: `xlswriter` has not been initialized.");

  xlsxiowrite_add_column(ctx->writer, luaL_checkstring(L, 2), lua_tointeger(L, 3));
  lua_pushboolean(L, 1);  
  return 1;
}

int lnext_line(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx || !ctx->writer)
    return luaL_error(L, "[LUA_XLSX ERROR]: `xlswriter` has not been initialized.");

  xlsxiowrite_next_row(ctx->writer);
  lua_pushboolean(L, 1);
  return 1;
}