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

#include <vector>
#include <unordered_map>
#include <iostream>

namespace our
{
    static Entity *frogCamera;
    static Entity *frog;
    static int heartsLeft = 2;
    static Entity *heart1;
    static Entity *heart2;
    static Entity *heart3;
    static Entity *wallL;
    static Entity *wallR;
    static Entity *frontWall1;
    static Entity *frontWall2;
    static Entity *frontWallExtend2;

    std::unordered_map<float, std::vector<Entity *>> woods;
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
                }
                else if (entity->name == "heart1")
                {
                    heart1 = entity;
                }
                else if (entity->name == "heart2")
                {
                    heart2 = entity;
                }
                else if (entity->name == "heart3")
                {
                    heart3 = entity;
                }
                else if (entity->name.find("tunnelL") == 0)
                {
                    wallL = entity;
                }
                else if (entity->name.find("tunnelR") == 0)
                {
                    wallR = entity;
                }
                else if (entity->name == "frontWall1")
                {
                    frontWall1 = entity;
                }
                else if (entity->name == "frontWall2")
                {
                    frontWall2 = entity;
                }
                else if (entity->name == "frontWallExtend2")
                {
                    frontWallExtend2 = entity;
                }
                else
                {
                    WoodMovementComponent *wood = entity->getComponent<WoodMovementComponent>();
                    if (wood)
                    {
                        Entity *woodEntity = wood->getOwner();
                        woods[woodEntity->localTransform.position.z].push_back(woodEntity);
                    }
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
            frog->localTransform.position.y = -2.5;
            glm::vec2 wallRPositon = glm::vec2(wallR->localTransform.position.x, wallR->localTransform.position.z);
            glm::vec2 wallLPositon = glm::vec2(wallL->localTransform.position.x, wallL->localTransform.position.z);
            // Walls Check
            if (frogPosition.x < wallLPositon.x + 0.58)
            {
                // std::cout << "Left Wall Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << wallLPositon.x << " Cy = " << wallLPositon.y << std::endl;
                frogCamera->localTransform.position.x = wallLPositon.x + 0.58;
            }

            if (frogPosition.x > wallRPositon.x - 0.58)
            {
                // std::cout << "Right Wall Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << wallRPositon.x << " Cy = " << wallRPositon.y << std::endl;
                frogCamera->localTransform.position.x = wallRPositon.x - 0.58;
            }
            if (frogPosition.y < frontWall2->localTransform.position.z + 0.5 && frogPosition.x > frontWall2->localTransform.position.x - 3 && frogPosition.x < frontWall2->localTransform.position.x + 4.9)
            {

                frogCamera->localTransform.position.z = frontWall2->localTransform.position.z + 4.5;

                // std::cout << "Front Wall Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << frontWall2->localTransform.position.x << " Cy = " << frontWall2->localTransform.position.z << std::endl;
                return;
            }
            if (frogPosition.y < frontWall1->localTransform.position.z + 0.5 && frogPosition.x > frontWall1->localTransform.position.x - 5 && frogPosition.x < frontWall1->localTransform.position.x + 3)
            {

                frogCamera->localTransform.position.z = frontWall2->localTransform.position.z + 4.5;

                // std::cout << "Front Wall Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << frontWall2->localTransform.position.x << " Cy = " << frontWall2->localTransform.position.z << std::endl;
                return;
            }
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
                            // std::cout << "Car Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << carPositon.x << " Cy = " << carPositon.y << std::endl;
                            heartsLeft--;
                            // Add Some Warning ??
                            frogCamera->localTransform.position = glm::vec3(0.5, 2.5, 4);
                            frog->localTransform.rotation = glm::vec3(-0.5f * glm::pi<float>(), 0, 0);
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
                                // std::cout << "Bus Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << busPositon.x << " Cy = " << busPositon.y << std::endl;

                                heartsLeft--;
                                // Add Some Warning ??
                                frogCamera->localTransform.position = glm::vec3(0.5, 2.5, 4);
                                frog->localTransform.rotation = glm::vec3(-0.5f * glm::pi<float>(), 0, 0);
                            }
                        }
                    }
                }
            }
            for (auto wood : woods)
            {
                if (wood.first - 0.8 < frogPosition.y && frogPosition.y < wood.first + 0.5)
                {
                    // in water zoneee
                    bool onWood = false;

                    for (auto woodEntity : wood.second)
                    {
                        glm::vec2 woodPosition = glm::vec2(woodEntity->localTransform.position.x, woodEntity->localTransform.position.z);
                        if (woodPosition.x + 0.5 < frogPosition.x && frogPosition.x < woodPosition.x + 3.5)
                        {
                            // std::cout << "Wood Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << woodPosition.x << " Cy = " << woodPosition.y << std::endl;
                            frog->localTransform.position.y = -2.1;
                            frogCamera->localTransform.position += deltaTime * woodEntity->getComponent<WoodMovementComponent>()->linearVelocity;
                            onWood = true;
                        }
                    }
                    if (!onWood)
                    {

                        // dropped in water
                        // std::cout << "Water Collision @ position Fx = " << frogPosition.x << " Fy = " << frogPosition.y << " Cx = " << woodPosition.x << " Cy = " << woodPosition.y << std::endl;

                        heartsLeft--;
                        // Add Some Warning ??
                        frogCamera->localTransform.position = glm::vec3(0.5, 2.5, 4);
                        frog->localTransform.rotation = glm::vec3(-0.5f * glm::pi<float>(), 0, 0);
                    }
                }
            }
            updateHearts(app);
        }
        void updateHearts(Application *app)
        {
            switch (heartsLeft)
            {
            case 1:
                heart3->localTransform.scale = glm::vec3(0, 0, 0);
                break;
            case 0:
                heart2->localTransform.scale = glm::vec3(0, 0, 0);
                break;
            default:
                break;
            }
            if (heartsLeft < 0)
            {
                std::cout << "NO HEARTS LEFT!" << std::endl;
                heartsLeft = 2;
                app->changeState("game-over");
            }
        }
    };
}
