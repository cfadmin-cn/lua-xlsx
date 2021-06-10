#define LUA_LIB

#include <core.h>
#include <xlsxio_version.h>
#include <xlsxio_read.h>
#include <xlsxio_write.h>

typedef struct xlsx_ctx {
  xlsxiowriter writer;
  xlsxioreader reader;
}xlsx_ctx;

typedef struct xlsx_sheet_ctx {
  xlsxioreadersheet sheet;
}xlsx_sheet_ctx;

int lropen(lua_State *L);
int lwopen(lua_State *L);

// 获取工作簿对象
int lopen_sheet(lua_State *L);

// 获取所有工作簿名称
int lget_sheets_name(lua_State *L);