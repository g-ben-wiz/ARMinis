#include "Terrain.cpp"

#include <GL/glut.h>

struct Camera 
{
    GLdouble eye_x, eye_y, eye_z,
             up_x, up_y, up_z,
             near, far, fov_y, aspect_ratio,
             h_angle, v_angle,
             los_x, los_y, los_z;
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
    void turn_cam();
};
