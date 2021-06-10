#include "lxlsx.h"

// 释放XLSX SHEET对象
static int lxlsx_sheet_gc(lua_State *L) {
  struct xlsx_sheet_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx)
    return 0;

  if (ctx->sheet) {
    xlsxioread_sheet_close(ctx->sheet);
    ctx->sheet = NULL;
  }
 
  return 0;
}

// 释放XLSX对象内存
static int lxlsx_gc(lua_State *L) {
  struct xlsx_ctx* ctx = luaL_checkudata(L, 1, "__XLSX__");
  if (!ctx)
    return 0;

  if (ctx->reader){
    xlsxioread_close(ctx->reader);
    ctx->reader = NULL;
  }

  if (ctx->writer){
    xlsxiowrite_close(ctx->writer);
    ctx->writer = NULL;
  }

  return 0;
}

// 创建XLSX对象
static int lxlsx_new(lua_State *L) {
  struct xlsx_ctx* ctx = lua_newuserdata(L, sizeof(struct xlsx_ctx));
  ctx->reader = NULL; ctx->writer = NULL;
  luaL_setmetatable(L, "__XLSX__");
  return 1;
}

// 获取XLSXIO的版本
static int lversion(lua_State *L) {
  lua_pushliteral(L, XLSXIOREAD_FULLNAME);
  lua_pushliteral(L, XLSXIOWRITE_FULLNAME);
  return 2;
}

static inline void lua_init_xlsx_sheet(lua_State *L) {
  luaL_newmetatable(L, "__XLSX_SHEET__");
  lua_pushstring (L, "__index");
  lua_pushvalue(L, -2);
  lua_rawset(L, -3);
  lua_pushliteral(L, "__mode");
  lua_pushliteral(L, "kv");
  lua_rawset(L, -3);
  lua_pushliteral(L, "__gc");
  lua_pushcfunction(L, lxlsx_sheet_gc);
  lua_rawset(L, -3);

  lua_pop(L, 1);
  return ;
}

static inline void lua_init_xlsx(lua_State *L) {
  lua_init_xlsx_sheet(L);
  luaL_newmetatable(L, "__XLSX__");
  lua_pushstring (L, "__index");
  lua_pushvalue(L, -2);
  lua_rawset(L, -3);
  lua_pushliteral(L, "__mode");
  lua_pushliteral(L, "kv");
  lua_rawset(L, -3);
  lua_pushliteral(L, "__gc");
  lua_pushcfunction(L, lxlsx_gc);
  lua_rawset(L, -3);
  luaL_Reg lxlsx_lib[] = {
    {"read_open", lropen},
    {"write_open", lwopen},
    {"open_sheet", lopen_sheet},
    {"get_sheets_name", lget_sheets_name},
    {"version", lversion},
    {NULL, NULL},
  };
  luaL_setfuncs(L, lxlsx_lib, 0);
  lua_pop(L, 1);

  return;
}

LUAMOD_API int luaopen_lxlsx(lua_State *L) {
  luaL_checkversion(L);
  lua_init_xlsx(L);
  luaL_Reg lxlsx_lib2[] = {
    {"new", lxlsx_new},
    {"version", lversion},
    {NULL, NULL},
  };
  luaL_newlib(L, lxlsx_lib2);
  return 1;
}