NAME = wolf3d
SRCS = wolf3d.c ray.c player.c screen.c input.c
LIBS = -L ~/.brew/lib/ -lSDL2 -lSDL2main
INCLUDES = -I . -I ~/.brew/include/
WARNINGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@gcc -o $(NAME) $(WARNINGS) $(LIBS) $(INCLUDES) $(SRCS)

debug:
	@gcc -g -o $(NAME) $(LIBS) $(INCLUDES) $(SRCS)

clean:
	@/bin/rm -f

fclean:
	@/bin/rm -f $(NAME)

re: fclean all
