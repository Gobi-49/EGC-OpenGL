#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


class MyCamera
{
public:
    MyCamera()
    {
        position = glm::vec3(0, 2, 5);
        forward = glm::vec3(0, 0, -1);
        up = glm::vec3(0, 1, 0);
        right = glm::vec3(1, 0, 0);
        distanceToTarget = 2;
    }

    MyCamera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
    {
        Set(position, center, up);
    }

    ~MyCamera()
    { }

    // Update MyCamera
    void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
    {
        this->position = position;
        forward = glm::normalize(center - position);
        right = glm::cross(forward, up);
        this->up = glm::cross(right, forward);
    }

    void MoveForward(float distance, float rot)
    {
        // Translates the MyCamera using the `dir` vector computed from
        // `forward`. Movement will always keep the MyCamera at the same
        // height. For example, if you rotate your head up/down, and then
        // walk forward, then you will still keep the same relative
        // distance (height) to the ground!

        glm::vec3 dir = glm::vec3(-sin(RADIANS(rot)), 0, -cos(RADIANS(rot)));
        position += dir * distance;
    }

    void MoveBack(float distance, float rot)
    {
        // Translates the MyCamera using the `dir` vector computed from
        // `forward`. Movement will always keep the MyCamera at the same
        // height. For example, if you rotate your head up/down, and then
        // walk forward, then you will still keep the same relative
        // distance (height) to the ground!
        glm::vec3 dir = glm::vec3(-sin(RADIANS(rot)), 0, -cos(RADIANS(rot)));
        position -= dir * distance;
    }

    void RotateFirstPerson_OX(float angle)
    {
        // TODO(student): Compute the new `forward` and `up` vectors.
        // Don't forget to normalize the vectors! Use `glm::rotate()`.
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, right);
        forward = glm::normalize(glm::vec3(rotation * glm::vec4(forward, 0)));
        up = glm::cross(right, forward);
        up = glm::normalize(up);
    }

    void RotateFirstPerson_OY(float angle)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
        forward = glm::normalize(rotation * glm::vec4(forward, 0));
        right = glm::normalize(rotation * glm::vec4(right, 0));

        up = glm::cross(right, forward);
        up = glm::normalize(up);
    }

    void RotateFirstPerson_OZ(float angle)
    {
        // TODO(student): Compute the new `right` and `up`. This time,
        // `forward` stays the same. Use `glm::rotate()`. Don't forget
        // to normalize the vectors!
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, forward);
        right = glm::normalize(glm::vec3(rotation * glm::vec4(right, 0)));
        up = glm::cross(right, forward);
        up = glm::normalize(up);
    }

    void RotateThirdPerson_OX(float angle)
    {
        // TODO(student): Rotate the MyCamera in third-person mode around
        // the OX axis. Use `distanceToTarget` as translation distance.
        position = distanceToTarget * forward;
        RotateFirstPerson_OX(angle);
        position = -distanceToTarget * forward;
    }

    void RotateThirdPerson_OY(float angle)
    {
        // TODO(student): Rotate the MyCamera in third-person mode around
        // the OY axis.
        
        position += distanceToTarget * forward;
        
        RotateFirstPerson_OY(angle);
        
        position -= distanceToTarget * forward;
    }

    void RotateThirdPerson_OZ(float angle)
    {
        // TODO(student): Rotate the MyCamera in third-person mode around
        // the OZ axis.
        position = distanceToTarget * right;
        RotateFirstPerson_OZ(angle);
        position = -distanceToTarget * right;
    }

    glm::mat4 GetViewMatrix()
    {
        // Returns the view matrix
        return glm::lookAt(position, position + forward, up);
    }

    glm::vec3 GetTargetPosition()
    {
        return position + forward * distanceToTarget;
    }

public:
    float distanceToTarget;
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
};
