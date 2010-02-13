#include "Model.h"

class Terrain
{
private:
	int tile_count_x, tile_count_z;
	int tile_len_x, tile_len_z;
	Vertex cell_centers[50][50];

public:
	Terrain();
    void load_data(char *filename);

    std::vector<GLfloat> vertices;

    //accessors, mutators
    void set_cell_center(int i, int j, Vertex *v);

    Vertex get_cell_center(int i, int j);
};
