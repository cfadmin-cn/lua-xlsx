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