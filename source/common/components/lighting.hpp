#pragma once

#include "../ecs/component.hpp"
#include "../material/material.hpp"
#include "../asset-loader.hpp"

namespace our
{

    class lightingComponent : public Component
    {

    public:
        int type;
        glm::vec3 color = glm::vec3(0, 0, 0);// same as diffussion
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::vec3 direction = glm::vec3(0, 0, 0);
        glm::vec3 specular = glm::vec3(0, 0, 0);
        glm::vec2 cone_angles = glm::vec2(0.0f, 0.0f);
        glm::vec3 attenuation = glm::vec3(0.0f, 0.0f, 0.0f);

        static std::string getID() { return "lighting"; }
        void deserialize(const nlohmann::json &data) override;
    }
}