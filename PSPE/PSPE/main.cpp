#include <SFML/Graphics.hpp>
#include <vector>

#include "particle.h"

const int WIDTH = 1080;
const int HEIGHT = 720;
const float PARTICLE_RADIOUS = 30.0f;

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth Simulation");

	std::vector<Particle> particles;
	particles.emplace_back(WIDTH / 2, HEIGHT / 2);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear(sf::Color::Black);

		// Draw particles as balls
		for (const auto& particle : particles) {
			sf::CircleShape circle(PARTICLE_RADIOUS);
			circle.setFillColor(sf::Color::White);
			circle.setPosition(particle.position.x - 15, particle.position.y - 15);
			window.draw(circle);
		}

		window.display();
	}
}
