/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:11:48 by drosa-ta          #+#    #+#             */
/*   Updated: 2018/04/25 00:22:38 by drosa-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_file_len(const int fd)
{
	size_t	n;
	char	buf[BUFF_SIZE];
	int		is_eof;

	n = 0;
	is_eof = 0;
	if (fd == -1)
		return (0);
	while ((is_eof = read(fd, buf, BUFF_SIZE)))
		n = is_eof + n;
	close(fd);
	return (n);
}

char	*ft_file_to_str(const char *file_name)
{
	char	*str;
	int		fd;
	int		ret;
	size_t	n;

	if ((fd = open(file_name, O_RDONLY, S_IRUSR)))
		n = ft_file_len(fd);
	else
		return (0);
	fd = open(file_name, O_RDONLY, S_IRUSR);
	str = (char *)malloc(sizeof(char) * (n + 1));
	str[n + 1] = '\0';
	if (!str || fd == -1)
		return (0);
	ret = read(fd, str, n);
	if (ret == -1 || (!ret && n == 0))
		return (0);
	str[n] = '\0';
	close(fd);
	return (str);
}

bool	is_input_key(SDL_Keycode key)
{
	const Uint8 *input;

	input = SDL_GetKeyboardState(NULL);
	return (input[SDL_GetScancodeFromKey(key)] != 0);
}

bool	done(bool quit_if_esc, bool delay, Mix_Music *music)
{
	SDL_Event event;

	if (delay)
		SDL_Delay(5);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return (true);
		else if (quit_if_esc && is_input_key(SDLK_ESCAPE))
			return (true);
		else if (is_input_key(SDLK_9))
		{
			if (Mix_PlayingMusic() == 0)
				Mix_PlayMusic(music, -1);
			return (false);
		}
		else if (is_input_key(SDLK_0))
		{
			Mix_HaltMusic();
			return (false);
		}
	}
	return (false);
}

bool	put_error(char *str)
{
	perror(str);
	perror(SDL_GetError());
	perror("\n");
	return (false);
}
