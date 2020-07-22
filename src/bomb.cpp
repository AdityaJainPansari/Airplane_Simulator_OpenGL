#include "bomb.h"
#include "main.h"

Bomb::Bomb(glm::vec3 plane_position, glm::vec3 forward_direction, float speed) {
    this->position = plane_position;
    // this->rotation = plane_rotation;
    // this->rotation = glm::rotate((float) (-10 * M_PI / 180.0f), glm::vec3(this->rotation[0][0], this->rotation[0][1], this->rotation[0][2]))*this->rotation;
    // this->speed = 0;
    this->velocity = glm::normalize(-forward_direction)*speed;
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    this->box.z=this->position.z;
    this->box.width =2.0f;
    this->box.height=2.0f;
    this->box.length=2.0f;
    this->acceleration = glm::vec3(0,-1/8.0f,0) ;

    int l = 50;
    int n = 50;
    // COCKPIT
	GLfloat vertex_buffer_data0[4000];
	int k = 0;
    float radius=0.5f;
    for(int j=0;j<l/2;j++)
    {
        for(int i = 0;i<n;i++)
        {
            vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*i)*cos(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*i)*sin(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f + radius*cos(2*M_PI/n*i);
        }
    }

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
            vertex_buffer_data2[i]*=0.28f;
        }
        done = true;
    }
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data2, COLOR_BOMB, GL_FILL);
    color_t color;
    color.r = COLOR_BOMB.r + 50;
    color.g = COLOR_BOMB.g + 50;
    color.b = COLOR_BOMB.b + 50;
    this->object1 = create3DObject(GL_LINE_STRIP, k/3, vertex_buffer_data0, color, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::change_speed(glm::vec3 acceleration)
{
    this->velocity += acceleration;
}

void Bomb::tick() {
    this->motion();
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    this->box.z=this->position.z;
}

void Bomb::motion()
{
    // glm::vec3 velocity_direction = glm::vec3(this->rotation[2][0],this->rotation[2][1],this->rotation[2][2]);
    this->position += this->velocity; //_direction*((-1)*this->speed/glm::length(velocity_direction));
    change_speed(this->acceleration);
}

