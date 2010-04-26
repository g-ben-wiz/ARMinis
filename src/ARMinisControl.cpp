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
    if (dragged_piece)
    {
        GLdouble mod_scr_x, mod_scr_y, mod_scr_z; 

        gluProject(dragged_piece->position.x, dragged_piece->position.y, dragged_piece->position.z, model, project, view, &mod_scr_x, &mod_scr_y, &mod_scr_z);

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
        /*if (screen_y - mod_scr_y <= -45.0  )
        {
            dragged_piece->position.z -= t->tile_len_z;
            return;
        }
        if (mod_scr_y - screen_y <= -45.0  )
        {
            dragged_piece->position.z += t->tile_len_z;
            return;
        }*/
    }

}

void ARMinisControl::drop()
{
    dragged_piece = NULL;
}
