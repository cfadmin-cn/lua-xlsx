#include "lxlsx.h"

int lropen(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx || ctx->reader)
    return luaL_error(L, "[LUA_XLSX ERROR]: The file is open for the current object.");

  size_t fsize;
  const char *filedata = luaL_checklstring(L, 2, &fsize);

  ctx->reader = xlsxioread_open_memory ((void *)filedata, fsize, 0);
  if (!ctx->reader)
    ctx->reader = xlsxioread_open(filedata);

  if (!ctx->reader) {
    lua_pushboolean(L, 0);
    lua_pushstring(L, "[LUA_XLSX ERROR]: Open failed or the file does not exist.");
    return 2;
  }

  lua_pushboolean(L, 1);
  return 1;
}

// 获取所有工作簿名称
int lget_sheets_name(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx)
    return luaL_error(L, "[LUA_XLSX ERROR]: Invalid parameter.");

  if (!ctx->reader)
    return luaL_error(L, "[LUA_XLSX ERROR]: Objects that have not been initialized.");

  xlsxioreadersheetlist sheetlist = xlsxioread_sheetlist_open(ctx->reader);
  if (!sheetlist)
    return 0;

  int index = 1;
  lua_createtable(L, 16, 0);
  const char* sheetname;
  while ((sheetname = xlsxioread_sheetlist_next(sheetlist)) != NULL) {
    lua_pushstring(L, sheetname);
    lua_rawseti(L, -2, index++);
  }

  xlsxioread_sheetlist_close(sheetlist);
  return 1;
}

// 获取当前工作簿所有数据
int lget_sheet_all(lua_State *L) {
  xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx)
    return luaL_error(L, "[LUA_XLSX ERROR]: Invalid parameter.");

  xlsxioreadersheet sheet = xlsxioread_sheet_open(ctx->reader, luaL_checkstring(L, 2), XLSXIOREAD_SKIP_EMPTY_ROWS);
  if (!sheet) {
    lua_pushboolean(L, 0);
    lua_pushstring(L, "[LUA_XLSX ERROR]: this worksheet does not exist.");
    return 2;
  }

  int index = 1;
  char *value = NULL;
  lua_createtable(L, 128, 0);
  while (xlsxioread_sheet_next_row(sheet)) {
    int rows = 0;
    while (xlsxioread_sheet_next_cell_string(sheet, &value)) {
      if (rows == 0) {
        rows++;
        lua_createtable(L, 16, 0);
      }
      lua_pushstring(L, value);
      lua_rawseti(L, -2, rows++);
      xlsxioread_free(value);
    }
    lua_rawseti(L, -2, index++);
  }
  xlsxioread_sheet_close(sheet);
  return 1;
}