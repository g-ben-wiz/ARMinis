#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

#include <vector>

#include "ARMinisControl.cpp"

#include "Pattern.cpp"

void init();
void render();
void normal_key_foo(unsigned char key, int x, int y);
void special_key_foo(int key, int x, int y);
void mouse_foo(int button, int state, int x, int y);
void process_dragging(int x, int y);
void reshape(int width, int height);
void refresh_camera();
void ar_loop();
bool check_line_tri( Vertex TP1, Vertex TP2, Vertex TP3, Vertex LP1, Vertex LP2, Vertex &HitPos);

Terrain terrain;
ARMinisView view;
ARMinisControl control;
Pattern patt;

int main(int argc, char** argv)
{
	::view.setTerrain(&terrain);
    ::control.set_view(&view);

    patt.name = "Data/wiz_hat.patt";
    patt.width = 80.0;
    patt.center[0] = 0.0;
    patt.center[1] = 100.0;

    terrain.load_data("../terrain/dwarven-ruin.map");

    Piece *dwarf = new Piece();
    dwarf->load_data("../model/dwarf.mod");
    ::view.piece_list.push_back(dwarf);
    control.move_to(dwarf, &terrain, 30 * 30.f, 0.f, 30 * 30.f); 


    Piece *dwarf2 = new Piece();
    dwarf2->load_data("../model/dwarf.mod");
    ::view.piece_list.push_back(dwarf2);
    control.move_to(dwarf2, &terrain, 35 * 30.f, 0.f, 30 * 30.f); 
    
	glutInit(&argc, argv);
    init();
    glutMotionFunc(process_dragging);

    arVideoCapStart();
    argMainLoop( mouse_foo, normal_key_foo, ar_loop);

//	glutInitWindowPosition(0, 0);
//	glutInitWindowSize(800, 680);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE); 

//	glutCreateWindow("ARMinis");

/*	glEnable(GL_DEPTH_TEST);

	glutIdleFunc(render);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(normal_key_foo);	
    glutSpecialFunc(special_key_foo);

    glutMouseFunc(mouse_foo);
	glutMainLoop();
*/

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

void init()
{
    ARParam cparam;
    char *cparam_name = "Data/camera_para.dat";
    ARParam wparam;
    int x_size, y_size;
    
    if (arVideoOpen ("") < 0)
        exit(0);

    if (arVideoInqSize(&x_size, &y_size) < 0)
        exit(0);


    if (arParamLoad(cparam_name, 1, &wparam) < 0)
    {
        printf("Not finding cparam_name\n");
        exit(0);
    }

    arParamChangeSize( &wparam, x_size, y_size, &cparam);
    arInitCparam (&cparam);
    printf("Cam Param\n");
    arParamDisp (&cparam);

    if ((patt.id = arLoadPatt(patt.name)) < 0)
    {
        printf("Pattern load error\n");
        exit(0);
    }

    argInit( &cparam, 1.0, 0, 0, 0, 0);
}

void cleanup()
{
    arVideoCapStop();
    arVideoClose();
    argCleanup();
}

void ar_loop()
{
    int thresh = 200;

    ARUint8 *data_ptr;
    ARMarkerInfo *marker_info;
    int marker_num; 
    int j, k;

    if ((data_ptr = (ARUint8 *)arVideoGetImage()) == NULL)
    {
        arUtilSleep(2);
        return;
    }

    argDrawMode2D();
    argDispImage(data_ptr, 0, 0);

    if (arDetectMarker(data_ptr, thresh, &marker_info, &marker_num) < 0) 
    {
        cleanup();
        exit(0);
    }

    arVideoCapNext();

    //look for obj visibility
    k = -1;
    for (j = 0; j < marker_num; j++)
    {
        if (patt.id == marker_info[j].id )
        {
            if (k == 1)
                k = j;
            else if (marker_info[k].cf < marker_info[j].cf)
                k = j;
        }
    }

    if (k == -1)
    {
        argSwapBuffers();
        return;
    }

    arGetTransMat(&marker_info[k], patt.center, patt.width, patt.trans);

    render();

    argSwapBuffers();

}

void normal_key_foo(unsigned char key, int x, int y) 
{
    switch (key)
    {
        case 27:
            printf("Bye.\n");
            cleanup();
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
    GLdouble win_x_hi, win_y_hi, win_z_hi;
    GLdouble win_x_low, win_y_low, win_z_low;
    GLdouble _y_hi, _y_low;

    double d_x, d_y, d_z, d_click_y;

    float pos_x_hi, pos_x_low, pos_z_hi, pos_z_low, pos_y_hi, pos_y_low; //bandaid for hitbopos_x / height
    Vertex base_low, base_high, top; //triangle face vertices to intersect
    int i;

    Vertex hit_pos;

    Vertex clickray_near, clickray_far;

    std::vector<Piece*>::iterator it;

    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            /*
                okay what we do is take the clicked point, 
                make a ray out of it that is the difference between the point 
                near the screen, and the point into the screen
                then see if that ray intersects a triangle around our piece
                 (for each piece)
            */

            GLdouble model_matrix[16];
            GLdouble proj_matrix[16];
            int viewport[4];

            glGetDoublev(GL_MODELVIEW_MATRIX,model_matrix);
            glGetDoublev(GL_PROJECTION_MATRIX,proj_matrix);
            glGetIntegerv(GL_VIEWPORT,viewport);
            d_click_y = double (viewport[3] - y - 1);
            
            for (it = view.piece_list.begin(); it < view.piece_list.end(); it++)
            {
                pos_x = (*it)->position.x;
                pos_y = (*it)->position.y;
                pos_z = (*it)->position.z;

                top.y = pos_y + 45.0;
                top.x = pos_x;
                top.z = pos_z;

                base_low.x = pos_x - 15.0;
                base_low.y = pos_y;
                base_low.z = pos_z;

                base_high.x = pos_x + 15.0;
                base_high.y = pos_y;
                base_high.z = pos_z; 

                gluUnProject ((double) x, d_click_y, 1.0, model_matrix, proj_matrix, viewport, &clickray_far.x, &clickray_far.y, &clickray_far.z);
                gluUnProject ((double) x, d_click_y, 0.0, model_matrix, proj_matrix, viewport, &clickray_near.x, &clickray_near.y, &clickray_near.z);

                if (check_line_tri(base_low, base_high, top, clickray_near, clickray_far, hit_pos))
                {    
//                    printf("%f %f %f\n", hit_pos.x, hit_pos.y, hit_pos.z);
                    control.dragged_piece = *it;
                }
            }

        }
    }
    else if (state == GLUT_UP)
    {
        control.dragged_piece = NULL;
    }
}

void process_dragging(int x, int y)
{
    GLdouble model_matrix[16];
    GLdouble proj_matrix[16];
    int viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX,model_matrix);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_matrix);
    glGetIntegerv(GL_VIEWPORT,viewport);
//    d_click_y = double (viewport[3] - y - 1);

    control.drag(&terrain, x, y, model_matrix, proj_matrix, viewport); 
}

void render()
{
    double gl_para[16];

    argDrawMode3D();
    argDraw3dCamera(0, 0);
    glClearDepth(1.0); 
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    argConvGlpara(patt.trans, gl_para);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd (gl_para);

    //draw map
    view.drawTerrain();

    //draw all pieces in view.piece_list)
    view.drawPieces();

    glDisable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

float dot3(Vertex v1, Vertex v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vertex cross3(Vertex v1, Vertex v2)
{
    Vertex crossed;

    crossed.x = v1.y * v2.z - v1.z * v2.y;
    crossed.y = v1.z * v2.x - v1.x * v2.z;
    crossed.z = v1.x * v2.y - v1.y * v2.x;

    return crossed;
}

//check line lp's intersection with triangle tp
    //the whole projection/intersection thing is from
    //http://www.3dkingdoms.com/selection.html
    //thanks, Jonathan Kreuzer
bool check_line_tri( Vertex TP1, Vertex TP2, Vertex TP3, Vertex LP1, Vertex LP2, Vertex &HitPos)
{
   Vertex normal, intersect_pos;
   float normal_mag;

   // Find Triangle Normal
   Vertex A, B;
   A.x = TP2.x - TP1.x;
   A.y = TP2.y - TP1.y;
   A.z = TP2.z - TP1.z;

   B.x = TP3.x - TP1.x;
   B.y = TP3.y - TP1.y;
   B.z = TP3.z - TP1.z;

   normal = cross3( A, B);
   normal_mag = (normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z);
   normal_mag = sqrt(normal_mag);

   normal.x /= normal_mag;
   normal.y /= normal_mag;
   normal.z /= normal_mag;
   
   //Normal.Normalize(); // not really needed

   // Find distance from LP1 and LP2 to the plane defined by the triangle
   
   A.x = LP1.x - TP1.x;
   A.y = LP1.y - TP1.y;
   A.z = LP1.z - TP1.z;

   B.x = LP2.x - TP1.x;
   B.y = LP2.y - TP1.y;
   B.z = LP2.z - TP1.z;

   float Dist1 = dot3(A, normal);
   float Dist2 = dot3(B, normal);
   if ( (Dist1 * Dist2) >= 0.0f) return false;  // line doesn't cross the triangle.
   if ( Dist1 == Dist2) return false;// line and plane are parallel

   float r = (-Dist1 / (Dist2 - Dist1));

   // Find point on the line that intersects with the plane
   intersect_pos.x = LP2.x - LP1.x;
   intersect_pos.y = LP2.y - LP1.y;
   intersect_pos.z = LP2.z - LP1.z;

   intersect_pos.x *= r;
   intersect_pos.y *= r;
   intersect_pos.z *= r;

   intersect_pos.x += LP1.x;
   intersect_pos.y += LP1.y;
   intersect_pos.z += LP1.z;
   
   // Find if the interesection point lies inside the triangle by testing it against all edges
   Vertex vTest;

   A.x = TP2.x - TP1.x;
   A.y = TP2.y - TP1.y;
   A.z = TP2.z - TP1.z;
   vTest = cross3( normal, A);

   B.x = intersect_pos.x - TP1.x;
   B.y = intersect_pos.y - TP1.y;
   B.z = intersect_pos.z - TP1.z;
   if ( dot3( vTest, B) < 0.0f ) return false;

   A.x = TP3.x - TP2.x;
   A.y = TP3.y - TP2.y;
   A.z = TP3.z - TP2.z;
   vTest = cross3( normal, A);

   B.x = intersect_pos.x - TP2.x;
   B.y = intersect_pos.y - TP2.y;
   B.z = intersect_pos.z - TP2.z;
   if ( dot3( vTest, B) < 0.0f ) return false;
   
   A.x = TP1.x - TP3.x;
   A.y = TP1.y - TP3.y;
   A.z = TP1.z - TP3.z;
   vTest = cross3( normal, A);
   
   B.x = intersect_pos.x - TP3.x;
   B.y = intersect_pos.y - TP3.y;
   B.z = intersect_pos.z - TP3.z;
   if ( dot3( vTest, B) < 0.0f ) return false;

   HitPos = intersect_pos;
   return true;
}
