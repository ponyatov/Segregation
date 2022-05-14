# MinGW/ `libcxx`
## install required .dll to project `/bin/`

- https://stackoverflow.com/questions/11703000/finding-dlls-required-of-a-win-exe-on-linux-cross-compiled-with-mingw

```Makefile
## Makefile

# mingw
XCXX = $(TARGET)-g++

# rule

GCCDLL = $(shell $(XCXX) -print-prog-name=cc1 | sed 's/.cc1$$//')

bin/%.dll: $(GCCDLL)/%.dll
	cp $< $@

DLL += bin/libgcc_s_dw2-1.dll
bin/$(MODULE).exe: $(DLL)
```
