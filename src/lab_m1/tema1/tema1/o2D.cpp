#include "o2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* o2D::CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, int priority, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, priority), color),
        VertexFormat(corner + glm::vec3(length, height, priority), color),
        VertexFormat(corner + glm::vec3(0, height, priority), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* o2D::CreateDiamond(const std::string& name, float diagL, float diagH, glm::vec3 color, int priority, bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0,0,priority), color),
        VertexFormat(glm::vec3(-diagL/2, 0, priority), color),
        VertexFormat(glm::vec3(diagL/2, 0, priority), color),
        VertexFormat(glm::vec3(0, diagH/2, priority), color),
        VertexFormat(glm::vec3(0, -diagH/2, priority), color),
        VertexFormat(glm::vec3(diagL, -diagH/4, priority), color),
        VertexFormat(glm::vec3(diagL, diagH/4, priority), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 1, 2, 3,
                                          1, 4, 2,
                                          0, 5, 6};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* o2D::CreateHexagon(const std::string& name, float length, glm::vec3 color1, glm::vec3 color2, int priority, bool fill)
{
    std::vector<VertexFormat> vertices = {VertexFormat(glm::vec3(0,0,priority), color1)};

    for (int i = 0; i < 6; ++i) {
        float angle = 2.0f * 3.1415926f * static_cast<float>(i) / 6;
        float x = length * cos(angle);
        float y = 50.0f * sin(angle);
        vertices.push_back((VertexFormat(glm::vec3(x,y, priority), color1)));
    }
    for (int i = 0; i < 6; ++i) {
        float angle = 2.0f * 3.1415926f * static_cast<float>(i) / 6;
        float x = (length - 10) * cos(angle);
        float y = (length - 10) * sin(angle);
        vertices.push_back((VertexFormat(glm::vec3(x, y, priority + 1), color2)));
    }

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 2, 1, 
                                          0, 3, 2,
                                          0, 4, 3,
                                          0, 5, 4,
                                          0, 6, 5,
                                          0, 1, 6,

                                          0, 2 + 6, 1 + 6,
                                          0, 3 + 6, 2 + 6,
                                          0, 4 + 6, 3 + 6,
                                          0, 5 + 6, 4 + 6,
                                          0, 6 + 6, 5 + 6,
                                          0, 1 + 6, 6 + 6
    };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* o2D::CreateStar(const std::string& name, float length, glm::vec3 color, int priority, bool fill)
{
    std::vector<VertexFormat> vertices;
    int numPoints = 5;
    float outerRadius = length;
    float innerRadius = length / 2;
    for (int i = 0; i <= numPoints * 2; ++i) {
        float angle = 2.0f * 3.1415926f * static_cast<float>(i) / (numPoints * 2);
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        vertices.push_back((VertexFormat(glm::vec3(x, y, priority), color)));
    }


    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 7, 3,
                                          2, 9, 5,
                                          4, 1, 7,
                                          6, 3, 9,
                                          8, 5, 1
    };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }

    square->InitFromData(vertices, indices);
    return square;
}
