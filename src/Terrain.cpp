#include "Terrain.h"

Terrain::Terrain()
{
	tile_count_x = 50;
	tile_count_z = 50;

	tile_len_x = 30.0;
	tile_len_z = 30.0;

	int row, column = 0;

	for (column = 0; column < tile_count_x; column++)
		for (row = 0; row < tile_count_z; row++)
		{
			cell_centers[row][column].x = 15 + tile_len_x * column;
			cell_centers[row][column].z = 15 + tile_len_z * row;
			cell_centers[row][column].y = 0.0;
			cell_centers[row][column].w = 1.0;
		}
}

void Terrain::load_data(char *filename)
{
    int i, k;
    int c_i, c_j;
    float max, sum;
    float x, y, z, w;
    Vertex quad_vertex[4]; //4 corners of 1 tile
    FILE *fp = fopen(filename, "r");

    while( fscanf(fp, "%f %f %f %f", &x, &y, &z, &w) == 4)
    {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        vertices.push_back(w);
    }

    k = vertices.size() - 1; 
    printf("%d\n", vertices.size());

    tile_count_x = 50;
    tile_count_z = 50;

    for (c_j = 0; c_j < tile_count_x; c_j++)
        for (c_i = 0; c_i < tile_count_z; c_i++) 
        {

            for (i = 0; i < 4; i++)
            {
                quad_vertex[i].w = vertices[k--];
                quad_vertex[i].z = vertices[k--];
                quad_vertex[i].y = vertices[k--];
                quad_vertex[i].x = vertices[k--];
            }

            max = quad_vertex[0].y; //arbitrary initial val
            
            for (i = 0; i < 4; i++)
                if (quad_vertex[i].y > max) 
                    max = quad_vertex[i].y;
                                       
            cell_centers[c_i][c_j].y = max; 
            
            sum = 0.0;
            for (i = 0; i < 4; i++)
                sum += quad_vertex[i].x;

            cell_centers[c_i][c_j].x = sum/4.0;

            sum = 0.0;
            for (i = 0; i < 4; i++)
                sum += quad_vertex[i].z;

            cell_centers[c_i][c_j].z = sum/4.0;

        } 
    
    fclose(fp);

//    vertices.clear();
}

//accessors & mutators

void Terrain::set_cell_center(int i, int j, Vertex *v)
{
    cell_centers[i][j] = *v;
}

Vertex Terrain::get_cell_center(int i, int j)
{
    return cell_centers[i][j];
}
