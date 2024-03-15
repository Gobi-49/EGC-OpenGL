#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace m1;


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    // camera setup
    {
        camera = new MyCamera();
        camera->Set(glm::vec3(0, 1.0f, 1.8f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        fov = RADIANS(60);
        projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);
    }

    //bloc
    {
        Mesh* mesh = new Mesh("bloc");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Tank
    {
        {
            Mesh* mesh = new Mesh("senila");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "Senila.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }

        {
            Mesh* mesh = new Mesh("corp");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "Corp.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }

        {
            Mesh* mesh = new Mesh("turela");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "TurelaV2.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }

        {
            Mesh* mesh = new Mesh("tun");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "TunV2.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }

        {
            Mesh* mesh = new Mesh("proiectil");
            mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "ProiectilV2.obj");
            meshes[mesh->GetMeshID()] = mesh;
        }
    }

    //teren
    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program
    {
        Shader* shader = new Shader("ShaderTema");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Light & material properties
    {
        lightPosition = glm::vec3(0, 1, 1);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }

    // player 
    {
        p = PlayerT2(3);
    }

    // generate random
    {
        random_device r;
        mt19937 gen(r());
        // Buildings
        {
            uniform_real_distribution<float> disPos(-10.0f, 10.0f);
            uniform_real_distribution<float> disRot(0.0f, 360.0f);
            uniform_real_distribution<float> disScale(0.0f, 1.5f);
            uniform_real_distribution<float> disScaleY(0.0f, 4.0f);
            nrBuildings = 3 + rand() % 10;
            for (int i = 0; i < nrBuildings; i++)
            {
                bool ok = true;
                float x = disPos(gen);
                float z = disPos(gen);
                if ((x < 2 && x > -2) || (z < 2 && z > -2))
                {
                    i--;
                    ok = false;
                }
                float rot = 0;//disRot(gen);
                float scaleX = 1 + disScale(gen);
                float scaleY = 1 + disScaleY(gen);
                float scaleZ = 1 + disScale(gen);
                if (ok)
                {
                    buildings.push_back(Building(x, scaleY / 2, z, rot, glm::vec3(scaleX, scaleY, scaleZ)));
                }
            }
            buildings.push_back(Building(0, 0, -12.2f, 0, glm::vec3(24.5f, 1, 0.2f)));
            buildings.push_back(Building(0, 0, 12.2f, 0, glm::vec3(24.5f, 1, 0.2f)));
            buildings.push_back(Building(-12.2f, 0, 0, 0, glm::vec3(0.3f, 1, 24.5f)));
            buildings.push_back(Building(12.2f, 0, 0, 0, glm::vec3(0.3f, 1, 24.5f)));
        }
        // Enemys
        {
            nrEnemys = 4 + rand() % 5;
            uniform_real_distribution<float> disPos(-10.0f, 10.0f);
            for (int i = 0; i < nrEnemys; i++)
            {
                bool ok = true;
                float x = disPos(gen);
                float z = disPos(gen);
                if ((x < 2 && x > -2) || (z < 2 && z > -2))
                {
                    i--;
                    ok = false;
                }
                for (vector<Building>::iterator j = buildings.begin(); j != buildings.end() && ok; j++)
                {
                    float P = tank_Build_Col_Distance((*j).getX(), (*j).getZ(), (*j).getScale().x, (*j).getScale().z, x, z);
                    if (P < tankRadius)
                    {
                        ok = false;
                        i--;
                    }
                }
                for (vector<Enemy>::iterator j = enemys.begin(); j != enemys.end() && ok; j++)
                {
                    float P = tank_tank_Col_Distance((*j).getTank()->getX(), (*j).getTank()->getZ(), x, z);
                    if (P < 2 * tankRadius)
                    {
                        ok = false;
                        i--;
                    }
                }
                if (ok)
                {
                    enemys.push_back(Enemy(3));
                    enemys.back().getTank()->setX(x);
                    enemys.back().getTank()->setZ(z);
                }
            }
        }
    }

    //lightPos
    {
        lightPosition = glm::vec3(0, 1, 0);
    }
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.52f, 0.8f, 0.92f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    gameTime -= deltaTimeSeconds;
    if (p.getTank()->getHealth() <= 0 || gameTime < 0)
    {
        if (p.getTank()->getHealth() <= 0)
        {
            printf("YOU DIED\n");
        }
        if (gameTime < 0)
        {
            printf("TIME'S UP!\n");
        }
        printf("SCORE: %d\n", p.getScore());
        std::this_thread::sleep_for(std::chrono::seconds(1));
        exit(EXIT_SUCCESS);
    }
    
    // Render player tank
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(p.getTank()->getX(), 0, p.getTank()->getZ()));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(p.getTank()->getRot()), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
        
        RenderSimpleMesh(meshes["senila"], shaders["ShaderTema"], modelMatrix, glm::vec3(0.41, 0.41, 0.41));
        RenderSimpleMesh(meshes["corp"], shaders["ShaderTema"], modelMatrix, glm::vec3(0, 0.39, 0), p.getTank()->getHealth());

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(p.getTank()->getX() + offsetZ * sin(RADIANS(p.getTank()->getRot())), offsetY, p.getTank()->getZ() + offsetZ * cos(RADIANS(p.getTank()->getRot()))));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(p.getTank()->getCanonRot()), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
        RenderSimpleMesh(meshes["turela"], shaders["ShaderTema"], modelMatrix, glm::vec3(0, 1, 0), p.getTank()->getHealth());
        RenderSimpleMesh(meshes["tun"], shaders["ShaderTema"], modelMatrix, glm::vec3(0.41, 0.41, 0.41));
    }

    // Render projectiles
    {
        int projectileSpeed = 10;
        for (vector<Projectile>::iterator i = projectiles.begin(); i != projectiles.end();)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3((*i).getX(), (*i).getY(), (*i).getZ()));
            modelMatrix = glm::rotate(modelMatrix, RADIANS((*i).getRot()), glm::vec3(0, 1, 0));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(270), glm::vec3(1, 0, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(scale/2));
            RenderSimpleMesh(meshes["proiectil"], shaders["ShaderTema"], modelMatrix, glm::vec3(0.2));
            (*i).move(projectileSpeed, deltaTimeSeconds);
            bool ok = true;
            for (vector<Building>::iterator j = buildings.begin(); j != buildings.end() && ok; j++)
            {
                if (proj_Build_Col((*i).getX(), (*i).getZ(), projectileLat, projectileLat, (*j).getX(), (*j).getZ(), (*j).getScale().x, (*j).getScale().z))
                {
                    i = projectiles.erase(i);
                    ok = false;
                    break;
                }
            }
            for (vector<Enemy>::iterator j = enemys.begin(); j != enemys.end() && ok; j++)
            {
                float P = tank_Build_Col_Distance((*i).getX(), (*i).getZ(), projectileLat, projectileLat, (*j).getTank()->getX(), (*j).getTank()->getZ());
                if (P < tankRadius - 0.2)
                {
                    if (!(*j).getTank()->damage())
                    {
                        (*j).setState(-1);
                        p.incrementScore();
                    }
                    i = projectiles.erase(i);
                    ok = false;
                    break;
                }
            }

            //player colision
            if(ok)
            {
                float P = tank_Build_Col_Distance((*i).getX(), (*i).getZ(), projectileLat, projectileLat, p.getTank()->getX(), p.getTank()->getZ());
                if (P < tankRadius - 0.2)
                {
                    p.getTank()->damage();
                    i = projectiles.erase(i);
                    ok = false;
                }
            }
            if (ok)
                i++;
        }
    }
    
    // Render ground
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.25f, 0.5f));
        RenderSimpleMesh(meshes["plane"], shaders["ShaderTema"], modelMatrix, glm::vec3(0.46f, 0.33f, 0.16f));
    }

    //Render buildings
    {
        for (vector<Building>::iterator i = buildings.begin(); i != buildings.end();)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3((*i).getX(), (*i).getY(), (*i).getZ()));
            
            modelMatrix = glm::rotate(modelMatrix, RADIANS((*i).getRot()), glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, (*i).getScale());
            RenderSimpleMesh(meshes["bloc"], shaders["ShaderTema"], modelMatrix, glm::vec3(0.41f));
            
            // player tank-building collision
            float P = tank_Build_Col_Distance((*i).getX(), (*i).getZ(), (*i).getScale().x, (*i).getScale().z, p.getTank()->getX(), p.getTank()->getZ());
            if ( P < tankRadius)
            {   
                float x = MAX((*i).getX() - (*i).getScale().x / 2, MIN(p.getTank()->getX(), (*i).getX() + (*i).getScale().x / 2));
                float z = MAX((*i).getZ() - (*i).getScale().z / 2, MIN(p.getTank()->getZ(), (*i).getZ() + (*i).getScale().z / 2));
                glm::vec2 Dif = glm::vec2(x, z) - glm::vec2(p.getTank()->getX(), p.getTank()->getZ());
                glm::vec2 Move = P * glm::normalize(Dif);
                p.getTank()->setX(p.getTank()->getX() - Move.x / 2);
                p.getTank()->setZ(p.getTank()->getZ() - Move.y / 2);
                camera->Set(glm::vec3(p.getTank()->getX(), 1, p.getTank()->getZ() + 1.8f), glm::vec3(p.getTank()->getX(), 0, p.getTank()->getZ()), glm::vec3(0, 1, 0));
                camera->RotateThirdPerson_OY(RADIANS(p.getTank()->getCanonRot()));
            }
            i++;
        }
    }

    // Render enemys
    {
        for (vector<Enemy>::iterator i = enemys.begin(); i != enemys.end(); i++)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3((*i).getTank()->getX(), 0, (*i).getTank()->getZ()));
            modelMatrix = glm::rotate(modelMatrix, RADIANS((*i).getTank()->getRot()), glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));

            RenderSimpleMesh(meshes["senila"], shaders["ShaderTema"], modelMatrix, glm::vec3(0.41, 0.41, 0.41));
            RenderSimpleMesh(meshes["corp"], shaders["ShaderTema"], modelMatrix, glm::vec3(0.5, 0, 0), (*i).getTank()->getHealth());

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3((*i).getTank()->getX() + offsetZ * sin(RADIANS((*i).getTank()->getRot())), offsetY, (*i).getTank()->getZ() + offsetZ * cos(RADIANS((*i).getTank()->getRot()))));
            modelMatrix = glm::rotate(modelMatrix, RADIANS((*i).getTank()->getCanonRot()), glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
            RenderSimpleMesh(meshes["turela"], shaders["ShaderTema"], modelMatrix, glm::vec3(1, 0, 0), (*i).getTank()->getHealth());
            RenderSimpleMesh(meshes["tun"], shaders["ShaderTema"], modelMatrix, glm::vec3(0.41, 0.41, 0.41));

            // player tank - enemy tank collisions
            {
                float P = tank_tank_Col_Distance((*i).getTank()->getX(), (*i).getTank()->getZ(), p.getTank()->getX(), p.getTank()->getZ());
                if (P < 2 * tankRadius)
                {
                    glm::vec2 Dif = glm::vec2((*i).getTank()->getX(), (*i).getTank()->getZ()) - glm::vec2(p.getTank()->getX(), p.getTank()->getZ());
                    glm::vec2 Move = P * glm::normalize(Dif);
                    p.getTank()->setX(p.getTank()->getX() - Move.x / 2);
                    p.getTank()->setZ(p.getTank()->getZ() - Move.y / 2);
                    if ((*i).getState() != -1)
                    {
                        (*i).getTank()->setX((*i).getTank()->getX() + Move.x / 2);
                        (*i).getTank()->setZ((*i).getTank()->getZ() + Move.y / 2);
                    }
                    camera->Set(glm::vec3(p.getTank()->getX(), 1, p.getTank()->getZ() + 1.8f), glm::vec3(p.getTank()->getX(), 0, p.getTank()->getZ()), glm::vec3(0, 1, 0));
                    camera->RotateThirdPerson_OY(RADIANS(p.getTank()->getCanonRot()));
                }
            }

            // enemy tank - enemy tank collisions
            {
                for (vector<Enemy>::iterator j = enemys.begin(); j != enemys.end(); j++)
                {
                    if (i != j)
                    {
                        float P = tank_tank_Col_Distance((*i).getTank()->getX(), (*i).getTank()->getZ(), (*j).getTank()->getX(), (*j).getTank()->getZ());
                        if (P < 2 * tankRadius)
                        {
                            glm::vec2 Dif = glm::vec2((*i).getTank()->getX(), (*i).getTank()->getZ()) - glm::vec2((*j).getTank()->getX(), (*j).getTank()->getZ());
                            glm::vec2 Move = P * glm::normalize(Dif);
                            (*j).getTank()->setX((*j).getTank()->getX() - Move.x / 2);
                            (*j).getTank()->setZ((*j).getTank()->getZ() - Move.y / 2);
                            if ((*i).getState() != -1)
                            {
                                (*i).getTank()->setX((*i).getTank()->getX() + Move.x / 2);
                                (*i).getTank()->setZ((*i).getTank()->getZ() + Move.y / 2);
                            }
                        }
                    }
                }
            }

            // enemy tank - building collision
            for (vector<Building>::iterator j = buildings.begin(); j != buildings.end(); j++)
            {
                float P = tank_Build_Col_Distance((*j).getX(), (*j).getZ(), (*j).getScale().x, (*j).getScale().z, (*i).getTank()->getX(), (*i).getTank()->getZ());
                if (P < tankRadius)
                {
                    float x = MAX((*j).getX() - (*j).getScale().x / 2, MIN((*i).getTank()->getX(), (*j).getX() + (*j).getScale().x / 2));
                    float z = MAX((*j).getZ() - (*j).getScale().z / 2, MIN((*i).getTank()->getZ(), (*j).getZ() + (*j).getScale().z / 2));
                    glm::vec2 Dif = glm::vec2(x, z) - glm::vec2((*i).getTank()->getX(), (*i).getTank()->getZ());
                    glm::vec2 Move = P * glm::normalize(Dif);
                    (*i).getTank()->setX((*i).getTank()->getX() - Move.x / 2);
                    (*i).getTank()->setZ((*i).getTank()->getZ() - Move.y / 2);
                }
            }

            // Fire at Player
            if((*i).getState() != -1){
                (*i).decrementCooldown(deltaTimeSeconds);
                if ((*i).makeCanon(p.getTank()->getX(), p.getTank()->getZ(), deltaTimeSeconds) && (*i).getCooldown() <= 0)
                {
                    projectiles.push_back(Projectile((*i).getTank()->getX() - 0.63 * sin(RADIANS((*i).getTank()->getCanonRot())) + offsetZ * sin(RADIANS((*i).getTank()->getRot())),
                        offsetY, (*i).getTank()->getZ() + offsetZ * cos(RADIANS((*i).getTank()->getRot())) - 0.63 * cos(RADIANS((*i).getTank()->getCanonRot())), (*i).getTank()->getCanonRot()));
                    (*i).setCooldown(1 + rand() % 3);
                }
            }

            if ((*i).getState() == 0) {
                random_device r;
                mt19937 gen(r());
                uniform_real_distribution<float> disPos(-10.0f, 10.0f);
                float x = disPos(gen);
                float z = disPos(gen);
                bool ok = true;
                for (vector<Building>::iterator j = buildings.begin(); j != buildings.end(); j++) {
                    if (trajectoryCol(glm::vec2((*i).getTank()->getX(), (*i).getTank()->getX()), glm::vec2(x, z), 
                        glm::vec2((*j).getX() - (*j).getScale().x / 2, (*j).getZ() + (*j).getScale().z / 2),
                        glm::vec2((*j).getX() + (*j).getScale().x / 2, (*j).getZ() - (*j).getScale().z / 2)))
                    {
                        ok = false;
                        break;
                    }
                }
                if (ok)
                {
                    (*i).setDest(x, z);
                    (*i).setState(1);
                }
            }

            if ((*i).getState() == 1) {
                (*i).makeMove(deltaTimeSeconds);
            }
        }
    }
}


void Tema2::FrameEnd()
{
    //DrawCoordinateSystem();
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, int hp)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    glm::vec3 eyePosition = camera->GetTargetPosition();// GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_loc = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(eye_loc, 1, glm::value_ptr(eyePosition));

    int objcol_loc = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(objcol_loc, 1, glm::value_ptr(color));

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 viewMatrix = camera->GetViewMatrix(); //GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    //glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int loc_hp = glGetUniformLocation(shader->program, "hp");
    glUniform1i(loc_hp, hp);

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float speedWS = 3;// 1.5f;
    float speedAD = 30;//15;
    
    {
        if (window->KeyHold(GLFW_KEY_W))
        {
            p.getTank()->moveForward(speedWS, deltaTime);
            camera->MoveForward(speedWS * deltaTime, p.getTank()->getRot());
        }
        if (window->KeyHold(GLFW_KEY_A))
        {
            p.getTank()->moveLeft(speedAD, deltaTime);
            camera->RotateThirdPerson_OY(RADIANS(speedAD * deltaTime));
        }
        if (window->KeyHold(GLFW_KEY_S))
        {
            p.getTank()->moveBackward(speedWS, deltaTime);
            camera->MoveBack(speedWS * deltaTime, p.getTank()->getRot());
        }
        if (window->KeyHold(GLFW_KEY_D))
        {
            p.getTank()->moveRight(speedAD, deltaTime);
            camera->RotateThirdPerson_OY(-RADIANS(speedAD * deltaTime));
        }

        ///backup rotation
        if (window->KeyHold(GLFW_KEY_LEFT))
        {
            p.getTank()->rotateLeft(speedAD, deltaTime);
            camera->RotateThirdPerson_OY(RADIANS(speedAD * deltaTime));
        }
        if (window->KeyHold(GLFW_KEY_RIGHT))
        {
            p.getTank()->rotateRight(speedAD, deltaTime);
            camera->RotateThirdPerson_OY(-RADIANS(speedAD * deltaTime));
        }
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_L)
    {
        cout << projectiles.size() << endl;
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_MIDDLE))
    {
        float sensivityOX = 0.001f;
        
        p.getTank()->rotateC((-1) * sensivityOX * deltaX * 60);
        camera->RotateThirdPerson_OY((-1) * deltaX * sensivityOX);
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_2)
    {
        projectiles.push_back(Projectile(p.getTank()->getX() - 0.63 * sin(RADIANS(p.getTank()->getCanonRot())) + offsetZ * sin(RADIANS(p.getTank()->getRot())),
            offsetY, p.getTank()->getZ() + offsetZ * cos(RADIANS(p.getTank()->getRot())) - 0.63 * cos(RADIANS(p.getTank()->getCanonRot())), p.getTank()->getCanonRot()));
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
