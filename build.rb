#! /usr/bin/env ruby
require 'fileutils'
require 'erb'

def create_from_erb(filename_in, filename_out)
  unless filename_in.end_with?'.erb'
    puts "ERROR this is not a erb template"
  end
  erb_template = File.read(filename_in)

  created_file = ""
  created_file += ERB.new(erb_template, nil, '>').result()

  File.write(filename_out, created_file)
end

if __FILE__ == $0
  build_dir = File.join(__dir__, 'build')
  src_dir = File.join(__dir__, 'src')
  output_dir = File.join(__dir__, 'output')
  FileUtils.mkdir_p(build_dir) unless File.directory?(build_dir)

  Dir[File.join(src_dir, '*')].each do |filename|
    FileUtils.cp(filename, build_dir)
    next unless filename.end_with? '.erb'
    create_from_erb(filename, File.join(build_dir, File.basename(filename, '.erb')))
  end

  FileUtils.mkdir_p(output_dir) unless File.directory?(output_dir)

  `cmake .`
  `make`


  # FileUtils.rm_rf(build_dir)
end
