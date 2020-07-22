#include "main.h"

#ifndef FIREBALL_H
#define FIREBALL_H


class FireBall {
public:
    FireBall() {}
    FireBall(glm::vec3 cannon_position, glm::vec3 forward_direction);
    glm::vec3 position;
    glm::vec3 velocity_direction;
    float speed;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void motion();
private:
    VAO *object1;
    VAO *object2;
};

#endif // FIREBALL_H
