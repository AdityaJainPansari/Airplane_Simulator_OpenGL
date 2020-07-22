#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(glm::vec3 plane_position, glm::vec3 forward_direction,float speed);
    glm::vec3 position;
    glm::mat4 rotation;
    glm::vec3 acceleration;
    glm::vec3 velocity;
    // float speed;
    bool is_accelerating;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void change_speed(glm::vec3 acceleration);
    void set_position(float x, float y, float z);
    void tick();
    void motion();
private:
    VAO *object1;
    VAO *object2;
};

#endif // BOMB_H
