CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude

SRC=src/main.cpp \
    src/Date.cpp src/Request.cpp src/Response.cpp \
    src/Attachment.cpp src/Image.cpp src/Video.cpp \
    src/Content.cpp src/PostMessage.cpp src/LongVideo.cpp src/ShortVideo.cpp \
    src/Published.cpp \
    src/Service.cpp src/Telegram.cpp src/Max.cpp src/RuTube.cpp src/VKClips.cpp
OBJ=$(SRC:.cpp=.o)

messangers: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f messangers src/*.o
