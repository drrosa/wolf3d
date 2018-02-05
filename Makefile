all:
	gcc wolf3d.c -I SDL2/ -L SDL2/ -lSDL2 -o wolf3d
#set -x DYLD_LIBRARY_PATH $PWD/libs/ $DYLD_LIBRARY_PATH
