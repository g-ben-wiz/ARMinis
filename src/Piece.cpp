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

    cranium_front = new spherebone;
    cranium_back = new spherebone;

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

    delete(cranium_front);
    delete(cranium_back);
    
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
