CXX ?= g++

# Optimize for M1 Max host compilation
ifeq ($(shell uname -m),arm64)
  CXXFLAGS := -Werror -std=c++17 -O3 -march=native -pipe
else
  CXXFLAGS := -Werror -std=c++17 -O2
endif

INCLUDES := -I .

SRCS := compresSmol.cpp compressAlgo.cpp tANS.cpp
TILEMAP_SRCS := mainTiles.cpp compressSmolTiles.cpp tANS.cpp compressAlgo.cpp

HEADERS := compressAlgo.h tANS.h
TILEMAP_HEADERS := compressSmolTiles.h tANS.h compressAlgo.h

ifeq ($(OS),Windows_NT)
EXE := .exe
else
EXE :=
endif

.PHONY: all clean

all: compresSmol$(EXE) compresSmolTilemap$(EXE)
	@:

compresSmol$(EXE): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $@ $(LDFLAGS)

compresSmolTilemap$(EXE): $(TILEMAP_SRCS) $(TILEMAP_HEADERS)
	$(CXX) $(CXXFLAGS) $(TILEMAP_INCLUDES) $(TILEMAP_SRCS) -o $@ $(LDFLAGS)

clean:
	$(RM) compresSmol compresSmol.exe compresSmolTilemap compresSmolTilemap.exe
