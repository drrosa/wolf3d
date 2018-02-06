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

int main(int argc, char *args[])
{
	SDL_Window *window;
	SDL_Renderer* renderer;
	window = init_window(false, "Wolf3D");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		put_error("Renderer could not be created! SDL_Error: ");
	SDL_RenderPresent(renderer);
	sleep();
	end(renderer, window);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

SDL_Window *init_window(bool fullscreen, const char *title)
{
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		put_error("SDL could not be initialized! SDL_Error: ");
	}
	else
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
								  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
								  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
			put_error("Window could not be created! SDL_Error: ");
		// else
		// {
		// 	screenSurface = SDL_GetWindowSurface(window);
		// 	SDL_FillRect(screenSurface, NULL,
		// 				 SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		// 	SDL_UpdateWindowSurface(window);
		// 	SDL_Delay(2000);
		// }
	}
	return (window);
}

void put_error(char *str)
{
	perror(str);
	perror(SDL_GetError());
	perror("\n");
	SDL_Quit();
	exit(-1);
}

// pauses the program until you press a key
void sleep()
{
	SDL_Event event = {0};
  bool done = false;
  while(done == false)
  {
    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) return ;
      if (event.type == SDL_KEYDOWN) done = true;
    }
    SDL_Delay(5);
  }
}

void end(SDL_Renderer *renderer, SDL_Window *window)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(1);
}