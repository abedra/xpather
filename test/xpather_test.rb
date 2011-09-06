require 'minitest/autorun'
require 'xpather/xpather'

class TestXPather < MiniTest::Unit::TestCase
  def setup
    @document = XPather.new("test/books.xml")
  end

  def test_basic_search_one
    assert_equal "Giada De Laurentiis", @document.search("/bookstore/book[1]/author") 
  end

  def test_basic_search_collection
    assert_equal ["James McGovern", "Per Bothner", "Kurt Cagle", "James Linn", "Vaidyanathan Nagarajan"], 
                 @document.search("/bookstore/book[3]/author")
  end  
end
