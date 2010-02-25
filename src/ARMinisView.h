#include "Terrain.cpp"

#include <GL/glut.h>

struct Camera 
{
    GLdouble eye_x, eye_y, eye_z,
             center_x, center_y, center_z,
             up_x, up_y, up_z,
             near, far, fov_y, zoom, aspect_ratio;
};

class ARMinisView
{
private:
	Terrain *terrain;
    GLUquadricObj *quadra;

public:
    ARMinisView();
    std::vector<Piece*> piece_list;
    Camera cam;

	void setTerrain (Terrain* t);
	
    void drawTerrain();
    void drawPieces();
};
