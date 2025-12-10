ifndef build
$(error Must provide variable: $$(build))
endif
ifndef pname
$(error Must provide variable: $$(pname))
endif
export TOP := $(CURDIR)
export RESDEST := $(build)/share/$(pname)
# Default flags
export CXXFLAGS = -g -ggdb -DDEBUG
