require 'rake'
require 'rake/testtask'
require 'rake/extensiontask'
#load 'lib/xpather.rb'

spec = Gem::Specification.new do |s|
  s.name        = "xpather"
  s.version     = "0.0.2"
  s.platform    = Gem::Platform::RUBY
  s.authors     = ["Aaron Bedra"]
  s.email       = ["aaron@aaronbedra.com"]
  s.homepage    = "https://github.com/abedra/xpather"
  s.summary     = %q{Quick and painless XPath searching for Ruby}
  s.description = %q{Quick and painless XPath searching for Ruby using libxml2}

  s.rubyforge_project = "xpather"

  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test}/*`.split("\n")
  s.require_paths = ["lib", "ext"]
  s.extensions = %w{ext/xpather/extconf.rb}

  s.add_development_dependency "rake-compiler", "~> 0.7.9"
end

Gem::PackageTask.new(spec) do |pkg|
end

Rake::ExtensionTask.new('xpather', spec)

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/*_test.rb']
  t.verbose = true
end

task :default => ["compile", "test"]
