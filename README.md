# lua-xlsx

  基于[xlsxio](https://github.com/brechtsanders/xlsxio)实现的`Lua`版`xlsx`读写库.

## 安装方法

  请参考[这里](https://github.com/brechtsanders/xlsxio#building-from-source)

## API 介绍

  ```lua
  local lxlsx = require "lxlsx"
  ```

### 0. 创建对象

```lua
function lxlsx:new() return xlsx end
```

  创建一个用于读/写`xlsx`的`C`对象.

### 1. 读模式

```lua
-- 以读模式打开文件
function xlsx:ropen() return boolean, string end
```

```lua
-- 获取所有工作簿名称
function xlsx:get_sheets_name() return { sheet1, sheet1, sheet1} end
```

  以数组形式返回所有工作簿名称.

```lua
-- 获取指定`sheet_name`下所有内容
function xlsx:lget_sheet_all(sheet_name) return table end
```

  以数组形式返回指定工作簿名的所有内容.

### 2. 写模式
```lua
-- 以写模式打开文件
function xlsx:wopen() return boolean, string end
```

  成功返回`true`, 失败返回`false`与出错原因.

  这两个方法没成功, 不可调用之后的方法。

```lua
-- 写入内容
function xlsx:add_column(text) return true end
```

  将字符串类型的`text`写入到当前游标的指向的单元格.

```lua
-- 设置换行
function xlsx:next_line() return true end
```

  从当前行尾换到下一行首.


### 3. 关闭

```lua
-- 关闭
function xlsx:close() end
```

  关闭调用`ropen`与`wopen`打开的文件, 如果没有打开则不做任何操作.

## Examples

  以下示例可以在`test.lua`文件中找到.

```lua
require "utils"

local lxlsx = require "lxlsx"

local xls = lxlsx:new()

assert(xls:wopen("test.xlsx", "sheet1"))
xls:add_column("名称"); xls:add_column("公司"); xls:add_column("年龄")
xls:next_line()
xls:add_column("水果糖"); xls:add_column("Netease"); xls:add_column("30")
xls:next_line()
xls:add_column("中二丸"); xls:add_column("未知"); xls:add_column("26")
xls:close()

assert(xls:ropen("test.xlsx"))
var_dump(xls:get_sheets_name())
var_dump(xls:get_sheet_all("sheet1"))
```

## 注意

  * `wopen`会立刻创建文件, 但是必须调用`close`才会将数据写入到文件.

  * `ropen`/`wopen`可以分别打开`2`个同一文件或不同文件, 但是`close`会同时关闭他们.

## 协议

  [MIT License](https://github.com/CandyMi/lua-xlsx/blob/master/LICENSE)