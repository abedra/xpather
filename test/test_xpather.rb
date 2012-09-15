require 'minitest/autorun'
require 'test_helper'
require 'xpather'

class TestXPather < MiniTest::Unit::TestCase
  def setup
    @document = XPather.new(XML)
  end

  def test_basic_search_one
    assert_equal("Giada De Laurentiis", @document.search("/bookstore/book[1]/author"))
  end

  def test_basic_search_collection

    assert_equal(["<author>James McGovern</author>", "<author>Per Bothner</author>", "<author>Kurt Cagle</author>",
                  "<author>James Linn</author>", "<author>Vaidyanathan Nagarajan</author>"],
                 @document.search("/bookstore/book[3]/author"))
  end

  def test_non_matches_return_nil
    assert_nil(@document.search("/foo"))
  end
end
