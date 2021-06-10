local lxlsx = require "lua-xlsx"
local LOG = require "logging"

-- 写入数据
local writer = lxlsx.write_open("my.xlsx", "sheet1")
writer:set_column_height(10)
writer:add_title("column-1", 5)
writer:add_title("column-2", 10)
writer:add_title("column-3", 15)
writer:next_line()
writer:add_column_datetime(os.time())
writer:add_column_datetime(os.time())
writer:add_column_datetime(os.time())
writer:next_line()
writer:close()

--读取数据
LOG:DEBUG(lxlsx.version())
LOG:DEBUG(lxlsx.get_sheets_name("my.xlsx"))

local reader = lxlsx.read_open("my.xlsx")
LOG:DEBUG(reader:get_all_rows("sheet1"))

LOG:INFO("over.")