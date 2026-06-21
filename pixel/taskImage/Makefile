CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -O2 -Iinclude

SRC=src/main.cpp src/Image.cpp src/TemplateImage.cpp
OBJ=$(SRC:.cpp=.o)

image: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f image src/*.o
