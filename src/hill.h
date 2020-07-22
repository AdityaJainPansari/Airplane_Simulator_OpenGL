#include "main.h"

#ifndef HILL_H
#define HILL_H


class Hill {
public:
    Hill() {}
    Hill(float x, float y, float z, float radius, color_t color);
    glm::vec3 position;
    float rotation;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1[5];
};

#endif // HILL_H
