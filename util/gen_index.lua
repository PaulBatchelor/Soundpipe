#!/usr/bin/env lua


file = io.open(arg[1])
io.write("<html>\n")
io.write("<head>\n")
io.write("<title>Soundpipe</title>\n")
io.write("<link rel=\"stylesheet\" href=\"css/skeleton.css\">\n")
io.write("<link rel=\"stylesheet\" href=\"css/normalize.css\">\n")
io.write("</head>\n")
io.write("<body>\n<div class=\"container\">\n")
io.write("<h1>Soundpipe Modules</h1>\n")
for line in file:lines() do
    sptbl = {}
    dofile(string.format("modules/data/%s.lua", line))
	io.write("<div class=\"row\"><nobr>\n")
	io.write(string.format("<a href=\"%s.html\">%s</a>\n", line, line))
  firstline = string.gsub(sptbl[line].description, "\n+", "")
  -- newstring = string.gsub(string,"Tutorial","Language")
	io.write(string.format("%s\n", string.sub(firstline, 0, 40)))
  if string.len(firstline) > 40 then
    io.write("...")
  end
	io.write("</nobr></div>\n")
end

io.write("</div></body></html>\n")
