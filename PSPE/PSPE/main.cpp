#include <SFML/Graphics.hpp>
#include <vector>

#include "Particle.h"
#include "Constraint.h"

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
	particles.emplace_back(WIDTH / 2 + 50, HEIGHT / 2 + 50);
	particles.emplace_back(WIDTH / 2 + 50, HEIGHT / 2 - 50);
	particles.emplace_back(WIDTH / 2 - 50, HEIGHT / 2 + 50);
	particles.emplace_back(WIDTH / 2 - 50, HEIGHT / 2 - 50);

	std::vector<Constraint> constraints;
	constraints.emplace_back(&particles[0], &particles[1]);
	constraints.emplace_back(&particles[0], &particles[2]);
	constraints.emplace_back(&particles[0], &particles[3]);
	constraints.emplace_back(&particles[0], &particles[4]);
	constraints.emplace_back(&particles[1], &particles[2]);
	constraints.emplace_back(&particles[1], &particles[3]);
	constraints.emplace_back(&particles[1], &particles[4]);
	constraints.emplace_back(&particles[2], &particles[3]);
	constraints.emplace_back(&particles[2], &particles[4]);
	constraints.emplace_back(&particles[3], &particles[4]);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		/// Apply gravity and update particles
		for (auto& particle : particles) {
			particle.apply_force(sf::Vector2f(0, GRAVITY));
			particle.update(TIME_STEP);
			particle.constraint_to_bounds(WIDTH, HEIGHT, PARTICLE_RADIOUS);
		}

		for (size_t i = 0; i < 5; i++)
			for (auto& constraint : constraints)
				constraint.satisfy();

		window.clear(sf::Color::Black);

		/// Draw particles as balls
		for (const auto& particle : particles) {
			sf::CircleShape circle(PARTICLE_RADIOUS);
			circle.setFillColor(sf::Color::White);
			circle.setPosition(particle.position.x - PARTICLE_RADIOUS,
								particle.position.y - PARTICLE_RADIOUS);
			window.draw(circle);
		}

		/// Draw constraints as lines
		for (const auto& constraint : constraints) {
			sf::Vertex line[] = {
				sf::Vertex(constraint.p1->position, sf::Color::Green),
				sf::Vertex(constraint.p2->position, sf::Color::Green),
			};

			window.draw(line, 2, sf::Lines);
		}

		window.display();
	}
}
