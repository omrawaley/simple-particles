/*
Copyright 2023 Om Rawaley (@omrawaley)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <SDL2/SDL.h>
#include <iostream>

// include the library
#include "particles/particleSystem.h"

int main()
{
	// seed the random number generator
	srand(time(nullptr));

	SDL_Window* window = SDL_CreateWindow("Simple Particles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// create a new particle system
	SimpleParticles::ParticleSystem particleSystem = SimpleParticles::ParticleSystem(40, SimpleParticles::Vector2(0, 600), 2, 2, true);

	// set the texture of the particles
	particleSystem.setParticleTexture(renderer, "assets/particleTexture.png", 0.03);

	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	uint32_t last = SDL_GetTicks();

	bool quit;
	while(!quit)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event) > 0)
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							quit = true;
							break;

						case SDLK_RETURN:
							// randomize the particles
							particleSystem.randomize(-500, 500, -600, 400, 800, 1000, 1, 2);

							// set the particles somewhere in the middle of the screen
							particleSystem.setPosition(SimpleParticles::Vector2(width / 2, height / 2));
							break;

						case SDLK_RSHIFT:
							// toggle trail rendering
							particleSystem.setTrailRendering(!particleSystem.getTrailRendering());
						break;
					}
					break;
			}
		}

		uint32_t current = SDL_GetTicks();

		float dT = (current - last) / 1000.0f;

		last = current;

		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		// update the particles and provide delta time
		particleSystem.update(dT);

		// draw the particles with optional values for trails
		particleSystem.draw(renderer, 0.04, 255, 100);

		SDL_RenderPresent(renderer);	
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}