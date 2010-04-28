#include "ARMinisControl.h"

ARMinisControl::ARMinisControl()
{
    dragged_piece = NULL;
}

void ARMinisControl::move_to(Piece *p, Terrain *t, float x, float y, float z)
{
    //set x and z to coordinates that set piece location
    //to be in the middle of a tile
    x = (int)(x / t->tile_len_x);
    z = (int)(z / t->tile_len_z);

    Vertex cell_middle = t->get_cell_center(x, z); 

    //put the piece at that x & z
    p->position.x = cell_middle.x;
    p->position.y = cell_middle.y;
    p->position.z = cell_middle.z;

}

void ARMinisControl::start_drag(Piece *p)
{
    dragged_piece = p;
}

void ARMinisControl::drag(Terrain *t, float screen_x, float screen_y, GLdouble *model, GLdouble *project, GLint *view)
{
    int i, j;
    if (dragged_piece)
    {
        GLdouble mod_scr_x, mod_scr_y, mod_scr_z; 
        GLdouble world_mouse_pt_x, world_mouse_pt_y, world_mouse_pt_z;

        GLdouble tile_scr_x, tile_scr_y, tile_scr_z;
        int mod_tile_x = (int) dragged_piece->position.x / t->tile_len_x;
        int mod_tile_z = (int) dragged_piece->position.z / t->tile_len_z;

        Vertex tile_pxs, proj_tile_pxs;
        GLdouble tx, ty, tz;
//        Vertex mod_pxs = t->get_cell_center(mod_tile_x, mod_tile_z);
//        Vertex proj_mod_pxs  = t->get_cell_center(mod_tile_x, mod_tile_z);

        gluProject(dragged_piece->position.x, dragged_piece->position.y, dragged_piece->position.z, model, project, view, &mod_scr_x, &mod_scr_y, &mod_scr_z);
        mod_scr_y = double (view[3] - mod_scr_y - 1);

/*
        gluUnProject((GLdouble) screen_x, (GLdouble) screen_y, dragged_piece->position.z, model, project, view, &world_mouse_pt_x, &world_mouse_pt_y, &world_mouse_pt_z);
        world_mouse_pt_y = double (view[3] - world_mouse_pt_y - 1);

        dragged_piece->position.x = world_mouse_pt_x;
*/
/*
        for (j = 0; j < t->tile_count_z; j++)
            for (i = 0; i < t->tile_count_x; i++)
            {
                tile_pxs = t->get_cell_center(i, j);

                gluProject(tile_pxs.x, tile_pxs.y, tile_pxs.z, model, project, view, &tx, &ty, &tz);
                proj_tile_pxs.x = tx;  
                proj_tile_pxs.y = ty;  
                proj_tile_pxs.z = tz;  

                if (abs (screen_x - proj_tile_pxs.x) <= 15)  
                {
                    dragged_piece->position.x -= 1;
                    //move_to(dragged_piece, t, tile_pxs.x, tile_pxs.y, tile_pxs.z);
                    //move_to(dragged_piece, t, dragged_piece->position.x, dragged_piece->position.y, dragged_piece->position.z);
                } 
            }*/
                 


        //these blocks work if cam is facing piece's face
        //for being behind piece or on its sides it will be different
        if (screen_x - mod_scr_x <= -t->tile_len_x  )
        {
            dragged_piece->position.x -= t->tile_len_x;
            return;
        }
        if (mod_scr_x - screen_x <= -t->tile_len_x  )
        {
            dragged_piece->position.x += t->tile_len_x;
            return;
        }
     
        if (screen_y - mod_scr_y <= -105.0  )
        {
            dragged_piece->position.z -= t->tile_len_z;
            return;
        }
        if (mod_scr_y - screen_y <= -15.0  )
        {
            dragged_piece->position.z += t->tile_len_z;
            return;
        }
    }

}

void ARMinisControl::drop()
{
    dragged_piece = NULL;
}
