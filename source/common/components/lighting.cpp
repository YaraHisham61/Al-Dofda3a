#include "lighting.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our
{
    // Reads sensitivities & speedupFactor from the given json object
    void lightingComponent::deserialize(const nlohmann::json &data)

    {
        if (!data.is_object())
            return;

        Typed = data.value("Typed", 0);
        // if the value of type not existed it assign the variable type to the default 0
        // the function does the same for other parameters

        color =data.value("color", glm::vec3(1, 0.9, 0.7));
        specular =data.value("specular", glm::vec3(1, 0.9, 0.7));
        attenuation = data.value("attenuation", glm::vec3(1, 0, 0));
        direction =data.value("direction", glm::vec3(0, -1, 0));
        position = data.value("position", glm::vec3(0, 0, 0));
        cone_angles.x = glm::radians((float)data.value("cone_angles.inner", 90));
        cone_angles.y = glm::radians((float)data.value("cone_angles.outer", 120));
    }

}