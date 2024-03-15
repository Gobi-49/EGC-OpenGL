#include "Colisions.h"

bool proj_Build_Col(float center1X, float center1Z, float latX1, float latZ1, float center2X, float center2Z, float latX2, float latZ2)
{
    float x1_left = center1X - latX1 / 2;
    float z1_bottom = center1Z + latZ1 / 2;
    float z1_top = center1Z - latZ1 / 2;
    float x1_right = center1X + latX1 / 2;

    float x2_left = center2X - latX2 / 2;
    float z2_bottom = center2Z + latZ2 / 2;
    float z2_top = center2Z - latZ2 / 2;
    float x2_right = center2X + latX2 / 2;

    return x1_left <= x2_right &&
        x1_right >= x2_left &&
        z1_bottom >= z2_top &&
        z1_top <= z2_bottom;
}

float tank_Build_Col_Distance(float center1X, float center1Z, float latX1, float latZ1, float center2X, float center2Z)
{
    float x = MAX(center1X - latX1 / 2, MIN(center2X, center1X + latX1 / 2));
    float z = MAX(center1Z - latZ1 / 2, MIN(center2Z, center1Z + latZ1 / 2));

    float distance = sqrt(
        (x - center2X) * (x - center2X) +
        (z - center2Z) * (z - center2Z)
    );

    return distance;
}

float tank_tank_Col_Distance(float center1X, float center1Z, float center2X, float center2Z)
{
    float distance = sqrt(
        (center1X - center2X) * (center1X - center2X) +
        (center1Z - center2Z) * (center1Z - center2Z)
    );

    return distance;
}

bool trajectoryCol(glm::vec2 l1, glm::vec2 l2, glm::vec2 rectTopLeft, glm::vec2 rectBottomRight)
{
    // Check if the line is completely to the left or right of the rectangle
    if (l1.x < rectTopLeft.x && l2.x < rectTopLeft.x)
        return false;
    if (l1.x > rectBottomRight.x && l2.x > rectBottomRight.x)
        return false;

    // Check if the line is completely above or below the rectangle
    if (l1.y < rectTopLeft.y && l2.y < rectTopLeft.y)
        return false;
    if (l1.y > rectBottomRight.y && l2.y > rectBottomRight.y)
        return false;

    // Check if the line intersects with any of the rectangle's sides
    // Using the line equation (y - y1) = m(x - x1)
    double m = (l2.y - l1.y) / (l2.x - l1.x);

    // Check left side
    double yLeft = m * (rectTopLeft.x - l1.x) + l1.y;
    if (yLeft >= rectTopLeft.y && yLeft <= rectBottomRight.y)
        return true;

    // Check right side
    double yRight = m * (rectBottomRight.x - l1.x) + l1.y;
    if (yRight >= rectTopLeft.y && yRight <= rectBottomRight.y)
        return true;

    // Check top side
    double xTop = (rectTopLeft.y - l1.y) / m + l1.x;
    if (xTop >= rectTopLeft.x && xTop <= rectBottomRight.x)
        return true;

    // Check bottom side
    double xBottom = (rectBottomRight.y - l1.y) / m + l1.x;
    if (xBottom >= rectTopLeft.x && xBottom <= rectBottomRight.x)
        return true;

    return false;
}
