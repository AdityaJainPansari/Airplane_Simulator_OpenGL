#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::mat4 rotation;
    float acceleration;
    float speed;
    float fuel;
    float score;
    float health;
    bool is_accelerating;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void rotation_Z(float angle);
    void rotation_Y(float angle);
    void rotation_X(float angle);
    void change_speed(float acceleration);
    void set_position(float x, float y, float z);
    void tick();
    void motion();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object[10];
};

#endif // PLANE_H
