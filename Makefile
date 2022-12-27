compiler = g++
cpp_version = -std=c++20
src_files = src/*.cpp
include_dir = -Iinclude
output_file = build/Raytracer
output_image = build/image.ppm

default:
	$(compiler) $(cpp_version) -Wall $(src_files) $(include_dir) -o $(output_file)
	$(output_file) > $(output_image)