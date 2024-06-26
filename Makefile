export CC := gcc
export PROJ_ROOT := $(realpath .)
export BUILD_DIR := build
TARGET_EXEC := brepviewer
OPTFLAGS := -O0 -ggdb
LIBS := glfw cglm GL m pthread Xrandr Xi dl
CFLAGS := -Ilib/include -Llib $(addprefix -l,$(LIBS)) $(OPTFLAGS)

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=$(BUILD_DIR)/%.o) $(wildcard lib/*.o)
DEPS := $(OBJS:.o=.d)

.PHONY: run
run: $(TARGET_EXEC)
	./$(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -MP -MMD -c $< -o $@

-include $(DEPS)

lib/%.o:
	$(MAKE) -C lib/
