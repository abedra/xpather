require 'mdpxpath'

d = MDPXPath.new("books.xml")

puts d.filename

puts d.search("/bookstore/book[1]/author")
