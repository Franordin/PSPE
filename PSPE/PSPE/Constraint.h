#pragma once

#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "Particle.h"
#include <cmath>
#include <limits>

class Constraint {
public:
	Particle* p1 = new Particle(1.0f, 1.0f);
	Particle* p2 = new Particle(1.0f, 1.0f);
	float initial_length;

	Constraint(Particle* p1, Particle* p2)
		: p1(p1), p2(p2),
		initial_length(std::hypot(p2->position.x - p1->position.x,
			p2->position.y - p1->position.y))
	{}

	/// Constraint Satisfaction - Maintain distance between two points
	void satisfy() {
		sf::Vector2f delta = p2->position - p1->position;
		float current_length = std::hypot(delta.x, delta.y);
		float difference = (current_length - initial_length) / current_length;
		sf::Vector2f correction = delta * 0.5f * difference;

		p1->position += correction;
		p2->position -= correction;
	}
};

#endif // CONSTRAINT_H
