#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our
{

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const
    {
        // TODO: (Req 3) Write this function
        glm::mat4 R = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
        // forming the rotation matrix using Euler angles.
        glm::mat4 T=glm::translate(glm::mat4(1.0f),position);
        // formating the transloation in to 4x4 matrix(the translation will be in the last col).
        glm::mat4 S=glm::scale(glm::mat4(1.0f),scale);
        // adding the scalling values to the diagonal of idedity matrix 4x4 
        glm::mat4 TRS=T*R*S;
        // multipying the the transformation matrix to get the final 4x4 transformation matrix 
        // in the order of the multipication with the vector of the point

        return TRS;
    }

    // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json &data)
    {
        position = data.value("position", position);
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));
        scale = data.value("scale", scale);
    }

}