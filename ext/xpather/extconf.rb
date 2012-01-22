require 'mkmf'
have_library("xml2")
find_header("libxml/tree.h", "/usr/include/libxml2")
find_header("libxml/parser.h", "/usr/include/libxml2")
find_header("libxml/xpath.h", "/usr/include/libxml2")
find_header("libxml/xpathInternals.h", "/usr/include/libxml2")
create_makefile('xpather/xpather')
