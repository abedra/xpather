# XPather

    $ gem install xpather    
    $ irb -rxpather
    >> document = XPather.new("test/books.xml")
    => #<XPather:test/books.xml>
    >> document.search("/bookstore/book[1]/author")
    => "Giada De Laurentiis"
    >> document.search("/bookstore/book/author")
	=> ["Giada De Laurentiis", "J K. Rowling", "James McGovern", "Per Bothner", "Kurt Cagle", "James Linn", "Vaidyanathan Nagarajan", "Erik T. Ray"]
