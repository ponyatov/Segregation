# MinGW

```Makefile
## Makefile

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
CFLAGS += -pipe -O0 -g2 -Iinc -Itmp

# all
.PHONY: all
all: bin/$(MODULE).exe
	$(WINE) $^

# rule
bin/$(MODULE).exe: $(C) $(H) Makefile
	$(XCXX) $(CFLAGS) -o $@ $(C) $(L)
```

## Build [[MinGW/DLL|.dll]] with MinGW

## [[MinGW/libcxx]]

## Configure [[MinGW/VSCode]] for cross-compile