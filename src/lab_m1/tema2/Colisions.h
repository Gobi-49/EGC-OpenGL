#pragma once
#include "utils\math_utils.h"
#include <glm/vec2.hpp>

bool proj_Build_Col(float center1X, float center1Y, float latX1, float latZ1, float center2X, float center2Y, float latX2, float latZ2);
float tank_Build_Col_Distance(float center1X, float center1Z, float latX1, float latZ1, float center2X, float center2Z);
float tank_tank_Col_Distance(float center1X, float center1Z, float center2X, float center2Z);
bool trajectoryCol(glm::vec2 l1, glm::vec2 l2, glm::vec2 squareTopLeft, glm::vec2 squareBottomRight);
