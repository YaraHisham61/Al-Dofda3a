#pragma once

#include "../ecs/world.hpp"
#include "../components/car_movement.hpp"
#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#include <iostream>

namespace our
{
    static Entity *frogCamera;
    static Entity *frog;
    static int heartsLeft = 3;

    // The Collision system is responsible for detecting collision of frog with every car which contains a CarMovementComponent.
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
                    frog = entity;
                    frogCamera = entity->parent;
                    break;
                }
            }
            if (frogCamera == nullptr)
            {
                std::cerr << "Frog not found in collision system" << std::endl;
            }
        }
        // This should be called every frame to update all entities containing a MovementComponent.
        void update(World *world, float deltaTime, Application *app)
        {
            // initial position.z of camera is  4 so we store the camera (position.z-4) to get the abs. positiion
            glm::vec2 frogPosition = glm::vec2(frogCamera->localTransform.position.x, frogCamera->localTransform.position.z - 4);
            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // Get the car component if it exists
                CarMovementComponent *car = entity->getComponent<CarMovementComponent>();

                // If the car component exists
                if (car)
                {
                    glm::vec2 carPositon = glm::vec2(car->getOwner()->localTransform.position.x, car->getOwner()->localTransform.position.z);
                    // std::cout << "We are @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << carPositon.x << " Cy = " << carPositon.y << std::endl;

                    if (carPositon.y - 0.9 < frogPosition.y && frogPosition.y < carPositon.y + 0.55)
                    {
                        if (carPositon.x - 1.6 < frogPosition.x && frogPosition.x < carPositon.x + 1.3)
                        {
                            std::cout << "Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << carPositon.x << " Cy = " << carPositon.y << std::endl;
                            if (!heartsLeft)
                            {
                                std::cout << "NO HEARTS LEFT!" << std::endl;
                                app->changeState("menu");
                            }
                            else
                            {
                                heartsLeft--;
                                // Add Some Warning ??
                                frogCamera->localTransform.position = glm::vec3(0.5, 2.5, 4);
                                frog->localTransform.rotation = glm::vec3(-0.5f * glm::pi<float>(), 0, 0);
                            }
                        }
                    }
                }
            }
        }
    };

}
