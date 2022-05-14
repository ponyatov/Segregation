# var
MODULE = $(notdir $(CURDIR))
module = $(shell echo $(MODULE) | tr A-Z a-z)
OS     = $(shell uname -o|tr / _)
NOW    = $(shell date +%d%m%y)
REL    = $(shell git rev-parse --short=4 HEAD)
BRANCH = $(shell git rev-parse --abbrev-ref HEAD)
PEPS   = E26,E302,E305,E401,E402,E701,E702

# tool
CURL   = curl -L -o
CF     = clang-format
PY     = $(shell which python3)
PIP    = $(shell which pip3)
PEP    = $(shell which autopep8)

# src
P += metaL.gen rc
S += $(P)

# all
.PHONY: all
all:

GEN =
.PHONY: gen
gen:
	./metaL.gen $(GEN) && $(MAKE) format

# format
.PHONY: format
format: tmp/format_py

tmp/format_py: $(P)
	$(PEP) --ignore=$(PEPS) -i $? && touch $@

# doc
doxy: doxy.gen
	rm -rf docs ; doxygen $< 1>/dev/null

doc:

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
MERGE  = Makefile README.md .clang-format doxy.gen $(S)
MERGE += apt.dev apt.txt requirements.txt
MERGE += .vscode bin doc lib src tmp
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
