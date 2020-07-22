#include "segmentdisplay.h"
#include "main.h"
#include <cstring>

Segmentdisplay::Segmentdisplay()
{
    score = 0;
    digslen = 0;
    position.x = 0;
    position.y = 3.5;
}

void Segmentdisplay::add(float d) {
    // update(score+d);
    this->score = score+d;
    char scorestr[50];
    sprintf(scorestr, "%d", int(score));
    digslen = strlen(scorestr);
    for (int i = digslen - 1; i >= 0; i--) {
        digs[i] = Digit(scorestr[i], 4 - 0.3*(digslen - i) + position.x, position.y);
    }
}

void Segmentdisplay::draw(glm::mat4 VP) {
    for (int i = 0; i < digslen; i++) digs[i].draw(VP);
}