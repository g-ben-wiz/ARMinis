#include "ARMinisView.h"

ARMinisView::ARMinisView()
{
    quadra = gluNewQuadric();
    gluQuadricNormals(quadra, GLU_SMOOTH);
    
    cam.eye_x = 0.0;
    cam.eye_y = 10.0;
    cam.eye_z = 0.0;

    cam.los_x = 0.0;
    cam.los_y = 0.0;
    cam.los_z = -1.0;

    cam.h_angle = 0.0;
    cam.v_angle = 0.0;

    cam.up_x = 0.0;
    cam.up_y = 1.0;
    cam.up_z = 0.0;

    cam.near = 1;
    cam.far = 10000;

    cam.fov_y = 45;
    cam.aspect_ratio = 1.0 * (800 / 680);
}

ARMinisView::~ARMinisView()
{
    gluDeleteQuadric(quadra);
}

void ARMinisView::setTerrain (Terrain* t) {
	this->terrain = t;
}

void ARMinisView::turn_cam()
{
    float center_x, center_y, center_z;

    cam.los_x = sin(cam.h_angle);
    cam.los_y = -sin(cam.v_angle);
    cam.los_z = -cos(cam.h_angle);

    center_x = cam.eye_x + cam.los_x;
    center_y = cam.eye_y + cam.los_y;
    center_z = cam.eye_z + cam.los_z;

    glLoadIdentity();
    gluLookAt(cam.eye_x, cam.eye_y, cam.eye_z,
              center_x, center_y, center_z,
              cam.up_x, cam.up_y, cam.up_z);
}

void ARMinisView::zoom(int h_direction, int v_direction)
{
    float speed = 10.0;
    float center_x, center_y, center_z;

    cam.eye_x = cam.eye_x + h_direction * cam.los_x * speed;
    cam.eye_y = cam.eye_y + v_direction * cam.los_y * speed;
    cam.eye_z = cam.eye_z + h_direction * cam.los_z * speed;

    center_x = cam.eye_x + cam.los_x;
    center_y = cam.eye_y + cam.los_y;
    center_z = cam.eye_z + cam.los_z;

    glLoadIdentity();
    gluLookAt(cam.eye_x, cam.eye_y, cam.eye_z,
              center_x, center_y, center_z,
              cam.up_x, cam.up_y, cam.up_z);
}

void ARMinisView::drawTerrain()
{
	//draw a 50 square x 1 x 50 square terrain
	//each sq 30 px
	//put a 3-square (150px) radius dais in the middle raised 30 px higher than the rest

	//draw ground
    glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
    	
	glEnableClientState( GL_VERTEX_ARRAY );

	glVertexPointer( 4, GL_FLOAT, 0, &terrain->vertices.front());

	glDrawArrays(GL_QUADS, 0, 4 * 50 * 50);

    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

void ARMinisView::drawPieces()
{
    std::vector<Piece*>::iterator it;
    std::vector<longbone*>::iterator lb_it;

    for (it = piece_list.begin(); it < piece_list.end(); it++) 
    {
        //draw each bone in each bone_list (in each piece)
        for (lb_it = (*it)->longbone_list.begin(); lb_it < (*it)->longbone_list.end(); lb_it++)
          {
             glPushMatrix();
             
             glTranslatef((*lb_it)->center_point.x, (*lb_it)->center_point.y, (*lb_it)->center_point.z);
             glRotatef((*lb_it)->rot_angle, (*lb_it)->rot_x, (*lb_it)->rot_y, (*lb_it)->rot_z);

             glColor3f((*lb_it)->rgb_r,(*lb_it)->rgb_g,(*lb_it)->rgb_b);


             gluCylinder(quadra, (*lb_it)->radius_bottom, (*lb_it)->radius_top, (*lb_it)->length, (*lb_it)->slices, (*lb_it)->stacks);

             glPopMatrix(); 
          }

        //TODO 
        //gluSphere calls from spherebone_list
        //draw shirt
        //draw pants
        //draw held_obj        
    }

}
