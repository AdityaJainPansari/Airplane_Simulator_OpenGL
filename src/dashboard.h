#include "main.h"
#include "digit.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y, float z, color_t color);
    
    glm::vec3 position;
    glm::vec3 rel_compass_pos;
    glm::vec3 compass_pos;
    glm::vec3 rel_fuel_pos;
    glm::vec3 fuel_pos;
    glm::vec3 rel_speed_pos;
    glm::vec3 speed_pos;
    glm::mat4 rotation;
    glm::vec3 health_pos    ;
    glm::vec3 altitude_pos  ;
    std::vector<Digit> charac;
    // float health_bar_len;
    // float alt_bar_len   ;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void drawCompass(glm::mat4 VP,glm::vec3 plane_forward_direction);
    void drawSpeed_meter(glm::mat4 VP,float speed);
    void drawFuel_meter(glm::mat4 VP,float fuel);
    void drawHealth_bar(glm::mat4 VP,float health);
    void drawAltitude_bar(glm::mat4 VP,float altitude);
    void set_position(float x, float y, float z);
    void set_rotation(glm::vec3 z_direction, glm::vec3 up);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *arrow1;
    VAO *arrow2;
    VAO *meter;
    VAO *semi_meter;
    VAO *bar;
    VAO *bar_background;
    VAO *bar_border;
};

#endif // DASHBOARD_H
