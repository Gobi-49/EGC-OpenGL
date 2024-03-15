#pragma once

#include "components/simple_scene.h"
#include "gameObject.h"
#include "entity.h"
#include "currency.h"
#include "player.h"

struct coord
{
    float x;
    float y;
};

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat3 modelMatrix;
        // TODO(student): If you need any other class variables, define them here.
        coord healthDim, fieldDim, homeDim, outlineDim, turretDim;
        float enemySpawnTime, enemyCurrentTime;
        float currencySpawnTime, currencyCurrentTime;
        float shootTime, currentShootTime;
        std::vector<entity> enemys, turrets, projectiles, kills;
        std::vector<currency> money;
        float starDim, enemyDim;
        player p;
        int selected;
        bool hold;
        int mx, my; //mouse position
    };
}   // namespace m1
