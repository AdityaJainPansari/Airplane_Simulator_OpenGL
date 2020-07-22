#include "missile.h"
#include "main.h"

Missile::Missile(glm::vec3 plane_position, glm::mat4 plane_rotation) {
    this->position = plane_position;
    this->rotation = plane_rotation;
    this->rotation = glm::rotate((float) (-10 * M_PI / 180.0f), glm::vec3(this->rotation[0][0], this->rotation[0][1], this->rotation[0][2]))*this->rotation;
    this->speed = 0;
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    this->box.z=this->position.z;
    this->box.width=1.0f;
    this->box.height=0.30f;
    this->box.length=2.0f;
    this->acceleration = 1/10.0f ;

    float l;
    int n = 100;
	int k;
    float radius;

    l = 0.7f;
    //CYLINDER
	GLfloat vertex_buffer_data1[2000];
	k = 0;
    radius=1/7.0;
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
    this->object2 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data1, COLOR_JET_GREY, GL_FILL);

    //BACK-END JET_COLOR_DISC
	GLfloat vertex_buffer_data6[1000];
	k = 0;
	for(int i = 0;i<n;i++)
	{
		vertex_buffer_data6[k++] = 0.0f;
		vertex_buffer_data6[k++] = 0.0f;
		vertex_buffer_data6[k++] = l+0.0001f;

		vertex_buffer_data6[k++] = 0.0f + radius*sin(2*M_PI/n*i);
		vertex_buffer_data6[k++] = 0.0f + radius*cos(2*M_PI/n*i);
		vertex_buffer_data6[k++] = l+0.0001f;

		vertex_buffer_data6[k++] = 0.0f + radius*sin(2*M_PI/n*(i+1));
		vertex_buffer_data6[k++] = 0.0f + radius*cos(2*M_PI/n*(i+1));
		vertex_buffer_data6[k++] = l+0.0001f;
	}
    this->object4 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data6, COLOR_JET_GREY, GL_FILL);

    //BACK-END FIRE_DISC
	GLfloat vertex_buffer_data7[1000];
	k = 0;
	for(int i = 0;i<n;i++)
	{
		vertex_buffer_data7[k++] = 0.0f;
		vertex_buffer_data7[k++] = 0.0f;
		vertex_buffer_data7[k++] = l+0.0002f;

		vertex_buffer_data7[k++] = 0.0f + radius*sin(2*M_PI/n*i)*(0.8);
		vertex_buffer_data7[k++] = 0.0f + radius*cos(2*M_PI/n*i)*(0.8);
		vertex_buffer_data7[k++] = l+0.0002f;

		vertex_buffer_data7[k++] = 0.0f + radius*sin(2*M_PI/n*(i+1))*(0.8);
		vertex_buffer_data7[k++] = 0.0f + radius*cos(2*M_PI/n*(i+1))*(0.8);
		vertex_buffer_data7[k++] = l+0.0002f;
	}
    this->object7 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data7, COLOR_FIRE_1, GL_FILL);

    n = 100;
    //JET_NOSE
	GLfloat vertex_buffer_data2[1000];
	k = 0;
    for(int i = 0;i<n;i++)
    {
        vertex_buffer_data2[k++] = 0.0f;
        vertex_buffer_data2[k++] = 0.0f;
        vertex_buffer_data2[k++] = (-1)*l-0.4f;

        vertex_buffer_data2[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data2[k++] = 0.0f + radius*cos(2*M_PI/n*i+1);
        vertex_buffer_data2[k++] = (-1)*l;

        vertex_buffer_data2[k++] = 0.0f + radius*sin(2*M_PI/n*(i));
        vertex_buffer_data2[k++] = 0.0f + radius*cos(2*M_PI/n*(i));
        vertex_buffer_data2[k++] = (-1)*l;
    }
    this->object3 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data2, COLOR_JET_NOSE, GL_FILL);

    // l = 1.0f;
    //JET_ENGINE_BACK-END_FIRE
    n = 100;
    int m= 18;
    int ind=0;
    for(float r=radius*(0.1);r<=radius;r+=0.1*radius)
    {
        GLfloat vertex_buffer_data3[8100];
        k = 0;
        for(int j=0;j<m;j++)
        {
            for(int i = 0;i<n/2;i++)
            {
                vertex_buffer_data3[k++] = 0.0f + r*sin(2*M_PI/m*j+1)*(0.7);
                vertex_buffer_data3[k++] = 0.0f + r*cos(2*M_PI/m*j+1)*(0.7);
                vertex_buffer_data3[k++] = l+1.0f*(r/radius);

                vertex_buffer_data3[k++] = 0.0f + r*sin(2*M_PI/m*j+1)*(0.7) + r*sin(2*M_PI/n*i+1)*(0.1);
                vertex_buffer_data3[k++] = 0.0f + r*cos(2*M_PI/m*j+1)*(0.7) + r*cos(2*M_PI/n*i+1)*(0.1);
                vertex_buffer_data3[k++] = l;

                vertex_buffer_data3[k++] = 0.0f + r*sin(2*M_PI/m*j+1)*(0.7) + r*sin(2*M_PI/n*(i))*(0.1);
                vertex_buffer_data3[k++] = 0.0f + r*cos(2*M_PI/m*j+1)*(0.7) + r*cos(2*M_PI/n*(i))*(0.1);
                vertex_buffer_data3[k++] = l;
            }
        }
        this->object[ind++] = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data3, arr_of_colors[((ind-1)/2)%5], GL_FILL);
    }
    
    //WINGS
    l/=3.0;
    float wing_span = 0.5f;
    static const GLfloat vertex_buffer_data4[] = {

        //right_wing
        wing_span,-0.1f,l-0.2f,
        0.0f     , 0.1f ,l,
        0.0f     , 0.1f ,(-1)*l,

        wing_span,-0.1f,l-0.2f,
        0.0f     , 0.1f ,(-1)*l,
        0.0f     ,-0.1f ,(-1)*l,

        wing_span,-0.1f,l-0.2f,
        0.0f     ,-0.1f,l,
        0.0f     ,-0.1f,(-1)*l,

        //left_wing
        (-1)*wing_span,-0.1f,l-0.2f,
        0.0f          , 0.1f ,l,
        0.0f          , 0.1f ,(-1)*l,

        (-1)*wing_span,-0.1f,l-0.2f,
        0.0f     , 0.1f ,(-1)*l,
        0.0f     ,-0.1f ,(-1)*l,

        (-1)*wing_span,-0.1f,l-0.2f,
        0.0f          , -0.1f ,l,
        0.0f          , -0.1f ,(-1)*l,
        
    };

    this->object5 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data4, COLOR_JET_NOSE, GL_FILL);


    static const GLfloat vertex_buffer_data5[] = {

        //right_wing
        wing_span,-0.1f, l-0.2f,
        0.0f     , 0.1f ,l,
        0.0f     ,-0.1f ,l,

        //left_wing
        (-1)*wing_span,-0.1f,l-0.2f,
        0.0f     , 0.1f ,    l,
        0.0f     ,-0.1f ,    l,        
    };

    this->object6 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, COLOR_JET_WING, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate * this->rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    for(int i=0;i<10;i++)
    {
        draw3DObject(this->object[i]);
    }
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object4);
    draw3DObject(this->object7);
}

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Missile::change_speed(float acceleration)
{
    this->speed += acceleration;
}

void Missile::tick() {
    this->motion();
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    this->box.z=this->position.z;
}

void Missile::motion()
{
    glm::vec3 velocity_direction = glm::vec3(this->rotation[2][0],this->rotation[2][1],this->rotation[2][2]);
    this->position += velocity_direction*((-1)*this->speed/glm::length(velocity_direction));
    change_speed(this->acceleration);
}

