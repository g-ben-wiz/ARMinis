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

    for (it = piece_list.begin(); it < piece_list.end(); it++) 
    {
        Vertex *pos;
        pos = (*it)->get_location();

        //draw core
        float core_length = 10.0;
        glPushMatrix();

        glColor3f(0, .7, .3);
        glTranslatef(pos->x, pos->y, pos->z);
        glRotatef(90.0, 1.0 ,0.0 ,0.0 ); 
        gluCylinder(quadra, 5.0, 3.0, core_length, 20, 20);
        
        glPopMatrix();

        //draw head
        float skull_radius = 2.5; 
        float neck_length = .5;

        glPushMatrix();

        glColor3f(0, 0, 1);
        glTranslatef(pos->x, pos->y + core_length / 2 + neck_length, pos->z );
        glRotatef(90.0, 1.0 ,0.0 ,0.0 ); 
        gluSphere(quadra,skull_radius, 20, 20);

        glPopMatrix();

        //draw arms
        //left upper
        glColor3f (1, 1, 0);
        glPushMatrix();
        
        glTranslatef(pos->x + 5, pos->y , pos->z);
        glRotatef(90.0, 1.0 ,0.0 ,0.0 ); 
        gluCylinder(quadra, 2.0, 1.5, 6.0, 20, 20);

        glPopMatrix();

        //left lower
        glColor3f (.3, .7, .7);
        glPushMatrix();
        
        glTranslatef(pos->x + 5, pos->y - 6, pos->z);
        glRotatef(90.0, 1.0 ,0.0 ,0.0 ); 
        gluCylinder(quadra, 1.5, 1.0, 6.0, 20, 20);

        glPopMatrix();

        //left hand 
        glPushMatrix();
            
        glPopMatrix();

        //right upper
        glPushMatrix();
        
        glPopMatrix();

        //right lower
        glPushMatrix();
        
        glPopMatrix();

        //right hand
        glPushMatrix();
        
        glPopMatrix();


        //draw legs
        //left femur
        glColor3f(1, .7, .7);
        glPushMatrix();

        glTranslatef(pos->x + 2, pos->y - 5 - 3,  pos->z); //y - half core len - half femur len
        glRotatef(90.0, 1.0 ,0.0 ,0.0 ); 
        gluCylinder(quadra, 2.0, 1.5, 6.0, 20, 20);

        glPopMatrix();

        //left shin
        glColor3f(.7, .7, 1);
        glPushMatrix();
        
        glTranslatef(pos->x + 2 , pos->y - 5 - 6 - 2.5,  pos->z);
        glRotatef(90.0, 1.0 ,0.0 ,0.0 ); 
        gluCylinder(quadra, 1.5, 1.2, 5.0, 20, 20);

        glPopMatrix();

        //left foot
        glColor3f(0, 1, 0);
        glPushMatrix();

        glTranslatef(pos->x + 2 , pos->y - 5 - 6 - 5 - 2.25,  pos->z);
        glRotatef(90.0, 0.0 ,0.0 ,1.0 ); 
        gluCylinder(quadra, 1.0, 0.8, 2.5, 20, 20);

        glPopMatrix();

        //right femur
        glPushMatrix();

        glPopMatrix();

        //right shin
        glPushMatrix();

        glPopMatrix();
        
        //right foot
        glPushMatrix();

        glPopMatrix();

        //draw shirt
        glPushMatrix();

        glPopMatrix();

        //draw pants
        glPushMatrix();

        glPopMatrix();
        
        //draw held_obj        
        glPushMatrix();

        glPopMatrix();
    }

}
