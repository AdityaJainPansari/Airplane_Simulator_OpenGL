#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

#include "digit.h"

class Segmentdisplay
{
public:
    Segmentdisplay();
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void add(float d = 2);

private:
    float score, digslen;
    Digit digs[50];
};

#endif // SCORE_H
