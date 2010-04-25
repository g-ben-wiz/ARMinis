#include "ARMinisView.cpp"

#include <GL/glut.h>

class ARMinisControl
{
private:
	Terrain *terrain;
    GLUquadricObj *quadra;

public:
    ARMinisControl();
    std::vector<Piece*> piece_list;
    Piece *dragged_piece;

    void move_to(Piece *p, Terrain *t, float x, float y, float z);

    void start_drag(Piece *p);
    void drag(Terrain *t, float screen_x, float screen_y, GLdouble *model, GLdouble *project, GLint *view);
    void drop();

	void setTerrain (Terrain* t);
};
