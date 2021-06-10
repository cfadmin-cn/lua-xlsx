#define LUA_LIB

#include <core.h>
#include <xlsxio_version.h>
#include <xlsxio_read.h>
#include <xlsxio_write.h>

typedef struct xlsx_ctx {
  xlsxiowriter writer;
  xlsxioreader reader;
}xlsx_ctx;

int lropen(lua_State *L);
// 获取工作簿所有数据
int lget_all_rows(lua_State *L);
// 获取所有工作簿名称
int lget_sheets_name(lua_State *L);

int lwopen(lua_State *L);
// 添加工作簿字段名
int ladd_title(lua_State *L);
// 添加工作簿的字符串列字段
int ladd_column(lua_State *L);
// 添加工作簿的日期时间列字段
int ladd_column_datetime(lua_State *L);
// 换行
int lnext_line(lua_State *L);
// 指定行高
int lset_column_height(lua_State *L);
// 指定间距
int lset_column_detection(lua_State *L);