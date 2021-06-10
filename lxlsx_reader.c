#include "lxlsx.h"

int lropen(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx || ctx->reader)
    return luaL_error(L, "[LUA_XLSX ERROR]: The file is open for the current object.");

  // 如果指定fd打开文件
  if (lua_type(L, 2) == LUA_TNUMBER) {
    ctx->reader = xlsxioread_open_filehandle(lua_tointeger(L, 2));
    if (!ctx->reader) {
      lua_pushboolean(L, 0);
      lua_pushstring(L, "[LUA_XLSX ERROR]: Open failed.");
      return 2;
    }
  }

  // 如果指定文件名或文件内容打开
  if (lua_type(L, 2) == LUA_TSTRING) {
    size_t fsize;
    const char *filedata = luaL_checklstring(L, 2, &fsize);
    // 先尝试当内存加载, 然后尝试当初文件名加载.
    ctx->reader = xlsxioread_open_memory ((void *)filedata, fsize, 0);
    if (!ctx->reader)
      ctx->reader = xlsxioread_open(filedata);

    if (!ctx->reader) {
      lua_pushboolean(L, 0);
      lua_pushstring(L, "[LUA_XLSX ERROR]: Open failed.");
      return 2;
    }
  }

  return luaL_error(L, "[LUA_XLSX ERROR]: Invalid parameter.");
}