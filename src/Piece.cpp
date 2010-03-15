#include "Piece.h"

Piece::Piece()
{
    held_obj = NULL;
    shirt = NULL; 
    pants = NULL;
}

Piece::~Piece()
{
    //remove all bones in bone_list
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
    char bone_str[20], bone_name[20];

    FILE *fp = fopen(filename, "r");

    while (!feof(fp))
    {
        //load line
        if (fscanf(fp, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %s", 
                      bone_str, 
                      &pos_x, &pos_y, &pos_z,
                      &rot_angle,
                      &rot_x, &rot_y, &rot_z,
                      &rgb_r, &rgb_g, &rgb_b, 
                      &radius, &radius_top, &radius_bottom,
                      &length, &slices, &stacks,
                      bone_name) 
                        == 18)
        {
            if (strcmp(bone_str, "longbone") == 0)
            {   
                longbone *lb = new longbone;
                lb->center_point.w = 1.0;
                lb->center_point.x = pos_x;
                lb->center_point.y = pos_y;
                lb->center_point.z = pos_z;

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
            else if (strcmp(bone_str, "spherebone") == 0)
            {
                spherebone *sb = new spherebone;

                sb->center_point.w = 1.0;
                sb->center_point.x = pos_x;
                sb->center_point.y = pos_y;
                sb->center_point.z = pos_z;

                sb->rot_angle = rot_angle;
                sb->rot_x = rot_x;
                sb->rot_y = rot_y;
                sb->rot_z = rot_z;
                sb->rgb_r = rgb_r;
                sb->rgb_g = rgb_g;
                sb->rgb_b = rgb_b;

                sb->radius = radius;
                sb->slices = slices;
                sb->stacks = stacks;

                spherebone_list.push_back(sb);

            }
        }
    }

        fclose(fp);

}

void Piece::name_bone(char *bone_name, longbone* lb)
{

}

void Piece::name_bone(char *bone_name, spherebone* sb)
{
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


