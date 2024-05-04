#pragma once

#include "../ecs/world.hpp"
#include "../components/car_movement.hpp"
#include "../components/bus_movement.hpp"
#include "../components/wood_movement.hpp"
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
    static int heartsLeft = 2;
    static Entity *heart1;
    static Entity *heart2;
    static Entity *heart3;
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
                    
                }else if (entity->name=="heart1"){
                    heart1 = entity;
                }else if (entity->name=="heart2"){
                    heart2 = entity;}
                else if (entity->name=="heart3"){
                    heart3 = entity;}
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
            frog->localTransform.position.y = -2.5;

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
                            std::cout << "Car Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << carPositon.x << " Cy = " << carPositon.y << std::endl;
                            switch (heartsLeft)
                            {
                            case 2:
                                heart3->localTransform.scale = glm::vec3(0, 0, 0);
                                break;
                            case 1:
                                heart2->localTransform.scale = glm::vec3(0, 0, 0);
                                break;
                            case 0:
                                heart1->localTransform.scale = glm::vec3(0, 0, 0);
                                break;
                            default:
                                break;
                            }
                            if (heartsLeft <= 0)
                            {
                                std::cout << "NO HEARTS LEFT!" << std::endl;
                                heartsLeft = 2;
                                app->changeState("game-over");
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
                else
                {
                    BusMovementComponent *bus = entity->getComponent<BusMovementComponent>();
                    WoodMovementComponent *wood = entity->getComponent<WoodMovementComponent>();
                    if (bus)
                    {
                        glm::vec2 busPositon = glm::vec2(bus->getOwner()->localTransform.position.x, bus->getOwner()->localTransform.position.z);
                        // std::cout << "We are @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << carPositon.x << " Cy = " << carPositon.y << std::endl;

                        if (busPositon.y - 0.9 < frogPosition.y && frogPosition.y < busPositon.y + 0.55)
                        {
                            if (busPositon.x - 3.5 < frogPosition.x && frogPosition.x < busPositon.x + 3.1)
                            {
                                std::cout << "Bus Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << busPositon.x << " Cy = " << busPositon.y << std::endl;
                                switch (heartsLeft)
                                {
                                case 2:
                                    heart3->localTransform.scale = glm::vec3(0, 0, 0);
                                    break;
                                case 1:
                                    heart2->localTransform.scale = glm::vec3(0, 0, 0);
                                    break;
                                case 0:
                                    heart1->localTransform.scale = glm::vec3(0, 0, 0);
                                    break;
                                default:
                                    break;
                                }
                                if (heartsLeft <= 0)
                                {
                                    std::cout << "NO HEARTS LEFT!" << std::endl;
                                    heartsLeft = 2;
                                    app->changeState("game-over");
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
                    else if (wood)
                    {
                        glm::vec2 WoodPositon = glm::vec2(wood->getOwner()->localTransform.position.x, wood->getOwner()->localTransform.position.z);
                        if (WoodPositon.y - 0.9 < frogPosition.y && frogPosition.y < WoodPositon.y + 0.55)
                        {
                            if (WoodPositon.x + 1 < frogPosition.x && frogPosition.x < WoodPositon.x + 3)
                            {
                                // std::cout << "Wood Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << WoodPositon.x << " Cy = " << WoodPositon.y << std::endl;
                                frog->localTransform.position.y = -2.1;
                                frogCamera->localTransform.position += deltaTime * wood->linearVelocity;
                            }
                            else
                            {
                                // dropped in water
                                // std::cout << "Water Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << WoodPositon.x << " Cy = " << WoodPositon.y << std::endl;

                                // if (heartsLeft <= 0)
                                // {
                                //     std::cout << "NO HEARTS LEFT!" << std::endl;
                                //     heartsLeft = 2;
                                //     // app->changeState("game-over");
                                // }
                                // else
                                // {
                                //     heartsLeft--;
                                //     // Add Some Warning ??
                                //     frogCamera->localTransform.position = glm::vec3(0.5, 2.5, 4);
                                //     frog->localTransform.rotation = glm::vec3(-0.5f * glm::pi<float>(), 0, 0);
                                // }
                            }
                        }
                    }
                }
            }
        }
    };

}
