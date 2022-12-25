all:
	g++ -std=c++20 -Wall src/Main.cpp -o build/Raytracer
	./build/Raytracer > build/image.ppm