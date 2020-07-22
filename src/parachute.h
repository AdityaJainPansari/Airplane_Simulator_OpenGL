#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, float vel_x, float vel_z, color_t color);
    
    glm::vec3 position;
    glm::vec3 velocity;
    float rotation;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void motion();
    double speed;
private:
    VAO *object2;
    VAO *object2b;
    VAO *object3a;
    VAO *object4a;
    VAO *object4b;
};

#endif // PARACHUTE_H
