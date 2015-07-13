#!/usr/bin/env lua

file = io.open(arg[1])
io.write("<html>\n")
io.write("<head>\n")
io.write("<title>Soundpipe</title>\n")
io.write("<link rel=\"stylesheet\" href=\"css/skeleton.css\">\n")
io.write("<link rel=\"stylesheet\" href=\"css/normalize.css\">\n")
io.write("</head>\n")
io.write("<h1>Soundpipe Modules</h1>\n")
for line in file:lines() do
	io.write("<div class=\"row\">\n")
	io.write(string.format("<a href=\"%s.html\">%s</a>\n", line, line))
	io.write("</div>\n")
end 

io.write("</html>\n")
