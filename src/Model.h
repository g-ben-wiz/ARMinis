#include "Vertex.h"
#include <algorithm>

struct rotate_record
{
    float rot_angle;
    float rot_x; //0 to 1
    float rot_y; //0 to 1
    float rot_z; //0 to 1
};

class Model
{
public:
    Vertex position; //where it goes in game-world coordinates
    GLdouble screen_x, screen_y; //where it goes on the screen
    rotate_record rot;    
};
