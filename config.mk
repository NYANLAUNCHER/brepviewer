# Configure Makefile environment
ifndef pname
$(error Must provide variable: $$(pname))
endif
# Top-most directory of project; project root
export TOP := $(CURDIR)
export build := $(TOP)/build
export RESDEST := $(build)/share/$(pname)
# default flags
export CXXFLAGS = -std=c++20 -Wall
export CXXFLAGS += -g -ggdb -DDEBUG
