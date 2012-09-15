require 'minitest/autorun'
require 'test_helper'
require 'xpather'

class TestXPather < MiniTest::Unit::TestCase
  def setup
    @document = XPather.new(XML)
  end

  def test_basic_get_one
    assert_equal("Giada De Laurentiis", @document.get("/bookstore/book[1]/author"))
  end

  def test_basic_get_collection
    assert_equal(["James McGovern", "Per Bothner", "Kurt Cagle", "James Linn", "Vaidyanathan Nagarajan"],
                 @document.get("/bookstore/book[3]/author"))
  end

  def test_get_non_matches_return_nil
    assert_nil(@document.get("/foo"))
  end

  def test_basic_search_one
    assert_equal(["<author>Giada De Laurentiis</author>"], @document.search("/bookstore/book[1]/author"))
  end

  def test_basic_search_collection

    assert_equal(["<author>James McGovern</author>", "<author>Per Bothner</author>", "<author>Kurt Cagle</author>",
                  "<author>James Linn</author>", "<author>Vaidyanathan Nagarajan</author>"],
                 @document.search("/bookstore/book[3]/author"))
  end

  def test_search_non_matches_return_empty_array
    assert_empty(@document.search("/foo"))
  end
end
