require 'minitest/autorun'
require 'xpather/xpather'

class TestXPather < MiniTest::Unit::TestCase
  def test_basic_search
    document = XPather.new("test/books.xml")
    assert_equal ["Giada De Laurentiis"], document.search("/bookstore/book[1]/author") 
  end
end
