#include "fire_ball.h"
#include "main.h"

FireBall::FireBall(glm::vec3 cannon_position, glm::vec3 forward_direction) {
    this->position = cannon_position;
    this->velocity_direction = forward_direction;
    speed = 1;
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    this->box.z=this->position.z;
    this->box.width =2.0f;
    this->box.height=2.0f;
    this->box.length=2.0f;

    int l = 100;
    int n = 100;
    // COCKPIT
	GLfloat vertex_buffer_data0[16000];
	int k = 0;
    float radius=1.0f;
    for(int j=0;j<l/2;j++)
    {
        for(int i = 0;i<n;i++)
        {
            vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*i)*cos(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*i)*sin(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f + radius*cos(2*M_PI/n*i);
        }
    }
    this->object1 = create3DObject(GL_LINE_STRIP, k/3, vertex_buffer_data0, COLOR_FIRE_3, GL_FILL);

    static GLfloat vertex_buffer_data2[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f, 
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    static bool done = false;

    if(!done)
    {
        for(int i=0 ; i<108; i++)
        {
            vertex_buffer_data2[i]*=0.57f;
        }
        done = true;
    }
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data2, COLOR_FIRE, GL_FILL);

}

void FireBall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void FireBall::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void FireBall::tick() {
    this->motion();
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    this->box.z=this->position.z;
}

void FireBall::motion()
{
    this->position += this->velocity_direction*((-1)*this->speed/glm::length(this->velocity_direction));
}

