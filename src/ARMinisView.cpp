#include "ARMinisView.h"


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
    glColor3f(1, 0, 0);

    std::vector<Piece*>::iterator it;

    for (it = piece_list.begin(); it < piece_list.end(); it++) 
    {
        Vertex *pos;
        pos = (*it)->get_location();

        glEnableClientState( GL_VERTEX_ARRAY );

        //draw core

        float vertices[16] = {
            pos->x - 150.0, pos->y, pos->z -150.0, pos->w,
            pos->x + 150.0, pos->y, pos->z -150.0, pos->w,
            pos->x + 150.0, pos->y, pos->z +150.0, pos->w,
            pos->x - 150.0, pos->y, pos->z +150.0, pos->w
        };

        glVertexPointer( 4, GL_FLOAT, 0, &vertices[0] );

        glDrawArrays(GL_QUADS, 0, 4 );

        //draw head
        
        //draw arms
        
        //draw legs
        
        //draw shirt
        
        //draw pants
        
        //draw held_obj        

        glDisableClientState(GL_VERTEX_ARRAY);
    }
}
