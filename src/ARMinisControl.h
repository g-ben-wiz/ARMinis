#include "Terrain.cpp"

#include <GL/glut.h>

class ARMinisControl
{
private:
	Terrain *terrain;
    GLUquadricObj *quadra;

public:
    ARMinisControl();
    std::vector<Piece*> piece_list;

	void setTerrain (Terrain* t);
	
};
