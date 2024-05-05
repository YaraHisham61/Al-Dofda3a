#pragma once

#include "../ecs/component.hpp"
#include <glm/glm.hpp>

namespace our
{

    class lightingComponent : public Component
    {

    public:
        int Typed=0;
        glm::vec3 color = {1, 0.9, 0.7};// same as diffussion
        glm::vec3 position =  {0, 0, 0 };
        glm::vec3 direction =  {0, 0, 0 };
        glm::vec3 specular =  {1, 0.9, 0.7 };
        glm::vec2 cone_angles =  {0.0f, 0.0f };
        glm::vec3 attenuation =  {0.0f, 0.0f, 0.0f };

        static std::string getID() { return "lighting"; }
        void deserialize(const nlohmann::json &data) override;
    };
}