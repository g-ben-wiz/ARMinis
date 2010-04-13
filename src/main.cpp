#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

#include <vector>

#include "ARMinisControl.cpp"

void render();
void normal_key_foo(unsigned char key, int x, int y);
void special_key_foo(int key, int x, int y);
void mouse_foo(int button, int state, int x, int y);
void reshape(int width, int height);
void refresh_camera();

Terrain terrain;
ARMinisView view;
ARMinisControl control;

int main(int argc, char** argv)
{
	::view.setTerrain(&terrain);

    terrain.load_data("../terrain/dwarven-ruin.map");

    Piece *dwarf = new Piece();
    dwarf->load_data("../model/dwarf.mod");
    ::view.piece_list.push_back(dwarf);
    
    control.move_to(dwarf, &terrain, 25 * 30.f, 0.f, 25 * 30.f); 
    
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 680);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE); 

	glutCreateWindow("ARMinis");

	glEnable(GL_DEPTH_TEST);

	glutIdleFunc(render);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(normal_key_foo);	
    glutSpecialFunc(special_key_foo);

    glutMouseFunc(mouse_foo);
	
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

    float center_x = cam->eye_x + cam->los_x;
    float center_y = cam->eye_y + cam->los_y;
    float center_z = cam->eye_z + cam->los_z;

    gluLookAt( cam->eye_x, cam->eye_y, cam->eye_z,
	       center_x, center_y, center_z, 
	       cam->up_x, cam->up_y, cam->up_z); //up-vector
    delete(cam);
}

void normal_key_foo(unsigned char key, int x, int y) 
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 'z': 
            ::view.zoom(1, 1);
            break;
        case 'x':
            ::view.zoom(-1, -1);
            break;
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
                ::view.turn_cam();                       
            }
            else
            {
            }
            break;
        case GLUT_KEY_RIGHT:
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.h_angle += .03;
                ::view.turn_cam();                       
            }
            else 
            {
            }
            break;
        case GLUT_KEY_UP:
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.v_angle -= .03;
                ::view.turn_cam();
            }
            else 
            {
            }
            break;
        case GLUT_KEY_DOWN:
            if (mod == GLUT_ACTIVE_CTRL) 
            {
                ::view.cam.v_angle += .03;
                ::view.turn_cam();
            }
            else
            {
            }
    }
}

void mouse_foo(int button, int state, int x, int y)
{
    float pos_x, pos_y, pos_z;
    float xhi, xlow, zhi, zlow, yhi, ylow; //bandaid for hitbox / height
    int i;
    GLdouble clickray_near_x, clickray_near_y, clickray_near_z;
    GLdouble clickray_far_x, clickray_far_y, clickray_far_z;
    GLdouble raydir_x, raydir_y, raydir_z;
    GLdouble raymag;
    std::vector<Piece*>::iterator it;

    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            /*
            One way to generate a pick ray is to call gluUnProject()  twice for the mouse location, first with winz  of 0.0 (at the near plane), then with winz of 1.0 (at the far plane). Subtract the near plane call's results from the far plane call's results to obtain the XYZ direction vector of your ray. The ray origin is the view location, of course.


            */
            //for drag for x 
            // objPos += mouseMovementx*scale*RightAxis

            GLdouble model_matrix[16];
            glGetDoublev(GL_MODELVIEW_MATRIX,model_matrix);
            GLdouble proj_matrix[16];
            glGetDoublev(GL_PROJECTION_MATRIX,proj_matrix);
            int viewport[4];
            glGetIntegerv(GL_VIEWPORT,viewport);
            
            for (it = view.piece_list.begin(); it < view.piece_list.end(); it++)
            {
                pos_x = (*it)->position.x;
                pos_y = (*it)->position.y;
                pos_z = (*it)->position.z;

                yhi = pos_y + 40.0;
                ylow = pos_y - 40.0;
                xhi = pos_x + 30.0;
                xlow = pos_x - 30.0;
                zhi = pos_z + 30.0;
                zlow = pos_z - 30.0;

                gluUnProject(x, y, 0, 
                           model_matrix, proj_matrix, viewport,
                           &clickray_near_x, &clickray_near_y, &clickray_near_z);

                gluUnProject(x, y, 1, 
                           model_matrix, proj_matrix, viewport,
                           &clickray_far_x, &clickray_far_y, &clickray_far_z);

                raydir_x = clickray_far_x - clickray_near_x;
                raydir_y = clickray_far_y - clickray_near_y;
                raydir_z = clickray_far_z - clickray_near_z;

                raymag = raydir_x * raydir_x + raydir_y * raydir_y + raydir_z * raydir_z;
                raymag = sqrt(raymag); 

                raydir_x = raydir_x / raymag;
                raydir_y = raydir_y / raymag;
                raydir_z = raydir_z / raymag;
            
//                printf("%f %f %f\n", raydir_x, raydir_y, raydir_z);

                for (i = 1; i < 1000 && i * raydir_x < xhi && i * raydir_y < yhi && i * raydir_z < zhi; i++)
                    if (i * raydir_x < xhi && xlow < i * raydir_x)
                        if (i * raydir_y < yhi && ylow < i * raydir_y)
                            if (i * raydir_z < zhi && zlow < i * raydir_z)
                            {
                             printf("u clicked\n");
                            }
            }

        }
    }
}

void render()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    //draw map
    view.drawTerrain();

    //draw all pieces in view.piece_list)
    view.drawPieces();

    glutSwapBuffers();
}

