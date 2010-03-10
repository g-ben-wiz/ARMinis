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

void Piece::load_data(char *filename)
{
    float pos_x, pos_y, pos_z;
    float rot_angle;
    float rot_x, rot_y, rot_z; //rotation in {x,y,z} axes
    float rgb_r, rgb_g, rgb_b; //colors 0.0 - 1.0
    float radius, radius_top, radius_bottom; 
    float length;
    int slices, stacks;
    char bone_str[20], garbage[20];

    spherebone *sb = new spherebone;

    FILE *fp = fopen(filename, "r");

    while (fscanf(fp, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %s", 
                  bone_str, 
                  &pos_x, &pos_y, &pos_z,
                  &rot_angle,
                  &rot_x, &rot_y, &rot_z,
                  &rgb_r, &rgb_g, &rgb_b, 
                  &radius_top, &radius_bottom,
                  &length, &slices, &stacks,
                  garbage) 
                    == 17)
    {
        longbone *lb = new longbone;
        lb->center_point.w = 1.0;
        lb->center_point.x = this->position.x + pos_x;
        lb->center_point.y = this->position.y + pos_y;
        lb->center_point.z = this->position.z + pos_z;

        lb->rot_angle = rot_angle;
        lb->rot_x = rot_x;
        lb->rot_y = rot_y;
        lb->rot_z = rot_z;

        lb->rgb_r = rgb_r;
        lb->rgb_g = rgb_g;
        lb->rgb_b = rgb_b;

        lb->radius_top = radius_top;
        lb->radius_bottom = radius_bottom;

        lb->length = length;
        lb->slices = slices;
        lb->stacks = stacks;

        longbone_list.push_back(lb);
    }

    fclose(fp);
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


