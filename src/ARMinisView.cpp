#include "ARMinisView.h"

ARMinisView::ARMinisView()
{
    quadra = gluNewQuadric();
    gluQuadricNormals(quadra, GLU_SMOOTH);
    
    cam.eye_x = 0.0;
    cam.eye_y = 3000.0;
    cam.eye_z = 0.0;

    cam.center_x = 0.0;
    cam.center_y = 0.0;
    cam.center_z = 0.0;

    cam.up_x = 0.0;
    cam.up_y = 0.0;
    cam.up_z = 1.0;

    cam.near = 1;
    cam.far = 10000;

    cam.fov_y = 45;
    cam.zoom = 1.0;
    cam.aspect_ratio = 1.0 * (800 / 680);
}
void ARMinisView::setTerrain (Terrain* t) {
	this->terrain = t;
}

void ARMinisView::drawTerrain()
{
	//draw a 50 square x 1 x 50 square terrain
	//each sq 30 px
	//put a 3-square (150px) radius dais in the middle raised 30 px higher than the rest

	//draw ground
	glColor3f(0.6, 0.6, 0.6);
	
	glEnableClientState( GL_VERTEX_ARRAY );

	glVertexPointer( 4, GL_FLOAT, 0, &terrain->vertices.front());

	glDrawArrays(GL_QUADS, 0, 4 * 50 * 50);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void ARMinisView::drawPieces()
{
    std::vector<Piece*>::iterator it;

    for (it = piece_list.begin(); it < piece_list.end(); it++) 
    {
        Vertex *pos;
        pos = (*it)->get_location();

        //draw core
        float core_length = 420.0;
        glPushMatrix();

        glColor3f(0, .7, .3);
        glTranslatef(pos->x, pos->y, pos->z);
        gluCylinder(quadra, 180.0, 180.0, core_length, 20, 20);
        
        glPopMatrix();

        //draw head
        float skull_radius = 100.0; 
        float neck_length = 22.0;

        glPushMatrix();

        glColor3f(0, 0, 1);
        glTranslatef(pos->x, pos->y, pos->z + core_length + skull_radius + neck_length);
        gluSphere(quadra,skull_radius, 20, 22);

        glPopMatrix();

        //draw arms
        //left upper
        glColor3f (.3, .3, .7);
        glPushMatrix();
        
        glTranslatef(pos->x + (core_length / 2) + 20, pos->y, pos->z + 130);
        glRotatef(-15.0, 0.0 ,1.0 ,0.0 ); 
        gluCylinder(quadra, 60.0, 70.0, 280.0, 20, 20);

        glPopMatrix();

        //left lower
        glColor3f (.3, .7, .7);
        glPushMatrix();
        
        glTranslatef(pos->x + (core_length / 2) + 40, pos->y + 100, pos->z - 95);
        glRotatef(-5.0, 0.0 ,1.0 ,0.0 ); 
        gluCylinder(quadra, 50.0, 60.0, 250.0, 20, 20);

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

        glTranslatef(pos->x + (core_length / 2) - 50, pos->y,  pos->z - core_length * .5);
        glRotatef(-5.0, 0.0 ,1.0 ,0.0 ); 
        gluCylinder(quadra, 80.0, 70.0, 200.0, 20, 20);

        glPopMatrix();

        //left shin
        glColor3f(.7, .7, 1);
        glPushMatrix();
        
        glTranslatef(pos->x + (core_length / 2) - 50, pos->y,  pos->z - 200 - 200);
        glRotatef(0.0, 0.0 ,1.0 ,0.0 ); 
        gluCylinder(quadra, 60.0, 70.0, 200.0, 20, 20);

        glPopMatrix();

        //left foot
        glPushMatrix();

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
