#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>

class Pattern
{
    private:

    public:
    Pattern();
    ~Pattern();

    char *name;
    int id;
    GLdouble width;
    GLdouble center[2];
    GLdouble trans[3][4];

};

