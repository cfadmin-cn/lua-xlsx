local lxlsx = require "lxlsx"

local type = type
local assert = assert

local class = require "class"

local sheet_reader = class("sheet_reader")

function sheet_reader:ctor(opt)
  self.xlsx = opt.xlsx
end

function sheet_reader:get_all_rows(sheetname)
  return self.xlsx:get_all_rows(sheetname)
end

local sheet_writer = class("sheet_writer")

function sheet_writer:ctor(opt)
  self.xlsx = opt.xlsx
end

---comment 添加字段
---@param column string @字符串字段内容
---@return boolean
function sheet_writer:add_column(column)
  return self.xlsx:add_column(column)
end

---comment 添加字段
---@param timestamp integer @32位时间戳
---@return boolean
function sheet_writer:add_column_datetime(timestamp)
  return self.xlsx:add_column_datetime(timestamp)
end

---comment 设置行高
---@param height integer @行高
---@return boolean
function sheet_writer:set_column_height(height)
  return self.xlsx:set_column_height(height)
end

---comment 添加首行字段名
---@param name string @字段
---@param width integer @间距
---@return boolean
function sheet_writer:add_title(name, width)
  return self.xlsx:add_title(name, width or 30)
end

---comment 换行
---@return boolean
function sheet_writer:next_line()
  return self.xlsx:next_line()
end

function sheet_writer:close()
  if self.xlsx then
    self.xlsx:close()
    self.xlsx = nil
  end
end

return {
  version = function ()
    return lxlsx.version()
  end,
  get_sheets_name = function (filename)
    filename = assert(type(filename) == 'string' and filename, "Invalid filename.")
    local xlsx = lxlsx:new()
    local ok, errinfo = xlsx:read_open(filename)
    if not ok then
      xlsx = nil
      return false, errinfo
    end
    local tab = xlsx:get_sheets_name()
    xlsx = nil
    return tab
  end,
  -- reader对象
  read_open = function (filename)
    filename = assert(type(filename) == 'string' and filename, "Invalid filename.")
    local xlsx = lxlsx:new()
    local ok, errinfo = xlsx:read_open(filename)
    if not ok then
      xlsx = nil
      return false, errinfo
    end
    return sheet_reader:new { xlsx = xlsx}
  end,
  -- writer对象
  write_open = function (filename, sheetname)
    filename = assert(type(filename) == 'string' and filename, "Invalid filename.")
    local xlsx = lxlsx:new()
    local ok, errinfo = xlsx:write_open(filename, sheetname)
    if not ok then
      xlsx = nil
      return false, errinfo
    end
    return sheet_writer:new { xlsx = xlsx }
  end
}