# Housekeeping:
.SUFFIXES:
.SUFFIXES: .c .cpp .o .d
##### Includes: ##########
include ./config.mk
#include ./lib/include.mk
##### Prerequisites: #####
SRCDIR := ./src
RESDIR := ./res
CXXSRCS := $(shell find $(SRCDIR) -type f -name "*.cpp")
DEPS := $(CXXSRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.d)
-include $(DEPS)
##### Targets: ###########
TARGET := $(build)/bin/$(pname)
OBJDIR := $(build)/.obj_tree
CXXOBJS := $(CXXSRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
RESOURCES := $(addprefix $(RESDEST)/,$(shell realpath --relative-to=$(RESDIR) $(shell find $(RESDIR) -type f)))
SUBMAKE := $(shell dirname $(shell find . -name "submake.mk") 2>/dev/null || true)
##### Flags: #############
CXXFLAGS +=
LDFLAGS += -lm -lGL -lGLEW -lglfw -lglm
##########################

# STYLE:
# - inputs use relative paths
# - outputs use absolute paths
# Manditory rules:
# - `make build` build $(TARGET)
# - `make run` build and execute $(TARGET)
# - `make clean` clean all artifacts
# - `make install` sync $(out) with $(build)

#### User-Invoked Rules: ####
.DEFAULT_GOAL :=
.PHONY: build
build: $(SUBMAKE) # $(SUBMAKE) is always the first target to run
	@$(MAKE) -i .ccls
	@$(MAKE) -i $(RESOURCES)
	@$(MAKE) $(TARGET)

develop: .dev-profile
	. $(realpath $<)

.PHONY: run
run: build
	@echo -e '\n\033[0;34m$(TARGET)\033[0m'
	@$(TARGET)

.PHONY: debug
debug: build
	clear
	gdb $(TARGET)

.PHONY: clean
clean:
	@echo -e '\033[0;32mCleaning build artifacts\033[0m'
	rm -rf $(build)/* $(build)/.*

.PHONY: install
install: # sync $(build) and $(out)
ifndef out
	$(error Variable $$(out) must be defined for `make install`)
endif
	rsync -a --delete $(build)/ $(out)

#### Tools: ####
.dev-profile: flake.nix flake.lock
	nix print-dev-env > $@

.ccls: 
	@echo -e '\033[0;32mRunning rule: \033[0;34m$@\033[0m'
	echo $(CXX) > .ccls
	echo $(CXXFLAGS) \
	     $(NIX_CFLAGS_COMPILE) | sed 's/ -/\n-/g' | tr -d ' ' >> $@
############################

.PHONY: $(SUBMAKE)
$(SUBMAKE):
	@echo -e '\033[0;32mRunning submake: \033[0;34m./$(shell realpath --relative-to=./ $@)/\033[0m'
	@$(MAKE) -C $@ -f submake.mk

$(TARGET): $(CXXOBJS)
	@echo -e '\033[0;32mBuilding target: \033[0;34m$(addprefix ./,$(shell realpath --relative-to=./ $@))\033[0m'
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(CXXOBJS) -o $@

# $(CXXSRCS) -> $(CXXOBJS)
$(CXXOBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo -e '\033[0;32mCompiling object: \033[0;34m$(addprefix ./,$(shell realpath -m --relative-to=./ $@))\033[0m'
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $(realpath $<) -o $@

$(RESOURCES): $(RESDEST)/%: $(RESDIR)/%
	@echo -e '\033[0;32mUpdating resource: \033[0;34m$(addprefix ./,$(shell realpath -m --relative-to=./ $@))\033[0m'
	mkdir -p $(dir $@)
	cp $(shell realpath -m $<) $@
