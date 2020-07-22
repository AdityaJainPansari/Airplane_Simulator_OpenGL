#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(glm::vec3 plane_position, glm::mat4 plane_rotation);
    glm::vec3 position;
    glm::mat4 rotation;
    float acceleration;
    float speed;
    bool is_accelerating;
    bounding_box_t box;
    void draw(glm::mat4 VP);
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

#endif // MISSILE_H
