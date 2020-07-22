#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(float x, float y, float z, color_t color) {
    this->position          = glm::vec3(x, y, z);
    this->compass_pos   = glm::vec3( 0.000,-0.03,0.0);
    this->speed_pos     = glm::vec3(-0.014,-0.03,0.0);
    this->fuel_pos      = glm::vec3( 0.014,-0.03,0.0);
    this->health_pos    = glm::vec3(-0.03,-0.035,0.0);
    this->altitude_pos  = glm::vec3( 0.03,-0.035,0.0);
    // this->health_bar_len= 0.5;
    // this->alt_bar_len   = 0.5;
    speed = 1;
    this->box.x             = this->position.x;
    this->box.y             = this->position.y;
    this->box.z             = this->position.z;
    this->box.width         = 0.60f;
    this->box.height        = 0.60f;
    this->box.length        = 0.60f;
    
    int scale = 100;
    this->compass_pos *= scale;
    this->fuel_pos    *= scale;
    this->speed_pos   *= scale;
    this->health_pos  *= scale;
    this->altitude_pos*= scale;

    this->charac.push_back(Digit( 'C' ,  this->compass_pos.x-0.1 ,  this->compass_pos.y-0.9 ));
    this->charac.push_back(Digit( 'S' ,    this->speed_pos.x-0.1 ,    this->speed_pos.y-0.6 ));
    this->charac.push_back(Digit( 'F' ,     this->fuel_pos.x-0.1 ,     this->fuel_pos.y-0.6 ));
    this->charac.push_back(Digit( 'H' ,   this->health_pos.x-0.1 ,   this->health_pos.y+0.3 ));
    this->charac.push_back(Digit( 'A' , this->altitude_pos.x+0.1 , this->altitude_pos.y-0.1 ));

    static GLfloat vertex_buffer_data[] = {
        -0.1f, -0.025f, 0.0f,
         0.1f, -0.025f, 0.0f,
         0.1f, 0.025f, 0.0f,
         0.1f, 0.025f, 0.0f,
        -0.1f, -0.025f, 0.0f,
        -0.1f, 0.025f, 0.0f,
    };

    // for(int i=0 ; i<12; i++)
    // {
    //     if(i%3 == 0)
    //         vertex_buffer_data[i]*=3; // X-direction or WIDTH
    //     else if(i%3 == 1)
    //     {
    //         vertex_buffer_data[i]*=5; // Y-direction or HEIGHT
    //         vertex_buffer_data[i]-=5; // Y-direction or HEIGHT
    //     }
    //     else if(i%3 == 2)
    //         vertex_buffer_data[i]*=3; // Z-direction or LENGTH
    // }
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);

    //ARROW
    GLfloat vertex_buffer_arrow1[] = {
        -0.003f,  0.00f, 0.0f,
         0.000f,  0.015f, 0.0f,
         0.003f,  0.00f, 0.0f,
    };
    GLfloat vertex_buffer_arrow2[] = {
        -0.003f,  0.00f, 0.0f,
         0.000f, -0.015f, 0.0f,
         0.003f,  0.00f, 0.0f,
    };
	GLfloat vertex_buffer_meter[360];
	int n = 36 ;
    int k = 0;
    float radius = 0.016f ;
	for(int i = -n/4;i<3*n/4;i++)
	{
		vertex_buffer_meter[k++] = 0.0f;
		vertex_buffer_meter[k++] = 0.0f;
		vertex_buffer_meter[k++] = -0.0001f;

		vertex_buffer_meter[k++] = 0.0f + radius*sin(2*M_PI/n*i);
		vertex_buffer_meter[k++] = 0.0f + radius*cos(2*M_PI/n*i);
		vertex_buffer_meter[k++] = -0.0001f;

		vertex_buffer_meter[k++] = 0.0f + radius*sin(2*M_PI/n*(i+1));
		vertex_buffer_meter[k++] = 0.0f + radius*cos(2*M_PI/n*(i+1));
		vertex_buffer_meter[k++] = -0.0001f;
	}
    scale = 40;
    for(int i=0;i<9;i++)
    {
        vertex_buffer_arrow1[i]*=scale;
        vertex_buffer_arrow2[i]*=scale;
    }
    for(int i=0;i<k;i++)
    {
        vertex_buffer_meter[i]*=scale;
    }
    this->semi_meter = create3DObject(GL_LINE_STRIP, (k/6)+1, vertex_buffer_meter, COLOR_BLACK, GL_FILL);
    this->meter = create3DObject(GL_LINE_STRIP, k/3, vertex_buffer_meter, COLOR_BLACK, GL_FILL);
    this->arrow1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_arrow1, COLOR_RED, GL_FILL);
    this->arrow2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_arrow2, COLOR_JET_GREY, GL_FILL);


    //Horizontal BAR
    float bar_len = 0.5f ;
    // GLfloat vertex_buffer_bar_border[] = {
    //     -bar_len-0.0001,-0.000001f, 0.0f,
    //      bar_len+0.0001,-0.000001f, 0.0f,
    //      bar_len+0.0001, 0.015001f, 0.0f,
    //     -bar_len-0.0001, 0.015001f, 0.0f,
    // };
    GLfloat vertex_buffer_bar_border[] = {
        -bar_len-0.05,  0.00f-0.05, -0.01f,
         bar_len+0.05,  0.15f+0.05, -0.01f,
         bar_len+0.05,  0.00f-0.05, -0.01f,
        -bar_len-0.05,  0.00f-0.05, -0.01f,
         bar_len+0.05,  0.15f+0.05, -0.01f,
        -bar_len-0.05,  0.15f+0.05, -0.01f,
    };
    GLfloat vertex_buffer_bar[] = {
        -bar_len,  0.00f, 0.0f,
         bar_len,  0.15f, 0.0f,
         bar_len,  0.00f, 0.0f,
        -bar_len,  0.00f, 0.0f,
         bar_len,  0.15f, 0.0f,
        -bar_len,  0.15f, 0.0f,
    };
    this->bar_border = create3DObject(GL_TRIANGLES, 6, vertex_buffer_bar_border, COLOR_FIRE, GL_FILL);
    this->bar = create3DObject(GL_TRIANGLES, 6, vertex_buffer_bar, COLOR_GREEN, GL_FILL);
}

void Dashboard::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<this->charac.size();i++)
    {
        this->charac[i].draw(VP);
    }
}

void Dashboard::drawCompass(glm::mat4 VP,glm::vec3 plane_forward_direction) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position+this->compass_pos);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->meter);

    Matrices.model = glm::mat4(1.0f);
    float sign = (glm::cross(plane_forward_direction,glm::vec3(0,0,1)).y);
    if(sign>=0) sign = -1;
    else sign = 1;
    float rot_angle = glm::acos(glm::dot(plane_forward_direction,glm::vec3(0,0,1)));
    glm::mat4 rotate    = glm::rotate((float) (rot_angle*sign), glm::vec3(0,0,-1));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->arrow1);
    draw3DObject(this->arrow2);
}

void Dashboard::drawSpeed_meter(glm::mat4 VP,float speed) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position+this->speed_pos);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->semi_meter);
    
    Matrices.model = glm::mat4(1.0f);
    glm::vec3 rel_speed_pos = glm::vec3(0,0,0);
    float rot_angle = (speed*180)-90;
    glm::mat4 rotate    = glm::rotate((float) (rot_angle * M_PI / 180.0f), glm::vec3(0,0,-1));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->arrow1);
    // draw3DObject(this->arrow2);
}

void Dashboard::drawFuel_meter(glm::mat4 VP,float fuel) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position+this->fuel_pos);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->semi_meter);
    
    Matrices.model = glm::mat4(1.0f);
    glm::vec3 rel_fuel_pos = glm::vec3(0,0,0);
    fuel /= 100.0f;
    float rot_angle = (fuel*180)-90;
    glm::mat4 rotate    = glm::rotate((float) (rot_angle * M_PI / 180.0f), glm::vec3(0,0,-1));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->arrow1);
    // draw3DObject(this->arrow2);
}

void Dashboard::drawHealth_bar(glm::mat4 VP,float health) {
    if(health>100) health = 100;
    if(health<0) health = 0;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position+this->health_pos);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->bar_border);

    GLfloat vertex_buffer_bar[] = {
        -0.5,  0.00f, 0.0f,
         health*(0.01)-0.5,  0.15f, 0.0f,
         health*(0.01)-0.5,  0.00f, 0.0f,
        -0.5,  0.00f, 0.0f,
         health*(0.01)-0.5,  0.15f, 0.0f,
        -0.5,  0.15f, 0.0f,
    };
    delete this->bar;
    if(health>33)
        this->bar = create3DObject(GL_TRIANGLES, 6, vertex_buffer_bar, COLOR_GREEN, GL_FILL);
    else
        this->bar = create3DObject(GL_TRIANGLES, 6, vertex_buffer_bar, COLOR_RED, GL_FILL);
    draw3DObject(this->bar);
}

void Dashboard::drawAltitude_bar(glm::mat4 VP,float altitude) {
    // altitude=5;
    if(altitude>100) altitude = 100;
    if(altitude<0) altitude = 0;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 trans_origin = glm::translate(glm::vec3(0,-0.075f,0));
    glm::mat4 trans_back = glm::translate(glm::vec3(-0.2,0.5f,0));
    glm::mat4 translate = glm::translate (this->position+this->altitude_pos);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * trans_back * rotate * trans_origin);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->bar_border);

    GLfloat vertex_buffer_bar[] = {
        -0.5,  0.00f, 0.0f,
        altitude*(0.01)-0.5,  0.15f, 0.0f,
        altitude*(0.01)-0.5,  0.00f, 0.0f,
        -0.5,  0.00f, 0.0f,
        altitude*(0.01)-0.5,  0.15f, 0.0f,
        -0.5,  0.15f, 0.0f,
    };
    delete this->bar;
    if(altitude>20)
        this->bar = create3DObject(GL_TRIANGLES, 6, vertex_buffer_bar, COLOR_GREEN, GL_FILL);
    else
        this->bar = create3DObject(GL_TRIANGLES, 6, vertex_buffer_bar, COLOR_RED, GL_FILL);
    draw3DObject(this->bar);
}

// void Dashboard::set_position(float x, float y, float z) {
//     this->position = glm::vec3(x, y, z);
// }

// void Dashboard::set_rotation(glm::vec3 z_direction, glm::vec3 up)
// {
//     z_direction = glm::normalize(-z_direction);
//     glm::vec3 x_direction = glm::normalize(glm::cross(z_direction,up));
//     glm::vec3 y_direction = glm::normalize(glm::cross(x_direction,z_direction));
//     this->rotation[0][0] = x_direction.x; this->rotation[0][1] = x_direction.y; this->rotation[0][2] = x_direction.z;
//     this->rotation[1][0] = y_direction.x; this->rotation[1][1] = y_direction.y; this->rotation[1][2] = y_direction.z;
//     this->rotation[2][0] = z_direction.x; this->rotation[2][1] = z_direction.y; this->rotation[2][2] = z_direction.z;

//     this->speed_pos = glm::vec3(0,0,0);
//     this->speed_pos += glm::vec3(this->rotation[0][0],this->rotation[0][1],this->rotation[0][2])*(this->rel_speed_pos.x);
//     this->speed_pos += glm::vec3(this->rotation[1][0],this->rotation[1][1],this->rotation[1][2])*(this->rel_speed_pos.y);
//     this->speed_pos += glm::vec3(this->rotation[2][0],this->rotation[2][1],this->rotation[2][2])*(this->rel_speed_pos.z);

//     this->compass_pos = glm::vec3(0,0,0);
//     this->compass_pos += glm::vec3(this->rotation[0][0],this->rotation[0][1],this->rotation[0][2])*(this->rel_compass_pos.x);
//     this->compass_pos += glm::vec3(this->rotation[1][0],this->rotation[1][1],this->rotation[1][2])*(this->rel_compass_pos.y);
//     this->compass_pos += glm::vec3(this->rotation[2][0],this->rotation[2][1],this->rotation[2][2])*(this->rel_compass_pos.z);

//     this->fuel_pos = glm::vec3(0,0,0);
//     this->fuel_pos += glm::vec3(this->rotation[0][0],this->rotation[0][1],this->rotation[0][2])*(this->rel_fuel_pos.x);
//     this->fuel_pos += glm::vec3(this->rotation[1][0],this->rotation[1][1],this->rotation[1][2])*(this->rel_fuel_pos.y);
//     this->fuel_pos += glm::vec3(this->rotation[2][0],this->rotation[2][1],this->rotation[2][2])*(this->rel_fuel_pos.z);

//     this->position -= y_direction*0.075f;
// }

// void Dashboard::tick()
// {
//     ;
// }

