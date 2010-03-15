#include "Model.cpp"
#include "string.h"

struct longbone
{
    Vertex center_point;
    float rot_angle;
    float rot_x, rot_y, rot_z;
    float rgb_r, rgb_g, rgb_b;
    float radius_top, radius_bottom;
    float length;
    int slices;
    int stacks;
};

struct spherebone
{
    Vertex center_point;
    float rot_angle;
    float rot_x, rot_y, rot_z;
    float rgb_r, rgb_g, rgb_b;
    float radius;
    int slices;
    int stacks;
};

class Piece : public Model
{
    private:
    longbone *l_arm_upper, *l_arm_lower, *r_arm_upper, *r_arm_lower;
    spherebone *r_hand, *l_hand;
    longbone *l_femur, *l_shin, *l_foot, *r_femur, *r_shin, *r_foot;
    longbone *core; //all bone locations are based off this one
    spherebone *skull; //this is a dumb way to draw a head
    longbone *face;
    float neck_length;// not a whole bone b/c no point at this stage

    Model *held_obj; //the thing the mini is holding in right hand
    Model *shirt;
    Model *pants;
    
    public:
    Piece();
    ~Piece();
    void load_data(char *filename);
    void name_bone(char *bone_name, longbone* lb);
    void name_bone(char *bone_name, spherebone* sb);
    std::vector<longbone*> longbone_list;
    std::vector<spherebone*> spherebone_list;

    void set_l_arm_upper(longbone* bone);
    void set_l_arm_lower(longbone* bone);
    void set_r_arm_upper(longbone* bone);
    void set_r_arm_lower(longbone* bone);
    void set_l_hand(spherebone* bone);
    void set_r_hand(spherebone* bone);
    void set_skull(spherebone* bone);

    void set_l_femur(longbone* bone);
    void set_l_shin(longbone* bone);
    void set_l_foot(longbone* bone);
    void set_r_femur(longbone* bone);
    void set_r_shin(longbone* bone);
    void set_r_foot(longbone* bone);
    void set_core(longbone* bone);
    void set_face(longbone* bone);

    Vertex* get_location();
    longbone* get_l_arm_upper();
    longbone* get_l_arm_lower();
    longbone* get_r_arm_upper();
    longbone* get_r_arm_lower();
    spherebone* get_l_hand();
    spherebone* get_r_hand();
    spherebone* get_skull();

    longbone* get_l_femur();
    longbone* get_l_shin();
    longbone* get_l_foot();
    longbone* get_r_femur();
    longbone* get_r_shin();
    longbone* get_r_foot();
    longbone* get_core();
    longbone* get_face();
};

