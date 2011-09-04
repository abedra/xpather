# XPather

    $ gem install xpather    
    $ irb -rxpather
    >> document = XPather.new("test/books.xml")
    => #<XPather:test/books.xml>
    >> document.search("/bookstore/book[1]/author")
    => ["Giada De Laurentiis"]
