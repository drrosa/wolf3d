all:

tutorial:
	gcc tutorial.c -I SDL2/ -L SDL2/ -lSDL2 -o tutorial

example:
	g++ example.c instantcg.cpp -L ~/.brew/lib/ -lSDL2 -lSDL2main -I. -I ~/.brew/include/ -o example

rayflat:
	g++ -g raycaster_flat.cpp -L ~/.brew/lib/ -lSDL2 -lSDL2main -I. -I ~/.brew/include/ instantcg.cpp -o rayflat

wolf3d:
	gcc -g wolf3d.c ray.c player.c screen.c input.c -L ~/.brew/lib/ -lSDL2 -lSDL2main -I. -I ~/.brew/include/ -o wolf3d

re: clean wolf3d
	./wolf3d

clean:
	rm wolf3d
#set -x DYLD_LIBRARY_PATH $PWD/libs/ $DYLD_LIBRARY_PATH
