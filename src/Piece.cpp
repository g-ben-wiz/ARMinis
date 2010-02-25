#include "Piece.h"

Piece::Piece()
{
    l_arm_upper = new longbone;
    l_arm_lower = new longbone;
    r_arm_upper = new longbone;
    r_arm_lower = new longbone;
    
    l_hand = new spherebone;
    r_hand = new spherebone;

    l_femur = new longbone;
    l_shin = new longbone;
    l_foot = new longbone;
    r_femur = new longbone;
    r_shin = new longbone;
    r_foot = new longbone;

    core = new longbone;

    face = new longbone;
    skull = new spherebone;

    held_obj = NULL;
    shirt = NULL; 
    pants = NULL;
}

Piece::~Piece()
{
    delete(l_arm_upper);
    delete(l_arm_lower);
    delete(r_arm_upper);
    delete(r_arm_lower);
    delete(l_hand);
    delete(r_hand);

    delete(l_femur);
    delete(l_shin);
    delete(l_foot);
    delete(r_femur);
    delete(r_shin);
    delete(r_foot);

    delete(face);
    delete(skull);
    
    if (held_obj)
        delete(held_obj);

    if (shirt)
        delete(shirt);

    if (pants)
        delete(pants);

    delete(core);
}

void Piece::set_location(Vertex* loc)
{
    location = *loc;
}

Vertex* Piece::get_location()
{
    return &location;
}


void Piece::set_l_arm_upper(longbone* bone){*l_arm_upper = *bone;}
void Piece::set_l_arm_lower(longbone* bone){*l_arm_lower = *bone;}
void Piece::set_r_arm_upper(longbone* bone){*r_arm_upper = *bone;}
void Piece::set_r_arm_lower(longbone* bone){*r_arm_lower = *bone;}
void Piece::set_l_hand(spherebone* bone){*l_hand = *bone;}
void Piece::set_r_hand(spherebone* bone){*r_hand = *bone;}
void Piece::set_skull(spherebone* bone){*skull = *bone;}

void Piece::set_l_femur(longbone* bone){*l_femur = *bone;}
void Piece::set_l_shin(longbone* bone){*l_shin = *bone;}
void Piece::set_l_foot(longbone* bone){*l_foot = *bone;}
void Piece::set_r_femur(longbone* bone){*r_femur = *bone;}
void Piece::set_r_shin(longbone* bone){*r_shin = *bone;}
void Piece::set_r_foot(longbone* bone){*r_foot = *bone;}
void Piece::set_core(longbone* bone){*core = *bone;}
void Piece::set_face(longbone* bone){*face = *bone;}

longbone* Piece::get_l_arm_upper(){return l_arm_upper;}
longbone* Piece::get_l_arm_lower(){return l_arm_lower;}
longbone* Piece::get_r_arm_upper(){return r_arm_upper;}
longbone* Piece::get_r_arm_lower(){return r_arm_lower;}
spherebone* Piece::get_l_hand(){return l_hand;}
spherebone* Piece::get_r_hand(){return r_hand;}
spherebone* Piece::get_skull(){return skull;}

longbone* Piece::get_l_femur(){return l_femur;}
longbone* Piece::get_l_shin(){return l_shin;}
longbone* Piece::get_l_foot(){return l_foot;}
longbone* Piece::get_r_femur(){return r_femur;}
longbone* Piece::get_r_shin(){return r_shin;}
longbone* Piece::get_r_foot(){return r_foot;}
longbone* Piece::get_core(){return core;}
longbone* Piece::get_face(){return face;}


