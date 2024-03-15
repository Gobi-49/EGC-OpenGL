#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace o2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, int priority, bool fill = true);

    Mesh* CreateDiamond(const std::string &name, float diagL, float diagH, glm::vec3 color, int priority, bool fill = true);
    
    Mesh* CreateHexagon (const std::string &name, float length, glm::vec3 color1, glm::vec3 color2, int priority, bool fill = true);
    
    Mesh* CreateStar (const std::string &name, float length, glm::vec3 color, int priority, bool fill = true);
}
