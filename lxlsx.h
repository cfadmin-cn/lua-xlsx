#define LUA_LIB

#include <core.h>
#include <xlsxio_version.h>
#include <xlsxio_read.h>
#include <xlsxio_write.h>

typedef struct xlsx_ctx {
  xlsxiowriter writer;
  xlsxioreader reader;
}xlsx_ctx;

// 以只读方式打开文件
int lropen(lua_State *L);
// 获取所有工作簿名称
int lget_sheets_name(lua_State *L);
// 获取指定工作簿所有数据
int lget_sheet_all(lua_State *L);

// 以只写的方式打开文件
int lwopen(lua_State *L);
// 当前游标写入一个单元格数据
int ladd_column(lua_State *L);
// 设置行尾然后将游标换行
int lnext_line(lua_State *L);