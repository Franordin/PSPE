#pragma once

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Particle.h"
#include "Constraint.h"

const float CLICK_TOLERANCE = 5.0f;


class InputHandler {
public:
	static void handle_mouse_click(const sf::Event& event, std::vector<Particle>& particles,
									std::vector<Constraint>& constraints) {
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			float mouse_x = static_cast<float>(event.mouseButton.x);
			float mouse_y = static_cast<float>(event.mouseButton.y);
			tear_cloth(mouse_x, mouse_y, particles, constraints);
		}
	}

private:
	static float point_to_segment_distance(float mouse_x, float mouse_y, float p1_x, float p1_y, float p2_x, float p2_y) {
		float P2P1_x = p2_x - p1_x;
		float P2P1_y = p2_y - p1_y;

		float MP1_x = mouse_x - p1_x;
		float MP1_y = mouse_y - p1_y;

		float MP2_x = mouse_x - p2_x;
		float MP2_y = mouse_y - p2_y;

		float dot_P2P1_MP1 = P2P1_x * MP1_x + P2P1_y * MP1_y;
		float dot_P2P1 = P2P1_x * P2P1_x + P2P1_y * P2P1_y;
		float t = dot_P2P1 > 0 ? dot_P2P1_MP1 / dot_P2P1 : 0;

		/// Project point P on the line segment AB
		if (t < 0.0f) {
			/// P is closer to p1
			return std::sqrt(MP1_x * MP1_x + MP1_y * MP1_y);
		}
		else if (t > 1.0f) {
			/// P is closer to p2
			return std::sqrt(MP2_x * MP2_x + MP2_y * MP2_y);
		}
		else {
			/// projection point is on the segment
			float proj_x = p1_x + t * P2P1_x;
			float proj_y = p1_y + t * P2P1_y;
			
			return std::sqrt((mouse_x - proj_x) * (mouse_x - proj_x) + (mouse_y - proj_y) * (mouse_y - proj_y));
		}
	}

	static Constraint* find_nearest_constraint(float mouse_x, float mouse_y,
												const std::vector<Constraint>& constraints) {
		Constraint* nearest_constraint = nullptr;
		float min_distance = CLICK_TOLERANCE;

		for (const auto& constraint : constraints) {
			float distance = point_to_segment_distance(mouse_x, mouse_y,
								constraint.p1->position.x, constraint.p1->position.y,
								constraint.p2->position.x, constraint.p2->position.y);
			if (distance < min_distance) {
				min_distance = distance;
				nearest_constraint = const_cast<Constraint*>(&constraint);
			}
		}

		return nearest_constraint;
	}

	static void tear_cloth(float mouse_x, float mouse_y,
							const std::vector<Particle>& particles,
							const std::vector<Constraint>& constraints) {
		Constraint* nearest = find_nearest_constraint(mouse_x, mouse_y, constraints);
		if (nearest) nearest->deactivate();
	}
};

#endif // INPUT_HANDLER_H
