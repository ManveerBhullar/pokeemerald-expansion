CC ?= gcc

# Set PKG_CONFIG_PATH for macOS homebrew
PKG_CONFIG_PATH := /opt/homebrew/lib/pkgconfig:/opt/homebrew/Library/Homebrew/os/mac/pkgconfig/14:$(PKG_CONFIG_PATH)

CFLAGS = -Wall -Wextra -Werror -std=c11 -O2 -DPNG_SKIP_SETJMP_CHECK
CFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags libpng)

LIBS = -lpng -lz
LDFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs-only-L libpng)

SRCS = main.c convert_png.c util.c font.c

.PHONY: all clean

ifeq ($(OS),Windows_NT)
EXE := .exe
else
EXE :=
endif

all: rsfont$(EXE)
	@:

rsfont$(EXE): $(SRCS) convert_png.h gfx.h global.h util.h font.h
	$(CC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS) $(LIBS)

clean:
	$(RM) rsfont rsfont.exe
