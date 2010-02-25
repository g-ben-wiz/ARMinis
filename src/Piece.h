#include "Model.cpp"

struct longbone
{
    int slices;
    float radius;
    float length;
    Vertex center_point;
};

struct spherebone
{
    int slices, segments;
    float radius;
    Vertex center_point;
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

    Vertex location;
    
    public:
    Piece();
    ~Piece();

    void set_location(Vertex* loc);
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

