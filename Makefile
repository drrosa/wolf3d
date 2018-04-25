NAME = wolf3d
SRCS = wolf3d.c ray.c player.c screen.c input.c
LIBS = -lSDL2 -lSDL2main -lSDL2_mixer
WARNINGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@gcc -o $(NAME) $(WARNINGS) $(LIBS) $(SRCS)

debug:
	@gcc -g -o $(NAME) $(LIBS) $(SRCS)

clean:
	@/bin/rm -f

fclean:
	@/bin/rm -f $(NAME)

re: fclean all
