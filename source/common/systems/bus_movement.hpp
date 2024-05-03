#pragma once

#include "../ecs/world.hpp"
#include "../components/bus_movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/components/movement.hpp"
    class BusMovementSystem
    {
    public:
        // This should be called every frame to update all entities containing a BusMovementComponent.
        void update(World *world, float deltaTime)
        {
            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // Get the movement component if it exists
                BusMovementComponent *bus = entity->getComponent<BusMovementComponent>();
                // If the movement component exists
                if (bus)
                {

                    entity->localTransform.position += deltaTime * bus->linearVelocity;
                    if (entity->localTransform.position.x > 12 && bus->linearVelocity.x > 0)
                    {
                        entity->localTransform.position.x = -12;
                    }
                    else if (entity->localTransform.position.x < -12 && bus->linearVelocity.x < 0)
                    {
                        entity->localTransform.position.x = 12;
                    }
                }
            }
        }
    };

}
