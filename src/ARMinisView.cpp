#include "ARMinisView.h"


void ARMinisView::setTerrain (Terrain* t) {
	this->terrain = t;
}

void ARMinisView::simpleDraw()
{
	//draw a 50 square x 1 x 50 square terrain
	//each sq 30 px
	//put a 3-square (150px) radius dais in the middle raised 30 px higher than the rest

	//put all vertices into one vector &
	//all indices into another

	//then call glDrawArrays to render them all in order

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//draw ground
	glColor3f(0.6, 0.6, 0.6);
	
	glEnableClientState( GL_VERTEX_ARRAY );

	glVertexPointer( 4, GL_FLOAT, 0, &terrain->vertices.front());

	glDrawArrays(GL_QUADS, 0, 4 * 50 * 50);

    glDisableClientState(GL_VERTEX_ARRAY);
        	
	glutSwapBuffers();
}

