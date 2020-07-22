#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    // this->rotation = 0;
    speed = 1;
    float radius = 5.0f;
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    this->box.z=this->position.z;
    this->box.width =0.8*radius;
    this->box.height=0.8*radius;
    this->box.length=0.4f;

    float l ;
    int n = 50;
	int k ;

    l = 0.8f;
    //CYLINDER
	GLfloat vertex_buffer_data1[2000];
	k = 0;
    // radius=3.0f;
    for(int i = 0;i<n;i++)
    {
        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*i);
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*i);
        vertex_buffer_data1[k++] = l;

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*i+1);
        vertex_buffer_data1[k++] = l*(-1);

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*(i));
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*(i));
        vertex_buffer_data1[k++] = l*(-1);

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*i);
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*i);
        vertex_buffer_data1[k++] = l;

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*i+1);
        vertex_buffer_data1[k++] = l*(-1);

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*(i+1));
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*(i+1));
        vertex_buffer_data1[k++] = l;
    }
    // this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data1, COLOR_FIRE, GL_FILL);

    for(int j=0; j<5; j++)
    {
        for(int i=0;i<k;i++)
        {
            vertex_buffer_data1[i] *= 3.9/4.0;
        }
        this->object1[j] = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data1, arr_of_colors[4-j], GL_FILL);
    }
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate);// * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    for(int i=0;i<5;i++)
    {
        draw3DObject(this->object1[i]);
    }
}

void Ring::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ring::tick()
{
    ;
}
