#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->box.x=this->position.x;
    this->box.y=this->position.y+1.5;
    this->box.z=this->position.z;
    this->box.width=8.5f;
    this->box.height=3.5f;
    this->box.length=8.5f;

    float l;
    int n = 100;
	int k;
    float radius;

    l = 0.7f;
    //ARROW_CYLINDER
	GLfloat vertex_buffer_data4a[2000];
	k = 0;
    radius=1/5.0;
    for(int i = 0;i<n;i++)
    {
        vertex_buffer_data4a[k++] = 0.0f + radius*sin(2*M_PI/n*i);
        vertex_buffer_data4a[k++] = 0.0f + radius*cos(2*M_PI/n*i);
        vertex_buffer_data4a[k++] = l;

        vertex_buffer_data4a[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data4a[k++] = 0.0f + radius*cos(2*M_PI/n*i+1);
        vertex_buffer_data4a[k++] = l*(-1);

        vertex_buffer_data4a[k++] = 0.0f + radius*sin(2*M_PI/n*(i));
        vertex_buffer_data4a[k++] = 0.0f + radius*cos(2*M_PI/n*(i));
        vertex_buffer_data4a[k++] = l*(-1);

        vertex_buffer_data4a[k++] = 0.0f + radius*sin(2*M_PI/n*i);
        vertex_buffer_data4a[k++] = 0.0f + radius*cos(2*M_PI/n*i);
        vertex_buffer_data4a[k++] = l;

        vertex_buffer_data4a[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data4a[k++] = 0.0f + radius*cos(2*M_PI/n*i+1);
        vertex_buffer_data4a[k++] = l*(-1);

        vertex_buffer_data4a[k++] = 0.0f + radius*sin(2*M_PI/n*(i+1));
        vertex_buffer_data4a[k++] = 0.0f + radius*cos(2*M_PI/n*(i+1));
        vertex_buffer_data4a[k++] = l;
    }
    this->object4a = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data4a, COLOR_RED, GL_FILL);
    
    //ARROW_NOSE
	GLfloat vertex_buffer_data4b[1000];
	k = 0;
    for(int i = 0;i<n;i++)
    {
        vertex_buffer_data4b[k++] = 0.0f;
        vertex_buffer_data4b[k++] = 0.0f;
        vertex_buffer_data4b[k++] = (-1)*l-(l/1.5f);

        vertex_buffer_data4b[k++] = 0.0f + 2*radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data4b[k++] = 0.0f + 2*radius*cos(2*M_PI/n*i+1);
        vertex_buffer_data4b[k++] = (-1)*l;

        vertex_buffer_data4b[k++] = 0.0f + 2*radius*sin(2*M_PI/n*(i));
        vertex_buffer_data4b[k++] = 0.0f + 2*radius*cos(2*M_PI/n*(i));
        vertex_buffer_data4b[k++] = (-1)*l;
    }
    this->object4b = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data4b, COLOR_JET_NOSE, GL_FILL);

    static GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
    };

    static bool loop1 = false;
    if(!loop1)
    {
        for(int i=0 ; i<54; i++)
        {
            if(i%3 == 0)
                vertex_buffer_data[i]*=4; // X-direction or WIDTH
            else if(i%3 == 1)
            {
                vertex_buffer_data[i]*=0.5; // Y-direction or HEIGHT
                vertex_buffer_data[i]+=0.4; // Y-direction or HEIGHT
            }
            else if(i%3 == 2)
                vertex_buffer_data[i]*=4; // Z-direction or LENGTH
        }
        loop1 = true;
    }
    this->object1a = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, COLOR_RED, GL_FILL);

    static GLfloat vertex_buffer_data1[] = {
        1.0f, 1.0f,-1.0f, 
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    }; 

    static bool loop2 = false;
    if(!loop2)
    {
        for(int i=0 ; i<54; i++)
        {
            if(i%3 == 0)
                vertex_buffer_data1[i]*=4; // X-direction or WIDTH
            else if(i%3 == 1)
            {
                vertex_buffer_data1[i]*=0.5; // Y-direction or HEIGHT
                vertex_buffer_data1[i]+=0.4; // Y-direction or HEIGHT
            }
            else if(i%3 == 2)
                vertex_buffer_data1[i]*=4; // Z-direction or LENGTH
        }
        loop2 = true;
    }
    this->object1b = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data1, COLOR_WHITE, GL_FILL);
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

    static bool loop3 = false;
    if(!loop3)
    {
        for(int i=0 ; i<108; i++)
        {
            if(i%3 == 0)
                vertex_buffer_data2[i]*=2; // X-direction or WIDTH
            else if(i%3 == 1)
            {
                vertex_buffer_data2[i]*=1; // Y-direction or HEIGHT
                vertex_buffer_data2[i]+=1.9; // Y-direction or HEIGHT
            }
            else if(i%3 == 2)
                vertex_buffer_data2[i]*=2; // Z-direction or LENGTH
        }
        loop3 = true;
    }
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data2, COLOR_CANNON, GL_FILL);



    l = 10.0f;
    //CYLINDER
	GLfloat vertex_buffer_data0[2000];
	k = 0;
    radius=1.5;
    for(int i = 0;i<n;i++)
    {
        vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*i);
        vertex_buffer_data0[k++] = 3.5f + radius*cos(2*M_PI/n*i);
        vertex_buffer_data0[k++] = l;

        vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data0[k++] = 3.5f + radius*cos(2*M_PI/n*i+1);
        vertex_buffer_data0[k++] = 0;

        vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*(i));
        vertex_buffer_data0[k++] = 3.5f + radius*cos(2*M_PI/n*(i));
        vertex_buffer_data0[k++] = 0;

        vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*i);
        vertex_buffer_data0[k++] = 3.5f + radius*cos(2*M_PI/n*i);
        vertex_buffer_data0[k++] = l;

        vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data0[k++] = 3.5f + radius*cos(2*M_PI/n*i+1);
        vertex_buffer_data0[k++] = 0;

        vertex_buffer_data0[k++] = 0.0f + radius*sin(2*M_PI/n*(i+1));
        vertex_buffer_data0[k++] = 3.5f + radius*cos(2*M_PI/n*(i+1));
        vertex_buffer_data0[k++] = l;
    }
    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data0, COLOR_JET_GREY, GL_FILL);

    GLfloat vertex_buffer_data6[1000];
	k = 0;
	for(int i = 0;i<n;i++)
	{
		vertex_buffer_data6[k++] = 0.0f;
		vertex_buffer_data6[k++] = 3.5f;
		vertex_buffer_data6[k++] = l+0.0001f;

		vertex_buffer_data6[k++] = 0.0f + radius*sin(2*M_PI/n*i);
		vertex_buffer_data6[k++] = 3.5f + radius*cos(2*M_PI/n*i);
		vertex_buffer_data6[k++] = l+0.0001f;

		vertex_buffer_data6[k++] = 0.0f + radius*sin(2*M_PI/n*(i+1));
		vertex_buffer_data6[k++] = 3.5f + radius*cos(2*M_PI/n*(i+1));
		vertex_buffer_data6[k++] = l+0.0001f;
	}
    this->object3 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data6, COLOR_JET_GREY, GL_FILL);

}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    draw3DObject(this->object1a);
    draw3DObject(this->object1b);
    draw3DObject(this->object2);
}

void Cannon::draw_bore(glm::mat4 VP,glm::vec3 plane_position) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate_origin = glm::translate (glm::vec3(0,-4.0,0));    // glTranslatef
    glm::mat4 translate_back = glm::translate (glm::vec3(0,4.0,0));    // glTranslatef
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::mat4(1.0f);
    glm::vec3 bore_z = glm::normalize(plane_position-this->position);
    glm::vec3 bore_x = glm::vec3(0,0,0);
    if(bore_z.x != 0 || bore_z.y != 0)
        bore_x = glm::normalize(glm::cross(bore_z,glm::vec3(bore_z.x,bore_z.y,bore_z.z-1)));
    else
        bore_x = glm::normalize(glm::cross(bore_z,glm::vec3(bore_z.x-1,bore_z.y,bore_z.z)));
    glm::vec3 bore_y = glm::normalize(glm::cross(bore_x,bore_z));
    rotate[0][0] = bore_x.x ;    rotate[0][1] = bore_x.y ;    rotate[0][2] = bore_x.z ;
    rotate[1][0] = bore_y.x ;    rotate[1][1] = bore_y.y ;    rotate[1][2] = bore_y.z ;
    rotate[2][0] = bore_z.x ;    rotate[2][1] = bore_z.y ;    rotate[2][2] = bore_z.z ;
    Matrices.model *= (translate * translate_back * rotate * translate_origin);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object3);
}

void Cannon::draw_arrow(glm::mat4 VP,glm::vec3 plane_position,glm::vec3 forward_in_xz_plane) {
    Matrices.model = glm::mat4(1.0f);
    glm::vec3 arrow_pos = plane_position - forward_in_xz_plane*7.0f + glm::vec3(0,6,0);
    glm::mat4 translate = glm::translate (arrow_pos);    // glTranslatef
    glm::mat4 rotate    = glm::mat4(1.0f);
    glm::vec3 bore_z = glm::normalize(arrow_pos-this->position);
    glm::vec3 bore_x = glm::vec3(0,0,0);
    if(bore_z.x != 0 || bore_z.y != 0)
        bore_x = glm::normalize(glm::cross(bore_z,glm::vec3(bore_z.x,bore_z.y,bore_z.z-1)));
    else
        bore_x = glm::normalize(glm::cross(bore_z,glm::vec3(bore_z.x-1,bore_z.y,bore_z.z)));
    glm::vec3 bore_y = glm::normalize(glm::cross(bore_x,bore_z));
    rotate[0][0] = bore_x.x ;    rotate[0][1] = bore_x.y ;    rotate[0][2] = bore_x.z ;
    rotate[1][0] = bore_y.x ;    rotate[1][1] = bore_y.y ;    rotate[1][2] = bore_y.z ;
    rotate[2][0] = bore_z.x ;    rotate[2][1] = bore_z.y ;    rotate[2][2] = bore_z.z ;

    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object4a);
    draw3DObject(this->object4b);
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->box.x=this->position.x;
    this->box.y=this->position.y+1.5;
    this->box.z=this->position.z;
}

void Cannon::tick()
{
    ;
}

