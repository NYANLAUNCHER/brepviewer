# vim: filetype=make

GL3W_TARGETS = gl3w.o include/GL/gl3w.h
$(GL3W_TARGETS): gl3w/src/gl3w.c gl3w/include/GL/gl3w.h
	@echo -e "\x1b[36mBuilding gl3w:\x1b[0m"
	cd gl3w/ && \
	gcc -c -Iinclude/ src/gl3w.c && \
	cp -r include/ gl3w.o ..
	@echo

gl3w/src/gl3w.c:
	cd gl3w/ && \
	scons
	@echo

LIB_TARGETS = $(GL3W_TARGETS)
