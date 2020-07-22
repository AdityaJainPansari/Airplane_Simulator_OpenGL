#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, color_t color);
    
    glm::vec3 position;
    float rotation;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void draw_bore(glm::mat4 VP,glm::vec3 plane_position);
    void draw_arrow(glm::mat4 VP,glm::vec3 plane_position,glm::vec3 forward_in_xz_plane);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1a;
    VAO *object1b;
    VAO *object2;
    VAO *object3;
    VAO *object4a;
    VAO *object4b;
};

#endif // CANNON_H
