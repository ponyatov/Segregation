# var
MODULE = $(notdir $(CURDIR))
module = $(shell echo $(MODULE) | tr A-Z a-z)
OS     = $(shell uname -o|tr / _)
NOW    = $(shell date +%d%m%y)
REL    = $(shell git rev-parse --short=4 HEAD)
BRANCH = $(shell git rev-parse --abbrev-ref HEAD)
PEPS   = E26,E302,E305,E401,E402,E701,E702
TARGET = i686-w64-mingw32

# tool
CURL   = curl -L -o
CF     = clang-format
PY     = $(shell which python3)
PIP    = $(shell which pip3)
PEP    = $(shell which autopep8)
# cpp
CXX    = g++
LD     = ld
# mingw
XCXX   = $(TARGET)-g++
XLD    = $(TARGET)-ld
WINE   = wine

# src
P += metaL.gen rc
S += $(P)
C += src/$(MODULE).cpp
H += inc/$(MODULE).hpp
S += $(C) $(H)

DLL += bin/libgcc_s_dw2-1.dll
DLL += bin/$(MODULE).dll

DC = $(shell find src -type f -regex '.+cpp$$' | grep -v $(C))
L += -Lbin -l$(MODULE)

# cfg
CFLAGS += -pipe -O0 -g2 -Iinc -Itmp

# all
.PHONY: all
all: bin/$(MODULE).exe
	$(WINE) $<

GEN = cpp mingw dll
.PHONY: gen
gen:
	./metaL.gen $(GEN) && $(MAKE) format

# format
.PHONY: format
format: tmp/format_py tmp/format_cpp

tmp/format_py: $(P)
	$(PEP) --ignore=$(PEPS) -i $? && touch $@

tmp/format_cpp: $(C) $(H) $(DC)
	$(CF) -style=file -i $? && touch $@

# rule
bin/$(MODULE).exe: $(C) $(H) Makefile $(DLL)
	$(XCXX) $(CFLAGS) -o $@ $(C) $(L)

bin/$(MODULE).dll: $(DC) Makefile
	$(XCXX) $(CFLAGS) -o $@ -s -shared $(DC) -Wl,--subsystem,windows

GCCDLL = $(shell $(XCXX) -print-prog-name=cc1 | sed 's/.cc1$$//')
bin/%.dll: $(GCCDLL)/%.dll
	cp $< $@

bin/$(MODULE).exe: $(DLL)

# doc

.PHONY: doxy
doxy: doxy.gen
	rm -rf docs ; doxygen $< 1>/dev/null

.PHONY: doc
doc:
	rsync -vss ~/mdoc/Segregation/README.md README.md
	rsync -vss ~/mdoc/Segregation/*         doc/Segregation/
	rsync -vss ~/mdoc/MinGW/*               doc/MinGW/

# install
install: $(OS)_install doc gz
	$(MAKE) update
update: $(OS)_update doc gz

GNU_Linux_install:
GNU_Linux_update:
	sudo apt update
	sudo apt install -yu `cat apt.txt`

gz:

# merge
MERGE  = Makefile README.md .clang-format doxy.gen apt.dev apt.txt $(S)
MERGE += .vscode bin doc lib src tmp inc
MERGE += static templates

dev:
	git push -v
	git checkout $@
	git pull -v
	git checkout shadow -- $(MERGE)

shadow:
	git push -v
	git checkout $@
	git pull -v

release:
	git tag $(NOW)-$(REL)
	git push -v --tags
	$(MAKE) shadow

ZIP = tmp/$(MODULE)_$(NOW)_$(REL)_$(BRANCH).zip
zip:
	git archive --format zip --output $(ZIP) HEAD
