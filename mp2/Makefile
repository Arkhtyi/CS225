EXENAME = testscene
OBJS = testscene.o png.o image.o rgbapixel.o scene.o

EXENAME2 = testimage
OBJS2 = testimage.o png.o image.o rgbapixel.o scene.o



CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME) $(EXENAME2)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

$(EXENAME2) : $(OBJS2)
	$(LD) $(OBJS2) $(LDFLAGS) -o $(EXENAME)

testscene.o : testscene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testscene.cpp

testimage.o : testimage.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testimage.cpp

png.o : png.cpp png.h image.h image.cpp
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

image.o : image.h image.cpp 
	$(CXX) $(CXXFLAGS) image.cpp

scene.o : scene.h scene.cpp
	$(CXX) $(CXXFLAGS) scene.cpp

clean :
	-rm -f *.o $(EXENAME)
