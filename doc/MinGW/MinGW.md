# MinGW

```Makefile
# var
TARGET = i686-w64-mingw32

# cpp
CXX = g++
LD = ld
# mingw
XCXX = $(TARGET)-g++
XLD = $(TARGET)-ld
WINE = wine

# src
C += src/$(MODULE).cpp

# cfg
CFLAGS += -pipe -O0 -g2

# all
.PHONY: all
all: bin/$(MODULE).exe
	$(WINE) $^


```


## [[MinGW/libcxx]]