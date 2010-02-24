#include "Model.cpp"

struct longbone
{
    int slices;
    Vertex center_point;
};

struct spherebone
{
    int slices, segments;
    Vertex center_point;
};

class Piece : public Model
{
    private:
    longbone *l_arm_upper, *l_arm_lower, *r_arm_upper, *r_arm_lower;
    spherebone *r_hand, *l_hand;
    longbone *l_femur, *l_shin, *l_foot, *r_femur, *r_shin, *r_foot;
    longbone *core; //all bone locations are based off this one
    spherebone *cranium_front, *cranium_back; //this is a dumb way to draw a head

    Model *held_obj; //the thing the mini is holding in right hand
    Model *shirt;
    Model *pants;

    Vertex location;
    
    public:
    Piece();
    ~Piece();

    void set_location(Vertex* loc);

    Vertex* get_location();
};

