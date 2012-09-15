# XPather

    $ gem install xpather    
    $ irb -rxpather
    >> XML = File.read("/test/books.xml")
    >> document = XPather.new(XML)
    => #<XPather:0x007f9bd2a32030>
    >>
    >> document.get("/bookstore/book[1]/author")
    => "Giada De Laurentiis"
    >>
    >> document.get("/bookstore/book/author")
	=> ["Giada De Laurentiis", "J K. Rowling", "James McGovern", "Per Bothner", "Kurt Cagle", "James Linn", "Vaidyanathan Nagarajan", "Erik T. Ray"]
	>>
	>> document.search("/bookstore/book[1]/author")
	=> ["<author>Giada De Laurentiis</author>"]
	>>
	>> document.search("/bookstore/book/author")
	=> ["<author>Giada De Laurentiis</author>", "<author>J K. Rowling</author>", "<author>James McGovern</author>", "<author>Per Bothner</author>", "<author>Kurt Cagle</author>", "<author>James Linn</author>", "<author>Vaidyanathan Nagarajan</author>", "<author>Erik T. Ray</author>"]
