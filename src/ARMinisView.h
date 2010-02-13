#include "Terrain.cpp"

#include <GL/glut.h>

class ARMinisView
{
private:
	Terrain *terrain;

public:
	void setTerrain (Terrain* t);
	
	void simpleDraw();
};
