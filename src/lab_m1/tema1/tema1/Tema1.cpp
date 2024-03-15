#include "Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "o2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// Dimensions
	{
		{
			homeDim.x = 60;
			homeDim.y = 490;
		}
		{
			healthDim.x = 80;
			healthDim.y = 80;
		}
		{
			fieldDim.x = 130;
			fieldDim.y = 130;
		}
		{
			outlineDim.x = 120;
			outlineDim.y = 120;
		}
		{
			turretDim.x = 85;
			turretDim.y = 85;
		}

		starDim = 20;
		enemyDim = 50;
	}

	//GUI
	{
		Mesh* health = o2D::CreateSquare("health", glm::vec3(0, 0, 0), healthDim.x, healthDim.y, glm::vec3(1, 0, 0), 0);
		AddMeshToList(health);

		Mesh* home = o2D::CreateSquare("home", glm::vec3(0, 0, 0), homeDim.x, homeDim.y, glm::vec3(0.7, 0, 0), 0);
		AddMeshToList(home);

		Mesh* field = o2D::CreateSquare("field", glm::vec3(0, 0, 0), fieldDim.x, fieldDim.y, glm::vec3(0, 0.7, 0), 0);
		AddMeshToList(field);

		Mesh* outline = o2D::CreateSquare("outline", glm::vec3(0, 0, 0), outlineDim.x, outlineDim.y, glm::vec3(0, 0, 0), 0, false);
		AddMeshToList(outline);
	}
	// Turrets
	{
		Mesh* orangeTurret = o2D::CreateDiamond("orangeTurret", 50, 100, glm::vec3(1, 0.64, 0), 1);
		AddMeshToList(orangeTurret);

		Mesh* blueTurret = o2D::CreateDiamond("blueTurret", 50, 100, glm::vec3(0, 0, 1), 1);
		AddMeshToList(blueTurret);

		Mesh* yellowTurret = o2D::CreateDiamond("yellowTurret", 50, 100, glm::vec3(1, 1, 0), 1);
		AddMeshToList(yellowTurret);

		Mesh* purpleTurret = o2D::CreateDiamond("purpleTurret", 50, 100, glm::vec3(0.5, 0, 0.5), 1);
		AddMeshToList(purpleTurret);
	}
	//Enemys
	{
		Mesh* purpleHexMax = o2D::CreateHexagon("purpleHexMax", enemyDim, glm::vec3(0.5, 0, 0.5), glm::vec3(0, 1, 0), 2);
		AddMeshToList(purpleHexMax);

		Mesh* purpleHexMid = o2D::CreateHexagon("purpleHexMid", enemyDim, glm::vec3(0.5, 0, 0.5), glm::vec3(1, 0.64, 0), 2);
		AddMeshToList(purpleHexMid);

		Mesh* purpleHexMin = o2D::CreateHexagon("purpleHexMin", enemyDim, glm::vec3(0.5, 0, 0.5), glm::vec3(1, 0, 0), 2);
		AddMeshToList(purpleHexMin);

		Mesh* yellowHexMax = o2D::CreateHexagon("yellowHexMax", enemyDim, glm::vec3(1, 1, 0), glm::vec3(0, 1, 0), 2);
		AddMeshToList(yellowHexMax);

		Mesh* yellowHexMid = o2D::CreateHexagon("yellowHexMid", enemyDim, glm::vec3(1, 1, 0), glm::vec3(1, 0.64, 0), 2);
		AddMeshToList(yellowHexMid);

		Mesh* yellowHexMin = o2D::CreateHexagon("yellowHexMin", enemyDim, glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), 2);
		AddMeshToList(yellowHexMin);

		Mesh* orangeHexMax = o2D::CreateHexagon("orangeHexMax", enemyDim, glm::vec3(1, 0.64, 0), glm::vec3(0, 1, 0), 2);
		AddMeshToList(orangeHexMax);

		Mesh* orangeHexMid = o2D::CreateHexagon("orangeHexMid", enemyDim, glm::vec3(1, 0.49, 0.31), glm::vec3(1, 0.64, 0), 2);
		AddMeshToList(orangeHexMid);

		Mesh* orangeHexMin = o2D::CreateHexagon("orangeHexMin", enemyDim, glm::vec3(1, 0.64, 0), glm::vec3(1, 0, 0), 2);
		AddMeshToList(orangeHexMin);

		Mesh* blueHexMax = o2D::CreateHexagon("blueHexMax", enemyDim, glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), 2);
		AddMeshToList(blueHexMax);

		Mesh* blueHexMid = o2D::CreateHexagon("blueHexMid", enemyDim, glm::vec3(0, 0, 1), glm::vec3(1, 0.64, 0), 2);
		AddMeshToList(blueHexMid);

		Mesh* blueHexMin = o2D::CreateHexagon("blueHexMin", enemyDim, glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), 2);
		AddMeshToList(blueHexMin);
	}
	// Stars
	{
		Mesh* price = o2D::CreateStar("price", 20, glm::vec3(1, 0, 0), 0);
		AddMeshToList(price);

		Mesh* fallMoney = o2D::CreateStar("fallMoney", 20, glm::vec3(0, 1, 0), 4);
		AddMeshToList(fallMoney);

		Mesh* orangeProjectile = o2D::CreateStar("orangeProjectile", 20, glm::vec3(1, 0.64, 0), 4);
		AddMeshToList(orangeProjectile);

		Mesh* blueProjectile = o2D::CreateStar("blueProjectile", 20, glm::vec3(0, 0, 1), 4);
		AddMeshToList(blueProjectile);

		Mesh* yellowProjectile = o2D::CreateStar("yellowProjectile", 20, glm::vec3(1, 1, 0), 4);
		AddMeshToList(yellowProjectile);

		Mesh* purpleProjectile = o2D::CreateStar("purpleProjectile", 20, glm::vec3(0.5, 0, 0.5), 4);
		AddMeshToList(purpleProjectile);
	}

	enemySpawnTime = 4 + rand() % 5;
	enemyCurrentTime = 0;
	currencyCurrentTime = 0;
	currencySpawnTime = 3 + rand() % 4;
	shootTime = 3;
	currentShootTime = 0;
	{
		p = player(3, 5, 11);
		selected = 0;
		hold = false;
	}
	mx = 0;
	my = 0;
}


void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
	// draw health bars
	for(int i = 0; i < p.getHealth(); i++)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(900 + i * (60 + homeDim.x), 600);
		RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
	}
	// draw currency
	for (int i = 0; i < p.getMoney(); i++)
	{
		int starDist = 40;
		int starPosX = 900;
		int starPosY = 570;
  
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(starPosX + i * starDist, starPosY);
		modelMatrix *= transform2D::Rotate(2 * 3.14 / 20);
		RenderMesh2D(meshes["price"], shaders["VertexColor"], modelMatrix);
	}
	// draw the 3x3 field
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(150 + j * (30 + fieldDim.x), 30 + i * (50 + fieldDim.y));
			RenderMesh2D(meshes["field"], shaders["VertexColor"], modelMatrix);
		}
	}
	// draw the home
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(60, 30);
		RenderMesh2D(meshes["home"], shaders["VertexColor"], modelMatrix);
	}
	// draw buy menu
	{
		//draw outlines
		for (int i = 0; i < 4; i++)
		{
			int starDist = 40;
			int starPosX = 55;
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(50 + i * (100 + outlineDim.x), 580);
			RenderMesh2D(meshes["outline"], shaders["VertexColor"], modelMatrix);
			// draw turrets
			if (i == 0) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(50 + i * (100 + outlineDim.x) + outlineDim.x/2, 580 + outlineDim.y/2);
				RenderMesh2D(meshes["orangeTurret"], shaders["VertexColor"], modelMatrix);
			}
			if (i == 1) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(50 + i * (100 + outlineDim.x) + outlineDim.x / 2, 580 + outlineDim.y / 2);
				RenderMesh2D(meshes["blueTurret"], shaders["VertexColor"], modelMatrix);
			}
			if (i == 2) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(50 + i * (100 + outlineDim.x) + outlineDim.x / 2, 580 + outlineDim.y / 2);
				RenderMesh2D(meshes["yellowTurret"], shaders["VertexColor"], modelMatrix);
			}
			if (i == 3) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(50 + i * (100 + outlineDim.x) + outlineDim.x / 2, 580 + outlineDim.y / 2);
				RenderMesh2D(meshes["purpleTurret"], shaders["VertexColor"], modelMatrix);
			}
			if(i >= 0)
			{
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(starPosX + i * (100 + outlineDim.x), 550);
				modelMatrix *= transform2D::Rotate(2 * 3.14 / 20);
				RenderMesh2D(meshes["price"], shaders["VertexColor"], modelMatrix);
			}
			if (i >= 1)
			{
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(starPosX + i * (100 + outlineDim.x) +starDist, 550);
				modelMatrix *= transform2D::Rotate(2 * 3.14 / 20);
				RenderMesh2D(meshes["price"], shaders["VertexColor"], modelMatrix);
			}
			if (i == 2)
			{
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(starPosX + (i + 1) * (100 + outlineDim.x) + 2 * starDist, 550);
				modelMatrix *= transform2D::Rotate(2 * 3.14 / 20);
				RenderMesh2D(meshes["price"], shaders["VertexColor"], modelMatrix);
			}
		}        
	}
	// enemys
	{
		if (enemyCurrentTime >= enemySpawnTime)
		{
			int row = rand() % 3;
			enemySpawnTime = 4 + rand() % 5;
			enemyCurrentTime = 0;
			int enemyType = 1 + rand() % 4;
			
			enemys.push_back(entity(1300, 30 + fieldDim.y / 2 + row * (50 + fieldDim.y), -enemyType, 3));
		}

		for (vector<entity>::iterator i = enemys.begin(); i != enemys.end();)
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate((*i).getX(), (*i).getY());
			if ((*i).getX() - enemyDim/2 <= 60)
			{
				kills.push_back(entity((*i).getX(), (*i).getY(), (*i).getType(), 1.0f));
				i = enemys.erase(i);
				if (!p.damage())
				{
					exit(EXIT_SUCCESS);
				}
			}
			else
			{
				for (vector<entity>::iterator j = turrets.begin(); j != turrets.end();)
				{ 
					if (((*i).getX() - enemyDim / 2) - ((*j).getX() + turretDim.x/2) <= 0 && (*j).getY() == (*i).getY() && 
						((*i).getX() + enemyDim / 2) > ((*j).getX() - turretDim.x / 2))
					{
						kills.push_back(entity((*j).getX(), (*j).getY(), (*j).getType(), 1.0f));
						j = turrets.erase(j);
					}
					else
					{
						j++;
					}
				}
				switch ((*i).getType())
				{
				case (-1):
					switch ((*i).getHealth())
					{
					case 3:
						RenderMesh2D(meshes["orangeHexMax"], shaders["VertexColor"], modelMatrix);
						break;
					case 2:
						RenderMesh2D(meshes["orangeHexMid"], shaders["VertexColor"], modelMatrix);
						break;
					case 1:
						RenderMesh2D(meshes["orangeHexMin"], shaders["VertexColor"], modelMatrix);
						break;
					default:
						break;
					}
					break;
				case (-2):
					switch ((*i).getHealth())
					{
					case 3:
						RenderMesh2D(meshes["blueHexMax"], shaders["VertexColor"], modelMatrix);
						break;
					case 2:
						RenderMesh2D(meshes["blueHexMid"], shaders["VertexColor"], modelMatrix);
						break;
					case 1:
						RenderMesh2D(meshes["blueHexMin"], shaders["VertexColor"], modelMatrix);
						break;
					default:
						break;
					}
					break;
				case (-3):
					switch ((*i).getHealth())
					{
					case 3:
						RenderMesh2D(meshes["yellowHexMax"], shaders["VertexColor"], modelMatrix);
						break;
					case 2:
						RenderMesh2D(meshes["yellowHexMid"], shaders["VertexColor"], modelMatrix);
						break;
					case 1:
						RenderMesh2D(meshes["yellowHexMin"], shaders["VertexColor"], modelMatrix);
						break;
					default:
						break;
					}
					break;
				case (-4):
					switch ((*i).getHealth())
					{
					case 3:
						RenderMesh2D(meshes["purpleHexMax"], shaders["VertexColor"], modelMatrix);
						break;
					case 2:
						RenderMesh2D(meshes["purpleHexMid"], shaders["VertexColor"], modelMatrix);
						break;
					case 1:
						RenderMesh2D(meshes["purpleHexMin"], shaders["VertexColor"], modelMatrix);
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				int speed = 100 * deltaTimeSeconds;
				(*i).setX((*i).getX() - speed);
				if ((*i).getHealth() <= 0)
				{
					kills.push_back(entity((*i).getX(), (*i).getY(), (*i).getType(), 1.0f));
					i = enemys.erase(i);
				} 
				else
				{
					i++;
				}
			}
		}
	}
	// money
		if (currencyCurrentTime >= currencySpawnTime)
		{
			currencySpawnTime = 3 + rand() % 4;
			currencyCurrentTime = 0;
			int x = 20 + rand() % (1250);
			int y = 20 + rand() % (560);
			money.push_back(currency(x, 780, x, y));
		}

		for (vector<currency>::iterator i = money.begin(); i != money.end(); i++)
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate((*i).getX(), (*i).getY());
			modelMatrix *= transform2D::Rotate(2 * 3.14 / 20);
			modelMatrix *= transform2D::Scale(1.2, 1.2);
			RenderMesh2D(meshes["fallMoney"], shaders["VertexColor"], modelMatrix);
			int speed = 150 * deltaTimeSeconds;
			if ((*i).getExpectedY() < (*i).getY())
			{
				(*i).setY((*i).getY() - speed);
			}
		}
	// drag and drop
	{
		if (hold)
		{
			if (selected == 1) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(mx, my);
				RenderMesh2D(meshes["orangeTurret"], shaders["VertexColor"], modelMatrix);
			}
			if (selected == 2) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(mx, my);
				RenderMesh2D(meshes["blueTurret"], shaders["VertexColor"], modelMatrix);
			}
			if (selected == 3) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(mx, my);
				RenderMesh2D(meshes["yellowTurret"], shaders["VertexColor"], modelMatrix);
			}
			if (selected == 4) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(mx, my);
				RenderMesh2D(meshes["purpleTurret"], shaders["VertexColor"], modelMatrix);
			}
		}
	}
	//turrets
	{
		bool ok = false;
		for (vector<entity>::iterator i = turrets.begin(); i != turrets.end();)
		{
			
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate((*i).getX(), (*i).getY());
			// draw turret by type
			{
				if ((*i).getType() == 1)
				{
					RenderMesh2D(meshes["orangeTurret"], shaders["VertexColor"], modelMatrix);
				}
				if ((*i).getType() == 2)
				{
					RenderMesh2D(meshes["blueTurret"], shaders["VertexColor"], modelMatrix);
				}
				if ((*i).getType() == 3)
				{
					RenderMesh2D(meshes["yellowTurret"], shaders["VertexColor"], modelMatrix);
				}
				if ((*i).getType() == 4)
				{
					RenderMesh2D(meshes["purpleTurret"], shaders["VertexColor"], modelMatrix);
				}
			}
			if (currentShootTime >= shootTime)
			{
				ok = true;
				for (vector<entity>::iterator j = enemys.begin(); j != enemys.end(); j++)
				{					
					if ((*i).getY() == (*j).getY() && (*i).getX() < (*j).getX() && (*i).getType() == -(*j).getType())
					{
						projectiles.push_back(entity((*i).getX() + 10, (*i).getY(), (*i).getType()));
					}
				}
			}
			i++;
		}
		if(ok)
			currentShootTime = 0;
	}
	// Projectiles
	{
		for (vector<entity>::iterator i = projectiles.begin(); i != projectiles.end();)
		{
			bool ok = false;
			int speed = 150 * deltaTimeSeconds;
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate((*i).getX(), (*i).getY());
			modelMatrix *= transform2D::Rotate( - 2 * (*i).getX() / 3.14);
			modelMatrix *= transform2D::Scale(1.5, 1.5);
			switch ((*i).getType())
			{
			case 1:
				RenderMesh2D(meshes["orangeProjectile"], shaders["VertexColor"], modelMatrix);
				break;
			case 2:
				RenderMesh2D(meshes["blueProjectile"], shaders["VertexColor"], modelMatrix);
				break;
			case 3:
				RenderMesh2D(meshes["yellowProjectile"], shaders["VertexColor"], modelMatrix);
				break;
			case 4:
				RenderMesh2D(meshes["purpleProjectile"], shaders["VertexColor"], modelMatrix);
				break;
			default:
				break;
			}
			for (vector<entity>::iterator j = enemys.begin(); j != enemys.end(); j++)
			{
				if (((*i).getX() + starDim) > ((*j).getX() - enemyDim/2) && 
					((*i).getX() - starDim) < ((*j).getX() + enemyDim / 2) && (*i).getY() == (*j).getY() && (*i).getType() == -(*j).getType())
				{
					ok = true;
					i = projectiles.erase(i);
					(*j).damage();
					break;
				}
			}
			
			if (!ok)
			{
				if ((*i).getX() > 1300)
				{
					i = projectiles.erase(i);
				}
				else
				{
					(*i).setX((*i).getX() + speed);
					i++;
				}
			}
		}
	}
	// Kill animation
	{
		for (vector<entity>::iterator i = kills.begin(); i != kills.end();)
		{
			if ((*i).shrink(deltaTimeSeconds))
			{
				i = kills.erase(i);
			}
			else
			{
				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate((*i).getX(), (*i).getY());
				modelMatrix *= transform2D::Scale((*i).getKillScale(), (*i).getKillScale());
				switch ((*i).getType())
				{
				case 1:
					RenderMesh2D(meshes["orangeTurret"], shaders["VertexColor"], modelMatrix);
					break;
				case 2:
					RenderMesh2D(meshes["blueTurret"], shaders["VertexColor"], modelMatrix);
					break;
				case 3:
					RenderMesh2D(meshes["yellowTurret"], shaders["VertexColor"], modelMatrix);
					break;
				case 4:
					RenderMesh2D(meshes["purpleTurret"], shaders["VertexColor"], modelMatrix);
					break;
				case -1:
					RenderMesh2D(meshes["orangeHexMin"], shaders["VertexColor"], modelMatrix);
					break;
				case -2:
					RenderMesh2D(meshes["blueHexMin"], shaders["VertexColor"], modelMatrix);
					break;
				case -3:
					RenderMesh2D(meshes["yellowHexMin"], shaders["VertexColor"], modelMatrix);
					break;
				case -4:
					RenderMesh2D(meshes["purpleHexMin"], shaders["VertexColor"], modelMatrix);
					break;
				default:
					break;
				}
				
				i++;
			}
		}
	}
	enemyCurrentTime += deltaTimeSeconds;
	currencyCurrentTime += deltaTimeSeconds;	
	currentShootTime += deltaTimeSeconds;
}


void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
	// Add key press event
	if (key == GLFW_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
}


void Tema1::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event

	// drag and drop
	if (hold)
	{
		mx = mouseX + deltaX/2;
		my = (720 - mouseY) + 2*deltaY;
	}
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
	int y = 720 - mouseY;
	if (button == GLFW_MOUSE_BUTTON_2)
	{
		int ok = true;
		for (vector<currency>::iterator i = money.begin(); i != money.end();)
		{
			if ((*i).getX() - starDim <= mouseX && (*i).getX() + starDim >= mouseX &&
				(*i).getY() - starDim <= y && (*i).getY() + starDim >= y)
			{
				ok = false;
				i = money.erase(i);
				p.incrementMoney();
			}
			else
				i++;
		}		
		{
			hold = true;
			if (50 <= mouseX && 50 + outlineDim.x >= mouseX &&
				580 <= y && 580 + outlineDim.y >= y)
			{
				mx = mouseX;
				my = y;
				selected = 1;
			}
			if (50 + (100 + outlineDim.x) <= mouseX && 150 + 2 * outlineDim.x >= mouseX &&
				580 <= y && 580 + outlineDim.y >= y)
			{
				mx = mouseX;
				my = y;
				selected = 2;
			}
			if (50 + 200 + 2 * outlineDim.x <= mouseX && 250 + 3 * outlineDim.x >= mouseX &&
				580 <= y && 580 + outlineDim.y >= y)
			{
				mx = mouseX;
				my = y;
				selected = 3;
			}
			if (50 + 300 + 3 * outlineDim.x <= mouseX && 350 + 4 * outlineDim.x >= mouseX &&
				580 <= y && 580 + outlineDim.y >= y)
			{
				mx = mouseX;
				my = y;
				selected = 4;
			}
		}

		if (ok)
		{
			for (vector<entity>::iterator i = turrets.begin(); i != turrets.end();)
			{
				if ((*i).getX() - turretDim.x <= mouseX && (*i).getX() + turretDim.y >= mouseX &&
					(*i).getY() - turretDim.y <= y && (*i).getY() + turretDim.y >= y)
				{
					kills.push_back(entity((*i).getX(), (*i).getY(), (*i).getType(), 1.0f));
					i = turrets.erase(i);
					p.incrementMoney();
				}
				else
					i++;
			}
		}
	}
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
	int y = 720 - mouseY;
	if(button == GLFW_MOUSE_BUTTON_2)
	{
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (150 + j * (30 + fieldDim.x) <= mouseX && 150 + j * (30 + fieldDim.x) + fieldDim.x >= mouseX &&
						30 + i * (50 + fieldDim.y) <= y && 30 + i * (50 + fieldDim.y) + fieldDim.y >= y)
					{
						bool ok = 1;
						int price = 0;
						// set Price
						{
							if (selected == 1 && p.getMoney() >= 1)
							{
								price = 1;
							}
							if (selected == 2 && p.getMoney() >= 2)
							{
								price = 2;
							}
							if (selected == 3 && p.getMoney() >= 2)
							{
								price = 2;
							}
							if (selected == 4 && p.getMoney() >= 3)
							{
								price = 3;
							}
						}
						float xT = 150 + j * (30 + fieldDim.x) + fieldDim.x / 2;
						float yT = 30 + i * (50 + fieldDim.y) + fieldDim.y / 2;
						for (vector<entity>::iterator i = turrets.begin(); i != turrets.end();i++)
						{
							if ((*i).getX() == xT && (*i).getY() == yT)
							{
								ok = false;
							}
						}
						if (ok && price)
						{
							entity turn(xT, yT, selected);
							turrets.push_back(turn);
							p.buy(price);
						}
					}
				}
			}
		}
		hold = false;
		selected = 0;
		if (hold)
		mx = -200;
		my = -200;

	}
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
