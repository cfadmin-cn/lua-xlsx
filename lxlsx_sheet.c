#include "lxlsx.h"

int lopen_sheet(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx)
    return luaL_error(L, "[LUA_XLSX ERROR]: Invalid parameter.");

  xlsxioreadersheet sheet = xlsxioread_sheet_open(ctx->reader, luaL_checkstring(L, 2), XLSXIOREAD_SKIP_EMPTY_ROWS);
  if (!sheet)
    return luaL_error(L, "[LUA_XLSX ERROR]: this worksheet does not exist.");

  xlsx_sheet_ctx* sheet_ctx = lua_newuserdata(L, sizeof(struct xlsx_sheet_ctx));
  sheet_ctx->sheet = sheet;

  luaL_setmetatable(L, "__XLSX_SHEET__");
  return 1;
}

int lget_sheets_name(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx)
    return luaL_error(L, "[LUA_XLSX ERROR]: Invalid parameter.");

  if (!ctx->reader)
    return luaL_error(L, "[LUA_XLSX ERROR]: Objects that have not been initialized.");

  xlsxioreadersheetlist sheetlist = xlsxioread_sheetlist_open(ctx->reader);
  if (!sheetlist)
    return 0;

  lua_createtable(L, 32, 0);
  int index = 1;
  const char* sheetname;
  while ((sheetname = xlsxioread_sheetlist_next(sheetlist)) != NULL) {
    lua_pushinteger(L, index);
    lua_pushstring(L, sheetname);
    lua_rawseti(L, -3, index++);
  }
  xlsxioread_sheetlist_close(sheetlist);
  return 1;
}