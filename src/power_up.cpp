#include "power_up.h"
#include "main.h"

Power_Up::Power_Up(float x, float y, float z, float vel_x, float vel_z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(vel_x, -1/20.0f, vel_z);
    this->rotation = 0;
    // speed = 1;
    float radius;
    float l;
    int n ;
	int k;

    l = 6.2f;
    radius=2;
    
    this->box.x=this->position.x;
    this->box.y=this->position.y+1.5;
    this->box.z=this->position.z;
    this->box.width=3.0f*radius;
    this->box.height=8.2f;
    this->box.length=3.0f*radius;

    
    //ARROW_NOSE
    n=7;
	GLfloat vertex_buffer_data4b[100];
	k = 0;
    for(int i = 0;i<n;i++)
    {
        vertex_buffer_data4b[k++] = 0.0f;
        vertex_buffer_data4b[k++] = l+(l/3.6f);
        vertex_buffer_data4b[k++] = 0.0f;

        vertex_buffer_data4b[k++] = 0.0f + 2*radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data4b[k++] = l;
        vertex_buffer_data4b[k++] = 0.0f + 2*radius*cos(2*M_PI/n*i+1);

        vertex_buffer_data4b[k++] = 0.0f + 2*radius*sin(2*M_PI/n*(i));
        vertex_buffer_data4b[k++] = l;
        vertex_buffer_data4b[k++] = 0.0f + 2*radius*cos(2*M_PI/n*(i));
    }
    this->object4a = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data4b, color, GL_FILL);
    vertex_buffer_data4b[k++] = 0.0f;
    vertex_buffer_data4b[k++] = l+(l/3.6f);
    vertex_buffer_data4b[k++] = 0.0f;
    color.r-=40;
    color.g-=40;
    color.b-=40;
    this->object4b = create3DObject(GL_LINE_STRIP, k/3, vertex_buffer_data4b, color, GL_FILL);

    //CYLINDER
    l/=4;
	GLfloat vertex_buffer_data1[150];
	k = 0;
    n=7;
    for(int i = 0;i<n;i++)
    {
        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*i);
        vertex_buffer_data1[k++] = l;
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*i);

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data1[k++] = l*(-1);
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*i+1);

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*(i));
        vertex_buffer_data1[k++] = l*(-1);
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*(i));

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*i);
        vertex_buffer_data1[k++] = l;
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*i);

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data1[k++] = l*(-1);
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*i+1);

        vertex_buffer_data1[k++] = 0.0f + radius*sin(2*M_PI/n*(i+1));
        vertex_buffer_data1[k++] = l;
        vertex_buffer_data1[k++] = 0.0f + radius*cos(2*M_PI/n*(i+1));
    }
    color.r-=40;
    color.g-=40;
    color.b-=40;
    this->object2 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data1, color, GL_FILL);

	GLfloat vertex_buffer_data6[100];
	k = 0;
	for(int i = 0;i<n;i++)
	{
		vertex_buffer_data6[k++] = 0.0f;
		vertex_buffer_data6[k++] = (-1)*(l+0.0001f);
		vertex_buffer_data6[k++] = 0.0f;

		vertex_buffer_data6[k++] = 0.0f + radius*sin(2*M_PI/n*i);
		vertex_buffer_data6[k++] = (-1)*(l+0.0001f);
		vertex_buffer_data6[k++] = 0.0f + radius*cos(2*M_PI/n*i);

		vertex_buffer_data6[k++] = 0.0f + radius*sin(2*M_PI/n*(i+1));
		vertex_buffer_data6[k++] = (-1)*(l+0.0001f);
		vertex_buffer_data6[k++] = 0.0f + radius*cos(2*M_PI/n*(i+1));
	}
    this->object2b = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data6, COLOR_JET_GREY, GL_FILL);

	GLfloat vertex_buffer_data2[100];
    k=0;
    for(int i=0;(9*i+8)<63;i++)
    {
        vertex_buffer_data2[k++]=vertex_buffer_data4b[ 9*i + 3 ];
        vertex_buffer_data2[k++]=vertex_buffer_data4b[ 9*i + 4 ];
        vertex_buffer_data2[k++]=vertex_buffer_data4b[ 9*i + 5 ];

        vertex_buffer_data2[k++]=vertex_buffer_data6[ 9*i + 3 ];
        vertex_buffer_data2[k++]=vertex_buffer_data6[ 9*i + 4 ]*(-1);
        vertex_buffer_data2[k++]=vertex_buffer_data6[ 9*i + 5 ];

        vertex_buffer_data2[k++]=vertex_buffer_data4b[ 9*i + 6 ];
        vertex_buffer_data2[k++]=vertex_buffer_data4b[ 9*i + 7 ];
        vertex_buffer_data2[k++]=vertex_buffer_data4b[ 9*i + 8 ];

        vertex_buffer_data2[k++]=vertex_buffer_data6[ 9*i + 6 ];
        vertex_buffer_data2[k++]=vertex_buffer_data6[ 9*i + 7 ]*(-1);
        vertex_buffer_data2[k++]=vertex_buffer_data6[ 9*i + 8 ];
    }
    vertex_buffer_data2[k++]=vertex_buffer_data4b[ 3 ];
    vertex_buffer_data2[k++]=vertex_buffer_data4b[ 4 ];
    vertex_buffer_data2[k++]=vertex_buffer_data4b[ 5 ];
    this->object3a = create3DObject(GL_LINE_STRIP, k/3, vertex_buffer_data2, COLOR_JET_GREY, GL_FILL);
}

void Power_Up::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object3a);
    draw3DObject(this->object2b);
    draw3DObject(this->object4a);
    draw3DObject(this->object4b);
}

void Power_Up::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->box.x=this->position.x;
    this->box.y=this->position.y+1.5;
    this->box.z=this->position.z;
}

void Power_Up::tick() {
    this->motion();
    this->box.x=this->position.x;
    this->box.y=this->position.y+1.5;
    this->box.z=this->position.z;
}

void Power_Up::motion()
{
    this->position += this->velocity;
}

