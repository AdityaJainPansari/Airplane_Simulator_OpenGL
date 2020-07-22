#include "main.h"
#include "timer.h"
// #include "ball.h"
#include "plane.h"
#include "ground.h"
#include "hill.h"
#include "ring.h"
#include "missile.h"
#include "bomb.h"
#include "cannon.h"
#include "fire_ball.h"
#include "segmentdisplay.h"
#include "parachute.h"
#include "power_up.h"
#include "dashboard.h"
#include <unistd.h>

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices2;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Plane plane;
Ground ground;
Dashboard dashboard;
vector<Hill> hills;
vector<Ring> rings;
vector<Missile> missiles;
vector<Bomb> bombs;
vector<FireBall> fire_balls;
vector<Parachute> parachutes;
vector<Power_Up> health;
vector<Power_Up> fuel;
Cannon cannon;
Segmentdisplay score;
double pre_cam_change = glfwGetTime();
double pre_cannon_fire = glfwGetTime();
double pre_fuel = glfwGetTime();
// double pre_beep = glfwGetTime();
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int camera_choice=0;
double pre_x_pos, pre_y_pos;
double cam_heli_x=0;
double cam_heli_y=0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    glm::vec3 eye2     = glm::vec3(0, 0, 5);
    glm::vec3 target2  = glm::vec3(0,0,-5);
    glm::vec3 up2      = glm::vec3(0, 1, 0);
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    if(camera_choice==0) // Still CAMERA
    {
        eye     = glm::vec3(0, 53, 5);
        target  = glm::vec3(0,48,-5);
        up      = glm::vec3(0, 51, 0);
    }
    else if(camera_choice==1) // Pilot CAMERA
    {
        glm::vec3 y_direction = glm::vec3(plane.rotation[1][0],plane.rotation[1][1],plane.rotation[1][2]);
        y_direction = y_direction*((1/2.7f)/glm::length(y_direction));
        glm::vec3 z_direction = glm::vec3(plane.rotation[2][0],plane.rotation[2][1],plane.rotation[2][2]);
        eye = plane.position+y_direction-z_direction*(1.0f);
        target = plane.position-z_direction*100.0f;
        up = y_direction;
    }
    else if(camera_choice==2) // Top CAMERA
    {
        eye     = plane.position+glm::vec3(0,20,0);
        target  = plane.position;
        glm::vec3 forward_in_xz_plane = glm::vec3(plane.rotation[2][0],0,(-1)*plane.rotation[2][2]);
        up      = forward_in_xz_plane;
    }
    else if(camera_choice==3) // TOWER CAMERA
    {
        glm::vec3 z_direction = glm::vec3(plane.rotation[2][0],plane.rotation[2][1],plane.rotation[2][2]);
        z_direction = z_direction*((20.0f)/glm::length(z_direction));
        eye     = plane.position+glm::vec3(0,20,0)+z_direction;
        target  = plane.position;
        up      = glm::vec3(0, 1, 0);
    }
    else if(camera_choice==4) // FOLLOW CAMERA
    {
        glm::vec3 y_direction = glm::vec3(plane.rotation[1][0],plane.rotation[1][1],plane.rotation[1][2]);
        y_direction = y_direction*(1/glm::length(y_direction));
        glm::vec3 z_direction = glm::vec3(plane.rotation[2][0],plane.rotation[2][1],plane.rotation[2][2]);
        eye = plane.position+y_direction*(3.0f)+z_direction*(5.0f);
        target = plane.position-y_direction*(2.0f)-z_direction*(5.0f);
        up      = glm::vec3(0, 1, 0);
    }
    else if(camera_choice==5) // HELICOPTER CAMERA
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
    
        // if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 

        cam_heli_x += + (xpos - pre_x_pos) * 90 / 600.0;
        cam_heli_y -= + (ypos - pre_y_pos) * 90 / 600.0;
        pre_x_pos = xpos;
        pre_y_pos = ypos;
        target = plane.position;

        // 10 + (20-camera_zoom/5)*cos(camera_look_x*M_PI/180.0f)*sin(camera_look_y*M_PI/180.0f)
        // (20-camera_zoom/5)*cos(camera_look_y*M_PI/180.0f)
        // 10 + (20-camera_zoom/5)*sin(camera_look_x*M_PI/180.0f)*sin(camera_look_y*M_PI/180.0f)
        float eye_x = plane.position.x + (20-10*screen_zoom)*cos(cam_heli_x*M_PI/180.0f)*sin(cam_heli_y*M_PI/180.0f);
        float eye_y = plane.position.y + (20-10*screen_zoom)*cos(cam_heli_y*M_PI/180.0f);
        float eye_z = plane.position.z + (20-10*screen_zoom)*sin(cam_heli_x*M_PI/180.0f)*sin(cam_heli_y*M_PI/180.0f);

        eye = glm::vec3(eye_x,eye_y,eye_z);
        up = glm::vec3(0,1,0);
                                // double pre_x_pos, pre_y_pos;
                                // pre_x_pos=x_pos;
                                // pre_y_pos=y_pos;
                                // //getting cursor position
                                // glfwGetCursorPos(window, &x_pos, &y_pos);
                                // cout << "Cursor Position at (" << x_pos << " : " << y_pos << endl;
                                // // return;

                                // glm::vec3 y_direction = glm::vec3(plane.rotation[1][0],plane.rotation[1][1],plane.rotation[1][2]);
                                // y_direction = y_direction*(1/glm::length(y_direction));
                                // glm::vec3 z_direction = glm::vec3(plane.rotation[2][0],plane.rotation[2][1],plane.rotation[2][2]);
                                // eye = plane.position+y_direction*(3.0f)+z_direction*(5.0f);//glm::vec3(0,3,5);
                                // // eye = plane.position+glm::vec3(0,(3.0f),0)+z_direction*(5.0f);//glm::vec3(0,3,5);
                                // target = plane.position;//-y_direction*(2.0f)-z_direction*(5.0f);//glm::vec3(0,-2,-5);
                                // // glm::vec3 x_direction = glm::vec3(plane.rotation[0][0],plane.rotation[0][1],plane.rotation[0][2]);
                                // // up = y_direction;//glm::vec3(0,1,0);
                                // // eye     = glm::vec3(0, 3, 5);
                                // // target  = glm::vec3(0,-2,-5);
                                // up      = glm::vec3(0, 1, 0);
    }

    // eye = target + (eye-target)*screen_zoom;
    glm::vec3 dashboard_position = eye2+glm::normalize(target2-eye2)*0.10001f;
    // dashboard.set_position(dashboard_position.x, dashboard_position.y, dashboard_position.z);
    // dashboard.set_rotation(eye2-target2,up2);
    
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Matrices2.view = glm::lookAt( eye2, target2, up2 ); // Rotating Camera for 3D
    // Don't change unless you are sure!!

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP2 = Matrices2.projection * Matrices2.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    plane.draw(VP);
    ground.draw(VP);
    glm::vec3 forward_in_xz_plane = glm::normalize(glm::vec3(plane.rotation[2][0],0,plane.rotation[2][2]));
    for(int i=0;i<hills.size();i++)
    {
        hills[i].draw(VP);
    }
    for(int i=0;i<rings.size();i++)
    {
        rings[i].draw(VP);
    }
    for(int i=0;i<missiles.size();i++)
    {
        missiles[i].draw(VP);
    }
    for(int i=0;i<bombs.size();i++)
    {
        bombs[i].draw(VP);
    }
    cannon.draw(VP);
    cannon.draw_bore(VP,plane.position);
    cannon.draw_arrow(VP,plane.position,forward_in_xz_plane);

    for(int i=0; i<fire_balls.size();i++)
    {
        fire_balls[i].draw(VP);
    }

    for(int i=0; i<parachutes.size();i++)
    {
        parachutes[i].draw(VP);
    }

    for(int i=0; i<health.size();i++)
    {
        health[i].draw(VP);
    }

    for(int i=0; i<fuel.size();i++)
    {
        fuel[i].draw(VP);
    }

    dashboard.draw(VP2);
    score.draw(VP2);
    dashboard.drawCompass(VP2,forward_in_xz_plane);
    dashboard.drawSpeed_meter(VP2,plane.speed);
    dashboard.drawFuel_meter(VP2,plane.fuel);
    dashboard.drawHealth_bar(VP2,plane.health);
    dashboard.drawAltitude_bar(VP2,plane.position.y);

    cout << "y : " << plane.position.y << endl;
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int C = glfwGetKey(window, GLFW_KEY_C);
    int W = glfwGetKey(window, GLFW_KEY_W);
    int S = glfwGetKey(window, GLFW_KEY_S);
    int A = glfwGetKey(window, GLFW_KEY_A);
    int D = glfwGetKey(window, GLFW_KEY_D);
    int Q = glfwGetKey(window, GLFW_KEY_Q);
    int E = glfwGetKey(window, GLFW_KEY_E);
    int UP = glfwGetKey(window, GLFW_KEY_UP);
    int DOWN = glfwGetKey(window, GLFW_KEY_DOWN);
    int MOUSE_BUTTON_LEFT = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
    int MOUSE_BUTTON_RIGHT = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);
    if(C)
    {
        if(glfwGetTime()-pre_cam_change > 1.0/10)
        {
            camera_choice += 1 ;
            camera_choice %= 6 ;
            pre_cam_change = glfwGetTime();
        }
    }
    if(W)
    {
        plane.change_speed(plane.acceleration);
        plane.is_accelerating = true;
        plane.fuel-=0.01;
        cout << plane.fuel << endl;
    }
    if(S)
    {
        plane.change_speed(-plane.acceleration);
    }
    if(A)
    {
        plane.rotation_Z(1);
    }
    if(D)
    {
        plane.rotation_Z(-1);
    }
    if(Q)
    {
        plane.rotation_Y(1);
    }
    if(E)
    {
        plane.rotation_Y(-1);
    }
    if(UP)
    {
        plane.rotation_X(-1);
    }
    if(DOWN)
    {
        plane.rotation_X(1);
    }
    if(MOUSE_BUTTON_LEFT)
    {
        system("amixer -D pulse sset Master 50%");
        system("aplay -q ../sounds/missile.wav &");
        missiles.push_back(Missile(plane.position,plane.rotation));
    }
    if(MOUSE_BUTTON_RIGHT)
    {
        glm::vec3 forward = glm::vec3(plane.rotation[2][0],plane.rotation[2][1],plane.rotation[2][2]);
        glm::vec3 up = glm::vec3(plane.rotation[1][0],plane.rotation[1][1],plane.rotation[1][2]);
        bombs.push_back(Bomb(plane.position-up*0.5f,forward,plane.speed));
    }
    if (left) {
        // Do something
    }
}

void tick_elements() {
    plane.tick();
    score.add(0);
    for(int i=0;i<missiles.size();i++)
    {
        missiles[i].tick();
        if(missiles[i].position.y<0)
        {
            missiles.erase(missiles.begin()+i);
            i--;
            continue;
        }
        if(glm::length(missiles[i].position-plane.position) > 1000.f/screen_zoom)
        {
            missiles.erase(missiles.begin()+i);
            i--;
            continue;
        }
        if(detect_collision(missiles[i].box,cannon.box))
        {
            missiles.erase(missiles.begin()+i);
            system("amixer -D pulse sset Master 80%");
            system("aplay -q ../sounds/explosion.wav &");
            i--;
            cout << "CHECKPOINT CLEARED ! Score += 100" << endl;
            plane.score+=100;
            score.add(100);
            float cannon_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1500.0)))-750+plane.position.x;
            if(cannon_x > 3000)
                cannon_x = 3000;
            else if(cannon_x < -3000)
                cannon_x = -3000;
            float cannon_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1500.0)))-750+plane.position.z;
            if(cannon_z > 3000)
                cannon_z = 3000;
            else if(cannon_z < -3000)
                cannon_z = -3000;
            cannon.set_position(cannon_x,0,cannon_z);
            continue;
        }
        for(int j=0; j<parachutes.size();j++)
        {
            if(detect_collision(parachutes[j].box,missiles[i].box))
            {
                missiles.erase(missiles.begin()+i);
                i--;
                parachutes.erase(parachutes.begin()+j);
                system("amixer -D pulse sset Master 50%");
                system("aplay -q ../sounds/parachute.wav &");
                cout << "PARACHUTE HIT ! Score += 50" << endl;
                plane.score+=50;
                score.add(50);
                float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
                float y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
                float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
                float vel_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
                float vel_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
                x = plane.position.x + x*2000;
                z = plane.position.z + z*2000;
                y = 100 + y*10 ;
                parachutes.push_back(Parachute(x,y,z,vel_x,vel_z,COLOR_BOOMERANG));
                break;
            }
        }
    }
    for(int i=0;i<bombs.size();i++)
    {
        bombs[i].tick();
        if(bombs[i].position.y<0)
        {
            bombs.erase(bombs.begin()+i);
            i--;
            continue;
        }
        if(glm::length(bombs[i].position-plane.position) > 1000.f/screen_zoom)
        {
            bombs.erase(bombs.begin()+i);
            i--;
            continue;
        }
        if(detect_collision(bombs[i].box,cannon.box))
        {
            bombs.erase(bombs.begin()+i);
            system("amixer -D pulse sset Master 80%");
            system("aplay -q ../sounds/explosion.wav &");
            i--;
            cout << "CHECKPOINT CLEARED ! Score += 100" << endl;
            plane.score+=100;
            score.add(100);
            float cannon_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1500.0)))-750+plane.position.x;
            if(cannon_x > 3000)
                cannon_x = 3000;
            else if(cannon_x < -3000)
                cannon_x = -3000;
            float cannon_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1500.0)))-750+plane.position.z;
            if(cannon_z > 3000)
                cannon_z = 3000;
            else if(cannon_z < -3000)
                cannon_z = -3000;
            cannon.set_position(cannon_x,0,cannon_z);
            continue;
        }
    }
    for(int i=0;i<hills.size();i++)
    {
        if(detect_collision(plane.box,hills[i].box))
        {
            plane.health -= 5;
            cout << "WARNING ! TEMPERATURE RISING ! Health -= 5" << endl ;
        }
    }
    // glm::vec3 plane_z_direction = glm::normalize(glm::vec3(plane.rotation[2][0],plane.rotation[2][1],plane.rotation[2][2]));
    // glm::vec3 ring_z_direction  = glm::normalize(glm::vec3(0,0,1));
    // float cross = glm::length(glm::cross(plane_z_direction,ring_z_direction));
    // float angle = glm::asin(cross)* 180.0 / M_PI;
    // cout << "angle = " << angle << endl ;
    for(int i=0;i<rings.size();i++)
    {
        if(detect_collision(plane.box,rings[i].box))
        {
            // glm::vec3 plane_z_direction = glm::normalize(glm::vec3(plane.rotation[2][0],plane.rotation[2][1],plane.rotation[2][2]));
            // glm::vec3 ring_z_direction = glm::normalize(glm::vec3(0,0,1));
            // float angle = glm::acos(glm::dot(plane_z_direction,ring_z_direction))* 180.0f / M_PI;
            // cout << "angle = " << angle << endl ;

            glm::vec3 plane_z_direction = glm::normalize(glm::vec3(plane.rotation[2][0],plane.rotation[2][1],plane.rotation[2][2]));
            glm::vec3 ring_z_direction  = glm::normalize(glm::vec3(0,0,1));
            float cross = glm::length(glm::cross(plane_z_direction,ring_z_direction));
            float angle = glm::asin(cross)* 180.0 / M_PI;
            if(angle < 50)
            {
                rings.erase(rings.begin()+i);
                system("amixer -D pulse sset Master 30%");
                system("aplay -q ../sounds/ring.wav &");
                cout << "WooHoo GOT THROUGH RING ! SCORE += 200 !" << endl ;
                plane.score += 200;
                score.add(200);
                cout << "angle = " << angle << endl ;
                break;
            }
        }
    }
    if(glfwGetTime()-pre_cannon_fire > 2.0)
    {
        if(glm::length(cannon.position-plane.position) < 600)
        {
            fire_balls.push_back(FireBall(cannon.position,glm::normalize(-plane.position+cannon.position)));
            system("amixer -D pulse sset Master 20%");
            system("aplay -q ../sounds/cannon.wav &");
            // system("amixer -D pulse sset Master 20%+");
        }
        cout << "fire_ball count :" << fire_balls.size() << endl;
        pre_cannon_fire = glfwGetTime();
    }

    for(int i=0; i<fire_balls.size();i++)
    {
        if(fire_balls[i].position.y<0 || glm::length(fire_balls[i].position-plane.position) > 1000)
        {
            fire_balls.erase(fire_balls.begin()+i);
            i--;
            continue;
        }
        fire_balls[i].tick();
        if(detect_collision(fire_balls[i].box,plane.box))
        {
            cout << "Fire Ball Collision ! Health -= 1" << endl;
            system("amixer -D pulse sset Master 20%");
            system("aplay -q ../sounds/cannon_hit.wav &");
            plane.health -= 1;
            fire_balls.erase(fire_balls.begin()+i);
            i--;
            continue;
        }
    }

    for(int i=0; i<parachutes.size();i++)
    {
        parachutes[i].tick();

        if(parachutes[i].position.y<-3.5f)
        {
            parachutes.erase(parachutes.begin()+i);
            float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float vel_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
            float vel_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
            x = plane.position.x + x*2000;
            z = plane.position.z + z*2000;
            y = 100 + y*10 ;
            parachutes.push_back(Parachute(x,y,z,vel_x,vel_z,COLOR_BOOMERANG));
            i--;
            continue;
        }
        if(detect_collision(parachutes[i].box,plane.box))
        {
            parachutes.erase(parachutes.begin()+i);
            system("amixer -D pulse sset Master 50%");
            system("aplay -q ../sounds/parachute.wav &");
            cout << "PARACHUTE HIT ! Score += 10 Health -= 1" << endl;
            plane.health -= 1;
            plane.score  += 10;
            score.add(10);
            float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float vel_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
            float vel_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
            x = plane.position.x + x*2000;
            z = plane.position.z + z*2000;
            y = 100 + y*10 ;
            parachutes.push_back(Parachute(x,y,z,vel_x,vel_z,COLOR_BOOMERANG));
            i--;
            continue;
        }
    }
    for(int i=0; i<health.size();i++)
    {
        health[i].tick();

        if(health[i].position.y<-3.5f)
        {
            health.erase(health.begin()+i);
            float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float vel_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
            float vel_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
            x = plane.position.x + x*800;
            z = plane.position.z + z*800;
            y = 100 + y*20 ;
            health.push_back(Power_Up(x,y,z,vel_x,vel_z,COLOR_GREEN));
            i--;
            continue;
        }
        if(detect_collision(health[i].box,plane.box))
        {
            if(plane.health<100)
            {
                cout << "POWER_UP HIT ! Health Regenrating" << endl;
                if(glfwGetTime()-pre_fuel>2)
                {
                    system("amixer -D pulse sset Master 30%");
                    system("aplay -q ../sounds/health.wav &");
                    pre_fuel = glfwGetTime();
                }
                plane.health += 1;
            }
            else
            {
                cout << "POWER_UP HIT ! Health already FULL" << endl;
                plane.health = 100;
            }
            continue;
        }
    }
    for(int i=0; i<fuel.size();i++)
    {
        fuel[i].tick();

        if(fuel[i].position.y<-3.5f)
        {
            fuel.erase(fuel.begin()+i);
            float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
            float vel_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
            float vel_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
            x = plane.position.x + x*800;
            z = plane.position.z + z*800;
            y = 100 + y*20 ;
            fuel.push_back(Power_Up(x,y,z,vel_x,vel_z,COLOR_JET_GREY));
            i--;
            continue;
        }
        if(detect_collision(fuel[i].box,plane.box))
        {
            if(plane.fuel<100)
            {
                cout << "POWER_UP HIT ! Fuel tank getting filled" << endl;
                if(glfwGetTime()-pre_fuel>2)
                {
                    system("amixer -D pulse sset Master 30%");
                    system("aplay -q ../sounds/fuel.wav &");
                    pre_fuel = glfwGetTime();
                }
                plane.fuel += 1;
            }
            else
            {
                cout << "POWER_UP HIT ! Fuel tank already FULL" << endl;
                plane.fuel = 100;
            }
            continue;
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane       = Plane(0,50, 0, COLOR_GREEN);
    ground      = Ground(0,0, 0, COLOR_GROUND);
    dashboard   = Dashboard(0,0,4.8,COLOR_BOOMERANG);
    for(int i=0;i<40;i++)
    {
        float radius = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5.0)))+5.0f;
        float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        hills.push_back(Hill(x*3000,0,z*3000,radius,COLOR_BOOMERANG));
    }
    for(int i=0;i<20;i++)
    {
        float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        x = plane.position.x + x*2000;
        z = plane.position.z + z*2000;
        y = 50 + y*20 ;
        rings.push_back(Ring(x,y,z,COLOR_BOOMERANG));
    }
    float cannon_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1500.0)))-750+plane.position.x;
    float cannon_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1500.0)))-750+plane.position.z;
    cannon = Cannon(cannon_x,0,cannon_z,COLOR_BROWN);

    for(int i=0;i<40;i++)
    {
        float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float vel_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
        float vel_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
        x = plane.position.x + x*2000;
        z = plane.position.z + z*2000;
        y = 100 + y*10 ;
        parachutes.push_back(Parachute(x,y,z,vel_x,vel_z,COLOR_BOOMERANG));
    }

    for(int i=0;i<4;i++)
    {
        float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float vel_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
        float vel_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
        x = plane.position.x + x*800;
        z = plane.position.z + z*800;
        y = 100 + y*20 ;
        health.push_back(Power_Up(x,y,z,vel_x,vel_z,COLOR_GREEN));
    }

    for(int i=0;i<4;i++)
    {
        float x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)))-0.5f;
        float vel_x = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
        float vel_z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.2)))-0.1f;
        x = plane.position.x + x*800;
        z = plane.position.z + z*800;
        y = 100 + y*20 ;
        fuel.push_back(Power_Up(x,y,z,vel_x,vel_z,COLOR_JET_GREY));
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices2.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    func();

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }
        if(plane.fuel < 0)
        {
            cout << "Fuel tank empty !" << endl;
            cout << "Score : " << plane.score << endl;
            quit(window);
        }
        if(plane.health < 0)
        {
            cout << "Health below zero !" << endl;
            cout << "Score : " << plane.score << endl;
            quit(window);
        }
        if(plane.position.y < 0)
        {
            cout << "health decreasing : " << plane.health << endl;
            // if(glfwGetTime()-pre_beep>2)
            // {
            //     pre_beep = glfwGetTime();
            system("amixer -D pulse sset Master 15%");
            system("aplay -q ../sounds/ring.wav &");
            // }
            plane.health -= 0.1f;
            // quit(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        usleep(15000);
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.length + b.length));
}

void reset_screen() {
    float top    = screen_center_y + 4 ;// / screen_zoom;
    float bottom = screen_center_y - 4 ;// / screen_zoom;
    float left   = screen_center_x - 4 ;// / screen_zoom;
    float right  = screen_center_x + 4 ;// / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(90.0f*screen_zoom),1.0f, 0.1f/screen_zoom, 1000.0f/screen_zoom);
    // Matrices2.projection = glm::ortho(glm::radians(90.0f),1.0f, 0.1f, 1000.0f);
    Matrices2.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
