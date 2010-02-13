#include <stdio.h>

int main()
{
    int i, j;

    FILE *fp;
    fp = fopen("../terrain/dwarven-ruin.map", "w");

    float x, y, z, w;
    float x_center, z_center;
    float tile_size = 30.0;
    
    w = 1.0; 

    //do all x's across same z
    //repeat for each z

    //the first 50 x's will all be at 
    //z = -750 -> -720


    //print varying x, same y, same z, same w, newline

    for (j = 0; j < 50; j++)
        for (i = 0; i < 50; i++)
        {
            y = 5.0;
            w = 1.0;

            z_center = -735.0 + (j * (tile_size + 5.0));

            x_center = -735.0 + (i * (tile_size + 5.0));

            //bottom left
            fprintf(fp, "%.1f %.1f %.1f %.1f\n", 
                x_center - tile_size/2, y, z_center - tile_size/2, w);

            //bottom right
            fprintf(fp, "%.1f %.1f %.1f %.1f\n", 
                x_center + tile_size/2, y, z_center - tile_size/2, w);

            //top right
            fprintf(fp, "%.1f %.1f %.1f %.1f\n", 
                x_center + tile_size/2, y, z_center + tile_size/2, w);

            //top left
            fprintf(fp, "%.1f %.1f %.1f %.1f\n", 
                x_center - tile_size/2, y, z_center + tile_size/2, w);
        }


        fclose(fp);
        return 0;
    }
