#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{


    class WoodMovementComponent : public Component
    {
    public:
        glm::vec3 linearVelocity = {0, 0, 0};  

        static std::string getID() { return "WoodMovement"; }

        void deserialize(const nlohmann::json &data) override;
    };

}