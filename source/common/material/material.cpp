#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"
#include <iostream>

namespace our
{

    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const
    {
        // TODO: (Req 7) Write this function
        this->pipelineState.setup();
        this->shader->use();
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        if (data.contains("pipelineState"))
        {
            pipelineState.deserialize(data["pipelineState"]);
        }
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint
    void TintedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        Material::setup();
        shader->set("tint", tint);
        // send the value of tint to the shaders that use tint.
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json &data)
    {
        Material::deserialize(data);
        if (!data.is_object())
            return;
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex"
    void TexturedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        TintedMaterial::setup();
        shader->set("alphaThreshold", alphaThreshold);
        shader->set("tex", 0);
        // send the value of alphaThreshold to the shaders that use it.

        glActiveTexture(GL_TEXTURE0);

        if (texture != nullptr)
            // check if the texture is not null before usign it
            this->texture->bind();
        if (sampler != nullptr)
            // check if the samler is not null before usign it
            this->sampler->bind(0);
        // send the value of tint to the shaders that use tint.
    }

    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json &data)
    {
        TintedMaterial::deserialize(data);
        if (!data.is_object())
            return;
        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

    void lightingMaterial::setup() const
    {
        TexturedMaterial::setup();

        if (emission != nullptr)
        {
            glActiveTexture(GL_TEXTURE0);
            this->emission->bind();
            this->sampler->bind(0);
            shader->set("material.emission", emission);
        }
        if (ambient_occlusion != nullptr)
        {
            glActiveTexture(GL_TEXTURE1);
            this->ambient_occlusion->bind();
            this->sampler->bind(1);
            shader->set("material.ambient_occlusion", ambient_occlusion);
        }
        if (specular != nullptr)
        {
            glActiveTexture(GL_TEXTURE2);

            this->specular->bind();
            this->sampler->bind(2);

            shader->set("material.specular", specular);
        }
        if (roughness != nullptr)
        {
            glActiveTexture(GL_TEXTURE3);

            this->roughness->bind();
            this->sampler->bind(3);

            shader->set("material.roughness", roughness);
        }
        if (albedo != nullptr)
        {
            glActiveTexture(GL_TEXTURE4);

            this->albedo->bind();
            this->sampler->bind(4);

            shader->set("material.albedo", albedo);
        }
    }

    // This function read the material data from a json object
    void lightingMaterial::deserialize(const nlohmann::json &data)
    {
        TexturedMaterial::deserialize(data);
        if (!data.is_object())
            return;
        if (!data.is_object())
            return;
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
        albedo = AssetLoader<Texture2D>::get(data.value("albedo", ""));
        specular = AssetLoader<Texture2D>::get(data.value("specular", ""));
        emission = AssetLoader<Texture2D>::get(data.value("emission", ""));
        roughness = AssetLoader<Texture2D>::get(data.value("roughness", ""));
        ambient_occlusion = AssetLoader<Texture2D>::get(data.value("ambient_occlusion", ""));
    }

}