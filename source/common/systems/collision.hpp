#pragma once

#include "../ecs/world.hpp"
#include "../components/car_movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#include <vector>
#include <iostream>

namespace our
{
    static Entity *frog;

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/components/movement.hpp"
    class CollisionSystem
    {

    public:
        void getFrogEntity(World *world)
        {
            for (auto entity : world->getEntities())
            {

                if (entity->name == "frog")
                {
                    // std::cout << "Found Frog @ " << entity->parent->localTransform.position.x << std::endl;
                    frog = entity->parent;
                    break;
                }
            }
        }
        // This should be called every frame to update all entities containing a MovementComponent.
        void update(World *world, float deltaTime)
        {
            // std::vector<Entity *> movingCars;
            std::vector<float> movingCarsPositions;
            glm::vec2 frogPosition = glm::vec2(frog->localTransform.position.x, frog->localTransform.position.z-4);
            // For each entity in the world
            for (auto entity : world->getEntities())
            {

                // Get the movement component if it exists
                CarMovementComponent *car = entity->getComponent<CarMovementComponent>();

                // If the movement component exists
                if (car)
                {
                    glm::vec2 carPositon = glm::vec2(car->getOwner()->localTransform.position.x, car->getOwner()->localTransform.position.z);
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    // std::cout << "We are @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << carPositon.x << " Cy = " << carPositon.y << std::endl;
                    if (carPositon.y - 0.5 < frogPosition.y && frogPosition.y < carPositon.y + 1)
                    {
                        if (carPositon.x - 2 < frogPosition.x && frogPosition.x < carPositon.x + 1.3)
                        {
                            std::cout << "Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << carPositon.x << " Cy = " << carPositon.y << std::endl;
                            world->clear(); // Should be replaced with a game over screen ??
                        }
                    }
                    // std::cout << "car found with postion " << carPositon << std::endl;
                }
            }
        }
    };

}
