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
#include <cstdlib>
#include <vector>

#include "particle.h"

namespace SimpleParticles
{
	class ParticleSystem
	{
		private:
			Vector2 gravity;
	
			float rotationSpeed;
	
			float textureScaleFactor;

			int trailsPerParticle;

			bool renderTrails;

		private:
			void addParticles(int amount);
	
		public:
			void setParticleTexture(SDL_Renderer* renderer, const char* imagePath, float textureScaleFactor);
	
			void setPosition(Vector2 pos);

			bool getTrailRendering();
			void setTrailRendering(bool enable);
	
			void randomize(int xVelMin, int xVelMax, int yVelMin, int yVelMax, int lifeMin, int lifeMax, int sizeMin, int sizeMax);
	
			void update(float dT);
			void draw(SDL_Renderer* renderer, float trailDelayFactor = 0.04, int particleOpacity = 255, int trailOpacity = 100);
	
		public:
			ParticleSystem(int amount, Vector2 gravity, float rotationSpeed, int trailsPerParticle = 0, bool renderTrails = false);
	
		private:
			std::vector<Particle> particles;
	};
}