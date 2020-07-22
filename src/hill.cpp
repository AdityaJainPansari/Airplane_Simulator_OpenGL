#include "hill.h"
#include "main.h"

Hill::Hill(float x, float y, float z, float radius, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->box.x=this->position.x;
    this->box.y=this->position.y+1.5*radius;
    this->box.z=this->position.z;
    this->box.width =3.5*radius;
    this->box.height=3.5*radius;
    this->box.length=3.5*radius;

    int l = 50;
    int n = 50;
	GLfloat vertex_buffer_data0[46000];
	int k = 0;
    for(int j=0;j<l/2;j++)
    {
        for(int i = 0;i<n/2;i++)
        {
            vertex_buffer_data0[k++] = 0.0f   + 1.5*radius*sin(2*M_PI/n*i)*cos(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f + 3*radius*sin(2*M_PI/n*i)*sin(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f  + 1.5*radius*cos(2*M_PI/n*i);

            vertex_buffer_data0[k++] = 0.0f   + 1.5*radius*sin(2*M_PI/n*i+1)*cos(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f + 3*radius*sin(2*M_PI/n*i+1)*sin(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f  + 1.5*radius*cos(2*M_PI/n*i+1);

            vertex_buffer_data0[k++] = 0.0f   + 1.5*radius*sin(2*M_PI/n*i)*cos(2*M_PI/l*j+1);
            vertex_buffer_data0[k++] = 0.0f + 3*radius*sin(2*M_PI/n*i)*sin(2*M_PI/l*j+1);
            vertex_buffer_data0[k++] = 0.0f  + 1.5*radius*cos(2*M_PI/n*i);

            //

            vertex_buffer_data0[k++] = 0.0f   + 1.5*radius*sin(2*M_PI/n*i+1)*cos(2*M_PI/l*j+1);
            vertex_buffer_data0[k++] = 0.0f + 3*radius*sin(2*M_PI/n*i+1)*sin(2*M_PI/l*j+1);
            vertex_buffer_data0[k++] = 0.0f  + 1.5*radius*cos(2*M_PI/n*i+1);

            vertex_buffer_data0[k++] = 0.0f   + 1.5*radius*sin(2*M_PI/n*i+1)*cos(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f + 3*radius*sin(2*M_PI/n*i+1)*sin(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 0.0f  + 1.5*radius*cos(2*M_PI/n*i+1);

            vertex_buffer_data0[k++] = 0.0f   + 1.5*radius*sin(2*M_PI/n*i)*cos(2*M_PI/l*j+1);
            vertex_buffer_data0[k++] = 0.0f + 3*radius*sin(2*M_PI/n*i)*sin(2*M_PI/l*j+1);
            vertex_buffer_data0[k++] = 0.0f  + 1.5*radius*cos(2*M_PI/n*i);
        }
    }

    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data0, COLOR_FIRE, GL_FILL);

    int ind=0;
    for(float r=radius*(1.6);ind<5;r+=0.15*radius)
    {
        GLfloat vertex_buffer_data6[500];
        k = 0;
        for(int i = 0;i<n;i++)
        {
            vertex_buffer_data6[k++] = 0.0f;
            vertex_buffer_data6[k++] = (5-ind)*0.05f;
            vertex_buffer_data6[k++] = 0.0f;

            vertex_buffer_data6[k++] = 0.0f + r*sin(2*M_PI/n*i);
            vertex_buffer_data6[k++] = (5-ind)*0.05f;
            vertex_buffer_data6[k++] = 0.0f + r*cos(2*M_PI/n*i);

            vertex_buffer_data6[k++] = 0.0f + r*sin(2*M_PI/n*(i+1));
            vertex_buffer_data6[k++] = (5-ind)*0.05f;
            vertex_buffer_data6[k++] = 0.0f + r*cos(2*M_PI/n*(i+1));
        }
        this->object1[ind++] = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data6, arr_of_colors[(5-ind)%5], GL_FILL);
    }
}

void Hill::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    for(int i=0;i<5;i++)
    {
        draw3DObject(this->object1[i]);
    }
}

void Hill::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Hill::tick()
{
    ;
}
