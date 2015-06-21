#!/usr/local/bin/lua

-- Parse a lua table in modules/data and write text
-- to run: lua sp.lua "foo"

sptbl = {}
module = arg[1]
dofile(string.format("modules/data/%s.lua", module))
PG = { name = module }

function PG.printheader(self, str)
    io.write("<b><u>" .. str .. "</u></b>")
    io.write("<br><br>")
end

function PG.printoption(self, str)
    io.write("<i>" .. str .. ":</i> ")
end

function PG.title(self, sp)
    io.write("<h1>" .. self.name .. "</h1>\n")
end

function PG.desc(self, sp)
    print(sp[self.name].description)
    io.write("\n<br><br>")
end

function PG.createf(self, sp)
    local tbl = sp[self.name]
    print(string.format("%s(sp_%s **%s)<br>", 
        tbl.func.create, self.name, self.name, tbl.func.init))
end

function PG.destroyf(self, sp)
    local tbl = sp[self.name]
    print(string.format("%s(sp_%s **%s)", 
        tbl.func.destroy, self.name, self.name, tbl.func.init))
end

function PG.initf(self, sp)
    local tbl = sp[self.name]
    
    io.write(string.format("%s(sp_data *sp, sp_%s *%s", 
        tbl.func.init, self.name, self.name))
    
    for _, v in pairs(tbl.params.mandatory) do
        if(string.byte(v.type, string.len(v.type)) == 42) then
        arg = string.format(", %s%s", v.type, v.name)
        else
        arg = string.format(", %s %s", v.type, v.name)
        end
        io.write(arg)
    end

    io.write(")\n<br>")
end

function PG.computef(self, sp)
    local tbl = sp[self.name]
    io.write(string.format("%s(sp_data *sp, sp_%s *%s", 
        tbl.func.compute, self.name, self.name, tbl.func.init))
        
    for _, input in pairs(tbl.inputs) do
        io.write(string.format(", SPFLOAT *%s", input.name))
    end

    io.write(")\n<br>")
end


function PG.funcs(self, sp)
    self:printheader("Functions")    
	self:createf(sp)   
	self:initf(sp)   
	self:computef(sp)
	self:destroyf(sp)   
	io.write("\n<br><br>")
end

function PG.man_params(self,sp)
    self:printheader("Mandatory Parameters")
    local tbl = sp[self.name].params.mandatory
    for _, v in pairs(tbl) do
        self:printoption(v.name)
        io.write(v.description)
        io.write(string.format("\n<br>(Recommended value: %s)\n<br>\n<br>", 
            v.default))
    end
 end

function PG.opt_params(self,sp)
    self:printheader("Optional Parameters:")
    local tbl = sp[self.name].params.optional
    for _, v in pairs(tbl) do
        self:printoption(v.name)
        io.write(v.description)
        io.write(string.format("\n<br>(Default value: %s)\n<br>\n<br>", 
            v.default))
    end
end

function PG.inputs(self, sp)
    self:printheader("Inputs:")
    local tbl = sp[self.name].inputs
    for _, v in pairs(tbl) do
        self:printoption(v.name)
        io.write(v.description .. "\n<br>\n<br>")
    end
	io.write("\n<br>")
end
	
function PG.outputs(self, sp)
    self:printheader("Outputs:")
    local tbl = sp[self.name].outputs
    for _, v in pairs(tbl) do
        self:printoption(v.name)
        io.write(v.description .. "\n<br>\n<br>")
    end
	io.write("\n<br>")
end

function PG.other(self, sp)
    self:printheader("Other Functions:")
    local tbl = sp[self.name].func.other
    
    for func,params in pairs(tbl) do
        io.write(string.format("%s(sp_%s %s", func, self.name, self.name))
        for _,p in pairs(params) do
            io.write(string.format(", %s %s", p.type, p.name))
        end
        io.write(")\n<br>\n<br>")
        for _,p in pairs(params) do
            self:printoption(p.name)
            io.write(p.description.. "\n<br>")
            io.write("(Suggested default: " .. p.default .. ")\n<br>\n<br>")
        end
    end
    io.write("\n<br>")
end
	
function PG.params(self, sp)
    PG:man_params(sp)
    PG:opt_params(sp)
    io.write("\n<br>")
end

function PG.files(self, sp)
	local tbl = sp[self.name].files
	io.write(string.format("Files: <i>%s, %s</i><br><br>", tbl.header, tbl.module))

end

function PG.example(self, sp)
	local example = sp[self.name].files.example
	if (example == nil) then return end
	self:printheader("Example")
	file = io.open("examples/" .. example)
	io.write("<pre>")
	for line in file:lines() do
		io.write(line .. "\n")
	end
	io.write("</pre>")
	file:close()
end

function PG.makepage(self, sp)
	PG:title(sptbl)
	PG:files(sptbl)
	PG:desc(sptbl)
	PG:funcs(sptbl)
	PG:params(sptbl)
	PG:inputs(sptbl)
	PG:outputs(sptbl)
	PG:other(sptbl)
	PG:example(sptbl)
end

PG:makepage(sptbl)
