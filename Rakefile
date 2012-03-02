require 'rake/testtask'
require 'rake/clean'
require 'rbconfig'

NAME = 'xpather'
EXT = RbConfig::CONFIG['DLEXT']

file "lib/#{NAME}/#{NAME}.#{EXT}" => Dir.glob("ext/#{NAME}/*.c") do
  Dir.chdir("ext/#{NAME}") do
    ruby "extconf.rb"
    sh "make"
  end
  cp "ext/#{NAME}/#{NAME}.#{EXT}", "lib/#{NAME}"
end

task :test => "lib/#{NAME}/#{NAME}.#{EXT}"

CLEAN.include("ext/**/*{.o,.log,.#{EXT}}")
CLEAN.include("ext/**/Makefile")
CLOBBER.include("lib/**/*.#{EXT}")

Rake::TestTask.new do |t|
  t.libs << 'test'
end

task :default => :test
