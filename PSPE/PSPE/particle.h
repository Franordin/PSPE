#pragma once

#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
public:
	sf::Vector2f position;
	sf::Vector2f previous_position;
	sf::Vector2f acceleration;

	Particle(float x, float y)
		: position(x, y), previous_position(x, y), acceleration(x, y)
	{}

	void apply_force(const sf::Vector2f& force) {
		acceleration += force;
	}

	void update(float time_step) {
		// verlet integration
		sf::Vector2f velocity = position - previous_position;
		previous_position = position;
		position += velocity + acceleration * time_step * time_step;
		acceleration = sf::Vector2f(0, 0); // reset after update
	}
};

#endif // PARTICLE_H
