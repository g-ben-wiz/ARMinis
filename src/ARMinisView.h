#include "Terrain.cpp"

#include <GL/glut.h>

class ARMinisView
{
private:
	Terrain *terrain;

public:
    std::vector<Piece*> piece_list;

	void setTerrain (Terrain* t);
	
    void drawTerrain();
    void drawPieces();
};
