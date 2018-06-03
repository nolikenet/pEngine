CFLAG= -std=c++14 -Wall -g 
SOURCE= $(wildcard *.cpp) $(wildcard */*.cpp) 
CC= g++
INCLUDES= -I../Libs/SDL2/include -I../Libs/SDL2_image-2.0.3 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glew/2.1.0/lib/ -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I../Libs/rapidjson/include
FRAMEWORKS= -F/Library/Frameworks -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/ -framework SDL2 -framework OpenGL -framework GLUT -framework SDL2_image

all:
	$(CC) $(CFLAG) $(INCLUDES) $(FRAMEWORKS) $(SOURCE) -o ../Output/Debug/Engine.out

clean: 
	rm ../Output/Debug/Engine.out 
	rm -r ../Output/Debug/Engine.out.dSYM
