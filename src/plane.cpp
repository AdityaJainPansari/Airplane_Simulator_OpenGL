#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = glm::mat4(1.0f);
    this->speed = 0;
    this->acceleration = 1/100.0f ;
    this->fuel = 100.0f;
    this->score = 0;
    this->health = 100.0f;
    this->box.x = x;
    this->box.y = y;
    this->box.z = z;
    this->box.width  = 5.0f;
    this->box.height = 1.0f;
    this->box.length = 4.0f;

    int l = 100;
    int n = 100;
    // COCKPIT
	GLfloat vertex_buffer_data0[45000];
	int k = 0;
    float radius=1/4.5;
    for(int j=0;j<l/2;j++)
    {
        for(int i = 0;i<6*n/8;i++)
        {
            vertex_buffer_data0[k++] = 0.0f   + 1.5*radius*sin(2*M_PI/n*i)*cos(2*M_PI/l*j);
            vertex_buffer_data0[k++] = 1/4.5f + 2*radius*sin(2*M_PI/n*i)*sin(2*M_PI/l*j);
            vertex_buffer_data0[k++] = -1.0f  + 2.5*radius*cos(2*M_PI/n*i);
        }
    }
    this->object1 = create3DObject(GL_LINE_STRIP, k/3, vertex_buffer_data0, COLOR_WIND_SHIELD, GL_FILL);

    l = 1.0f;
    //CYLINDER
	GLfloat vertex_buffer_data1[2000];
	k = 0;
    radius=1/3.0;
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
        vertex_buffer_data2[k++] = -0.2f;
        vertex_buffer_data2[k++] = (-1)*l-1.5f;

        vertex_buffer_data2[k++] = 0.0f + radius*sin(2*M_PI/n*i+1);
        vertex_buffer_data2[k++] = 0.0f + radius*cos(2*M_PI/n*i+1);
        vertex_buffer_data2[k++] = (-1)*l;

        vertex_buffer_data2[k++] = 0.0f + radius*sin(2*M_PI/n*(i));
        vertex_buffer_data2[k++] = 0.0f + radius*cos(2*M_PI/n*(i));
        vertex_buffer_data2[k++] = (-1)*l;
    }
    this->object3 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data2, COLOR_JET_NOSE, GL_FILL);

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
    float wing_span = 2.5f;
    static const GLfloat vertex_buffer_data4[] = {

        //right_wing
        wing_span,-0.1f,l-0.4f,
        0.0f     , 0.1f ,l,
        0.0f     , 0.1f ,(-1)*l,

        wing_span,-0.1f,l-0.4f,
        0.0f     , 0.1f ,(-1)*l,
        0.0f     ,-0.1f ,(-1)*l,

        wing_span,-0.1f,l-0.4f,
        0.0f     ,-0.1f,l,
        0.0f     ,-0.1f,(-1)*l,

        //left_wing
        (-1)*wing_span,-0.1f,l-0.4f,
        0.0f          , 0.1f ,l,
        0.0f          , 0.1f ,(-1)*l,

        (-1)*wing_span,-0.1f,l-0.4f,
        0.0f     , 0.1f ,(-1)*l,
        0.0f     ,-0.1f ,(-1)*l,

        (-1)*wing_span,-0.1f,l-0.4f,
        0.0f          , -0.1f ,l,
        0.0f          , -0.1f ,(-1)*l,
        
    };

    this->object5 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data4, COLOR_JET_WING, GL_FILL);


    static const GLfloat vertex_buffer_data5[] = {

        //right_wing
        wing_span,-0.1f,l-0.4f,
        wing_span,-0.1f,l,
        0.0f     , 0.1 ,l,

        wing_span,-0.1f, l,
        0.0f     , 0.1f ,l,
        0.0f     ,-0.1f ,l,

        wing_span,-0.1f,l-0.4f,
        wing_span,-0.1f,l,
        0.0f     ,-0.1f,l,

        //left_wing
        (-1)*wing_span,-0.1f,l-0.4f,
        (-1)*wing_span,-0.1f,l,
        0.0f          , 0.1f ,l,

        (-1)*wing_span,-0.1f,l,
        0.0f     , 0.1f ,    l,
        0.0f     ,-0.1f ,    l,

        (-1)*wing_span,-0.1f,l-0.4f,
        (-1)*wing_span,-0.1f,l,
        0.0f          , -0.1f ,l,
        
    };

    this->object6 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data5, COLOR_JET_NOSE, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate * this->rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    for(int i=0;i<10;i++)
    {
        if(this->is_accelerating || i<5)
            draw3DObject(this->object[i]);
    }
    this->is_accelerating = false;
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object4);
    draw3DObject(this->object7);
}

void Plane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::rotation_Z(float angle)
{
    glm::mat4 rotate_Z = glm::rotate((float) (angle * M_PI / 180.0f), glm::vec3(this->rotation[2][0],this->rotation[2][1],this->rotation[2][2]));
    this->rotation = rotate_Z*this->rotation;
}

void Plane::rotation_Y(float angle)
{
    glm::mat4 rotate_Y = glm::rotate((float) (angle * M_PI / 180.0f), glm::vec3(this->rotation[1][0],this->rotation[1][1],this->rotation[1][2]));
    this->rotation = rotate_Y*this->rotation;
}

void Plane::rotation_X(float angle)
{
    glm::mat4 rotate_X = glm::rotate((float) (angle * M_PI / 180.0f), glm::vec3(this->rotation[0][0],this->rotation[0][1],this->rotation[0][2]));
    this->rotation = rotate_X*this->rotation;
}

void Plane::change_speed(float acceleration)
{
    if(this->speed > 0 || acceleration > 0)
        this->speed += acceleration;
}

void Plane::tick() {
    this->motion();
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    this->box.z=this->position.z;
}

void Plane::motion()
{
    glm::vec3 velocity_direction = glm::vec3(this->rotation[2][0],this->rotation[2][1],this->rotation[2][2]);
    this->position += velocity_direction*((-1)*this->speed/glm::length(velocity_direction));
    if(this->speed > 0)
        this->change_speed((-1/100.0)*this->speed*this->speed);
    else if(this->speed < 0)
        this->change_speed((10/1.0)*this->speed*this->speed);
}

