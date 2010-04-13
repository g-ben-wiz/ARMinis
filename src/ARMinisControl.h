#include "ARMinisView.cpp"

#include <GL/glut.h>

class ARMinisControl
{
private:
	Terrain *terrain;
    GLUquadricObj *quadra;
    Piece *dragged_piece;

public:
    ARMinisControl();
    std::vector<Piece*> piece_list;

    void move_to(Piece *p, Terrain *t, float x, float y, float z);

    void start_drag(Piece *p);
    void drag(Piece *p, float screen_x, float screen_y, float screen_z);
    void drop();

	void setTerrain (Terrain* t);
};
