CC = gcc
# optional flags, typically for optimization or debuggin'
OPT = -O0 -ggdb
DEPFLAGS = -MP -MMD
LIBS = glfw cglm GL m pthread Xrandr Xi dl
LIBFLAGS = $(addprefix -l,$(LIBS))
CFLAGS = -Ilib/include -Llib $(LIBFLAGS) $(DEPFLAGS) $(OPT)
TARGET_EXEC = brepviewer

.PHONY: run
run: $(TARGET_EXEC)
	./$(TARGET_EXEC)

$(TARGET_EXEC):
	$(CC) src/*.c $(CFLAGS) -o $(TARGET_EXEC)

