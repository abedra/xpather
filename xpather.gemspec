spec = Gem::Specification.new do |s|
  s.name              = "xpather"
  s.version           = "0.0.7"
  s.platform          = Gem::Platform::RUBY
  s.authors           = ["Aaron Bedra"]
  s.email             = ["aaron@aaronbedra.com"]
  s.homepage          = "https://github.com/abedra/xpather"
  s.summary           = %q{Quick and painless XPath searching for Ruby}
  s.description       = %q{Quick and painless XPath searching for Ruby using libxml2}
  s.rubyforge_project = "xpather"
  s.files             = Dir.glob('lib/**/*.rb') + Dir.glob('ext/**/*.c')
  s.extensions        = %w{ext/xpather/extconf.rb}
  s.require_paths     = ["lib", "ext"]
end
