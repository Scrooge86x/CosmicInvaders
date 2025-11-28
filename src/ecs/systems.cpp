#include "systems.h"

void movementSystem(entt::registry& registry) {
	entt::basic_view view = registry.view<Transform, Velocity>();

	for (auto [entity, transform, velocity]: view.each()) {
		transform.position += velocity.linear * velocity.speed;
	}
}