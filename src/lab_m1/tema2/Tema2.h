#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "tema_camera.h"
#include "tank.h"
#include "PlayerT2.h"
#include "Projectile.h"
#include "Building.h"
#include "Colisions.h"
#include "Enemy.h"
#include <random>

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1), int hp = 3);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        float offsetZ = 0.14;
        float offsetY = 0.38;
        float scale = 0.02;
        float projectileLat = 0.1;
        float tankRadius = 0.6;

        PlayerT2 p;
        std::vector<Projectile> projectiles;
        int nrBuildings;
        std::vector<Building> buildings;
        int nrEnemys;
        std::vector<Enemy> enemys;

        float gameTime = 150;//10;

    protected:
        MyCamera* camera = new MyCamera(glm::vec3(0, 1.0f, 1.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glm::vec3 cameraPos;
        glm::vec3 cameraTarget;
        glm::vec3 cameraDirection;
        glm::mat4 projectionMatrix;
        float fov;
    };
}   // namespace m1
