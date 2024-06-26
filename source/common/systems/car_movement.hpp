#pragma once

#include "../ecs/world.hpp"
#include "../components/car_movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/components/movement.hpp"
    class CarMovementSystem
    {
    public:
        // This should be called every frame to update all entities containing a CarMovementComponent.
        void update(World *world, float deltaTime)
        {
            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // Get the movement component if it exists
                CarMovementComponent *movement = entity->getComponent<CarMovementComponent>();
                // If the movement component exists
                if (movement)
                {
                    
                    entity->localTransform.position += deltaTime * movement->linearVelocity;
                    if (entity->localTransform.position.x > 12&&movement->linearVelocity.x>0)
                    {
                        entity->localTransform.position.x = -12;
                    }
                    else if(entity->localTransform.position.x < -12 && movement->linearVelocity.x < 0)
                    {
                        entity->localTransform.position.x = 12;
                    }
                }
            }
        }
    };

}
