local lxlsx = require "lxlsx"


local class = require "class"

local XLSX = class("xlsx")

function XLSX:ctor()
  self.xlsx = lxlsx:new()
end

function XLSX:read_open(filename)
  return assert(assert(self.xlsx, "[XLSX ERROR]: Invalid xlsx object."):ropen(filename))
end

function XLSX:write_open(filename)
  return assert(assert(self.xlsx, "[XLSX ERROR]: Invalid xlsx object."):wopen(filename))
end

function XLSX:version()
  return lxlsx.version()
end

return XLSX
