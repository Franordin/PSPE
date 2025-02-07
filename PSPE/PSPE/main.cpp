#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "particle.h"

const int WIDTH = 1080;
const int HEIGHT = 640;
const float PARTICLE_RADIOUS = 30.0f;
const float GRAVITY = 10.0f;
const float TIME_STEP = 0.1f;

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth Simulation");
	window.setFramerateLimit(60);

	std::vector<Particle> particles;
	particles.emplace_back(WIDTH / 2, HEIGHT / 2);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		// Apply gravity and update particles
		for (auto& particle : particles) {
			particle.apply_force(sf::Vector2f(0, GRAVITY));
			particle.update(TIME_STEP);
			particle.constrain_to_bounds(WIDTH, HEIGHT, PARTICLE_RADIOUS);
		}

		window.clear(sf::Color::Black);

		// Draw particles as balls
		for (const auto& particle : particles) {
			sf::CircleShape circle(PARTICLE_RADIOUS);
			circle.setFillColor(sf::Color::White);
			circle.setPosition(particle.position.x - PARTICLE_RADIOUS,
								particle.position.y - PARTICLE_RADIOUS);
			window.draw(circle);
		}

		window.display();
	}
}
