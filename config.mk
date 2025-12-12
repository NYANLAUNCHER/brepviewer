# Configure Makefile environment
ifndef build
$(error Must provide variable: $$(build))
endif
ifndef pname
$(error Must provide variable: $$(pname))
endif
# Top-most directory of project; project root
export TOP := $(CURDIR)
export RESDEST := $(build)/share/$(pname)
# default flags
export CXXFLAGS = -std=c++20 -Wall
export CXXFLAGS += -g -ggdb -DDEBUG
