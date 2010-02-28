#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

#include <vector>

#include "ARMinisView.cpp"

void render();
void normal_key_foo(unsigned char key, int x, int y);
void special_key_foo(int key, int x, int y);
void reshape(int width, int height);
void refresh_camera();
void set_los();

Terrain terrain;
ARMinisView view;

int main(int argc, char** argv)
{
	::view.setTerrain(&terrain);

    terrain.load_data("../terrain/dwarven-ruin.map");

    Piece *dwarf = new Piece();
    ::view.piece_list.push_back(dwarf);

    Vertex dwarfloc;
    dwarfloc.x = 000.0;
    dwarfloc.y = 50.0;
    dwarfloc.z = 100.0;
    dwarfloc.w = 1.0;

    dwarf->set_location(&dwarfloc);
    
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 680);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 

	glutCreateWindow("ARMinis");

	glEnable(GL_DEPTH_TEST);

	glutIdleFunc(render);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(normal_key_foo);	
    glutSpecialFunc(special_key_foo);
	
	glutMainLoop();

	return 0;
}

void reshape(int width, int height)
{
	if (height == 0) 
		height = 1;

    ::view.cam.aspect_ratio = 1.0 * width/height;
	glViewport(0, 0, width, height); 

    refresh_camera();

}

void refresh_camera()
{
    Camera *cam = new Camera;
    *cam = ::view.cam; 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(cam->fov_y, cam->aspect_ratio, cam->near, cam->far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt( cam->eye_x, cam->eye_y, cam->eye_z,
	       cam->center_x, cam->center_y, cam->center_z, 
	       cam->up_x, cam->up_y, cam->up_z); //up-vector
    delete(cam);
}

void normal_key_foo(unsigned char key, int x, int y) 
{
    float zoom_mag = 30.0;
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 'z': //need fixed so it's like cam.forward_x
            ::view.cam.eye_x += (view.cam.up_x * zoom_mag);
            ::view.cam.eye_y += (view.cam.up_y * zoom_mag);
            ::view.cam.eye_z += (view.cam.up_z * zoom_mag);

            refresh_camera();
            break;
        case 'x':
            ::view.cam.eye_x -= (view.cam.up_x * zoom_mag);
            ::view.cam.eye_y -= (view.cam.up_y * zoom_mag);
            ::view.cam.eye_z -= (view.cam.up_z * zoom_mag);
           
            refresh_camera();
    }
}

void special_key_foo(int key, int x, int y)
{
    int mod = glutGetModifiers();
    float distance = 300.0;
    switch (key)
    {
        case GLUT_KEY_LEFT :
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.h_angle -= .03;
                ::view.cam.center_x = cos(::view.cam.h_angle) - sin(::view.cam.h_angle);
                ::view.cam.center_z = cos(::view.cam.h_angle) + sin(::view.cam.h_angle);
                
                ::view.cam.center_x *= distance;
                ::view.cam.center_z *= distance;
                
            }
            else
            {
                view.cam.eye_x += 50;
            }
            refresh_camera();
            break;
        case GLUT_KEY_RIGHT:
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.h_angle += .03;
                ::view.cam.center_x = cos(::view.cam.h_angle) - sin(::view.cam.h_angle);
                ::view.cam.center_z = cos(::view.cam.h_angle) + sin(::view.cam.h_angle);
                
                ::view.cam.center_x *= distance;
                ::view.cam.center_z *= distance;
            }
            else 
            {
                view.cam.eye_x -= 50;
            }
            refresh_camera();
            break;
        case GLUT_KEY_UP:
            //view.cam.eye_y -= 50;
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.v_angle -= .03;
                ::view.cam.center_y = cos(::view.cam.v_angle) - sin(::view.cam.v_angle);
                ::view.cam.center_z = cos(::view.cam.v_angle) + sin(::view.cam.v_angle);
                
                ::view.cam.center_y *= distance;
                ::view.cam.center_z *= distance;
            }
            refresh_camera();
            break;
        case GLUT_KEY_DOWN:
            //view.cam.eye_y -= 50;
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.v_angle += .03;
                ::view.cam.center_y = cos(::view.cam.v_angle) - sin(::view.cam.v_angle);
                ::view.cam.center_z = cos(::view.cam.v_angle) + sin(::view.cam.v_angle);
                
                ::view.cam.center_y *= distance;
                ::view.cam.center_z *= distance;
            }
            refresh_camera();
    }
}

void render()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    //draw map
    view.drawTerrain();

    //draw all pieces in view.piece_list)
    //view.drawPieces();

    glutSwapBuffers();
}

