#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;



    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(square3);

    // initiate location
    x1 = 150; y1 = 250;
    x2 = 400; y2 = 250;
    x3 = 650; y3 = 250;

    ok = 0;
    vr = 0;
    vs = 0;
    ok1 = 0;

    rot = 0;
    x1 = 600;
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{

    /*modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x1, y1);

    float v = 200 * deltaTimeSeconds;
    {
        if (ok == 0) {
            modelMatrix = transform2D::Translate(0, v) * modelMatrix;
            y1 += v;
            if (y1 >= 620) {
                ok = 1;
            }
        }
        else 
        {
            modelMatrix = transform2D::Translate(0, -v) * modelMatrix;
            y1 += -v;
            if (y1<=0) {
                ok = 0;
            }
        }
    }

    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    vr += 2 * 3.14 / 8 * deltaTimeSeconds;
    modelMatrix *= transform2D::Translate(x2, y2) * transform2D::Rotate(-vr) * transform2D::Translate(-cx,-cy);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    if (ok1==0) {
        vs += 0.5 * deltaTimeSeconds;
        modelMatrix *= transform2D::Translate(x3, y3) * transform2D::Scale(vs, vs) * transform2D::Translate(-cx, -cy);
        if (vs >= 2)
            ok1 = 1;
    } 
    else
    {
        vs -= 0.5 * deltaTimeSeconds;
        modelMatrix *= transform2D::Translate(x3, y3) * transform2D::Scale(vs, vs) * transform2D::Translate(-cx, -cy);
        if (vs <= 0)
            ok1 = 0;
    }
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);*/

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(x1, 350);
    modelMatrix *= transform2D::Rotate(RADIANS(rot));
    modelMatrix *= transform2D::Translate(-cx, -cy);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(x1, 350);
    modelMatrix *= transform2D::Rotate(RADIANS(rot * 2));
    modelMatrix *= transform2D::Translate(250, 0);
    modelMatrix *= transform2D::Rotate(RADIANS(rot));
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(x1, 350);
    modelMatrix *= transform2D::Rotate(RADIANS(rot * 2));
    modelMatrix *= transform2D::Translate(250, 0);

    modelMatrix *= transform2D::Rotate(RADIANS(rot * 9));
    modelMatrix *= transform2D::Translate(150, 0);
    modelMatrix *= transform2D::Rotate(RADIANS(rot));
    modelMatrix *= transform2D::Scale(0.2, 0.2);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
    rot += 2;
    if (ok == 0) {
        x1 += 100 * deltaTimeSeconds;
        if (x1 >= 1200) {
            ok = 1;
        }
    }
    else
    {
        x1 -= 100 * deltaTimeSeconds;
        if (x1 <= 50) {
            ok = 0;
        }
    }
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
