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

#include "particleSystem.h"

namespace SimpleParticles
{
	ParticleSystem::ParticleSystem(int amount, Vector2 gravity, float rotationSpeed, int trailsPerParticle, bool renderTrails) : rotationSpeed{rotationSpeed}, gravity{gravity}, trailsPerParticle{trailsPerParticle}, renderTrails{renderTrails}
	{
		this->addParticles(amount);
	}

	void ParticleSystem::addParticles(int amount)
	{
		for(size_t i = 0; i < amount; ++i)
		{
			this->particles.push_back(Particle());
		}
	}

	void ParticleSystem::setParticleTexture(SDL_Renderer* renderer, const char* imagePath, float textureScaleFactor)
	{
		SDL_Texture* imageTexture = IMG_LoadTexture(renderer, imagePath);

		SDL_SetTextureBlendMode(imageTexture, SDL_BLENDMODE_BLEND);

		for(auto& particle : this->particles)
		{
			particle.texture = imageTexture;
		}

		this->textureScaleFactor = textureScaleFactor;
	}

	void ParticleSystem::setPosition(Vector2 pos)
	{
		for(auto& particle : this->particles)
		{
			particle.pos.x = pos.x;
			particle.pos.y = pos.y;
		}
	}

	bool ParticleSystem::getTrailRendering()
	{
		return this->renderTrails;
	}

	void ParticleSystem::setTrailRendering(bool enable)
	{
		this->renderTrails = enable;
	}

	void ParticleSystem::randomize(int xVelMin, int xVelMax, int yVelMin, int yVelMax, int lifeMin, int lifeMax, int sizeMin, int sizeMax)
	{
		for(auto& particle : this->particles)
		{
			particle.vel.x = (rand() % (xVelMax - xVelMin)) + xVelMin;
			particle.vel.y = (rand() % (yVelMax - yVelMin)) + yVelMin;

			particle.angle = (rand() % 360);

			particle.size = sizeMin + (rand() % (sizeMax - sizeMin));

			particle.lifetime = lifeMin + (rand() % (lifeMax - lifeMin));
		}
	}

	void ParticleSystem::update(float dT)
	{
		for(auto& particle : this->particles)
		{
			if(particle.lifetime <= 0)
				continue;

			particle.angle += this->rotationSpeed * particle.vel.x * dT;

			particle.vel += this->gravity * Vector2(dT, dT);

			particle.pos += particle.vel * Vector2(dT, dT);

			particle.lifetime -= 1 * dT;
		}
	}

	void ParticleSystem::draw(SDL_Renderer* renderer, float trailDelayFactor, int particleOpacity, int trailOpacity)
	{
		for(size_t i = 0; i < this->particles.size(); ++i)
		{
			if(this->particles[i].lifetime <= 0)
				continue;

			int textureWidth, textureHeight;
			SDL_QueryTexture(this->particles[i].texture, nullptr, nullptr, &textureWidth, &textureHeight);

			SDL_FRect particleRect;
			particleRect.x = this->particles[i].pos.x;
			particleRect.y = this->particles[i].pos.y;
			particleRect.w = textureWidth * this->particles[i].size * this->textureScaleFactor;
			particleRect.h = textureHeight * this->particles[i].size * this->textureScaleFactor;

			SDL_SetTextureAlphaMod(this->particles[i].texture, particleOpacity);

			SDL_RenderCopyExF(renderer, this->particles[i].texture, nullptr, &particleRect, this->particles[i].angle, nullptr, SDL_FLIP_NONE);

			if(!this->renderTrails)
				continue;

			for(size_t j = 1; j < (this->trailsPerParticle + 1); ++j)
			{
				SDL_FRect trailRect;
				trailRect.x = this->particles[i].pos.x - this->particles[i].vel.x * (trailDelayFactor * j);
				trailRect.y = this->particles[i].pos.y - this->particles[i].vel.y * (trailDelayFactor * j);
				trailRect.w = textureWidth * this->particles[i].size * this->textureScaleFactor;
				trailRect.h = textureHeight * this->particles[i].size * this->textureScaleFactor;

				SDL_SetTextureAlphaMod(this->particles[i].texture, trailOpacity);

				SDL_RenderCopyExF(renderer, this->particles[i].texture, nullptr, &trailRect, this->particles[i].angle, nullptr, SDL_FLIP_NONE);
			}
		}
	}
}