/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 18:00:00 by drosa-ta          #+#    #+#             */
/*   Updated: 2018/02/05 00:09:54 by drosa-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

bool init_window(bool fullscreen, const char *title, SDL_Window *window, SDL_Renderer* renderer)
{
	SDL_Surface *screenSurface = NULL;
	bool success;

	success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		success = put_error("SDL could not be initialized! SDL_Error: ");
	else
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
								  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
								  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
			success = put_error("Window could not be created! SDL_Error: ");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL)
			success = put_error("Renderer could not be created! SDL_Error: ");
		SDL_RenderPresent(renderer);
		// else
		// {
		// 	screenSurface = SDL_GetWindowSurface(window);
		// 	SDL_FillRect(screenSurface, NULL,
		// 				 SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		// 	SDL_UpdateWindowSurface(window);
		// 	SDL_Delay(2000);
		// }
	}
	return (success);
}

bool read()
{
	return (true);
}

void update()
{
	while(!done(true, true));
	//init variables
	//initial calculations
	//DDA

}

void end(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	// ft_putendl("Program quit successfully.");
	exit(1);
}

int main(int argc, char *args[])
{
	SDL_Window *window;
	SDL_Renderer* renderer;

	if (read() && init_window(false, "Wolf3D", window, renderer))
		update();
	end(window, renderer);
	return 0;
}

bool put_error(char *str)
{
	perror(str);
	perror(SDL_GetError());
	perror("\n");
	return (false);
}

bool keyDown(SDL_Scancode key)
{
    return (SDL_GetKeyboardState(NULL)[key] != 0);
}

//Returns 1 if you close the window or press the escape key.
//Also handles everything thats needed per frame.
bool done(bool quit_if_esc, bool delay)
{
	SDL_Event event;
	if (delay) SDL_Delay(5); //So it consumes less processing power
   
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) return true;
		if (quit_if_esc && keyDown(SDL_SCANCODE_ESCAPE))return true;
	}
	return false;
}