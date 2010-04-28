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
    int flip_coeff;

    if (dragged_piece)
    {
        GLdouble mod_scr_x, mod_scr_y, mod_scr_z; 

        gluProject(dragged_piece->position.x, dragged_piece->position.y, dragged_piece->position.z, model, project, view, &mod_scr_x, &mod_scr_y, &mod_scr_z);
        mod_scr_y = double (view[3] - mod_scr_y - 1);


        if (this->view->cam.eye_z >= dragged_piece->position.z)            
            flip_coeff = 1;
        else
            flip_coeff = -1;

        if (screen_x - mod_scr_x <= -t->tile_len_x )
        {
            dragged_piece->position.x -= t->tile_len_x * flip_coeff;
//            board_govern(t);
            return;
        }
        if (mod_scr_x - screen_x <= -t->tile_len_x  )
        {
            dragged_piece->position.x += t->tile_len_x * flip_coeff;
//           board_govern(t);
            return;
        }
     
        if (screen_y - mod_scr_y <= -105.0  )
        {
            dragged_piece->position.z -= t->tile_len_z * flip_coeff;
//            board_govern(t);
            return;
        }
        if (mod_scr_y - screen_y <= -15.0  )
        {
            dragged_piece->position.z += t->tile_len_z * flip_coeff;
//           board_govern(t);
            return;
        }

    }

}

void ARMinisControl::drop()
{
    dragged_piece = NULL;
}

void ARMinisControl::board_govern(Terrain *t)
{
    int max_x = t->tile_count_x;
    int max_z = t->tile_count_z;

    if (dragged_piece->position.x < t->get_cell_center(0, 0).x)
        dragged_piece->position.x = t->get_cell_center(0, 0).x;
    if (dragged_piece->position.z < t->get_cell_center(0, 0).z)
        dragged_piece->position.z = t->get_cell_center(0, 0).z;

    if (dragged_piece->position.x > t->get_cell_center(max_x, 0).x)
        dragged_piece->position.x = t->get_cell_center(max_x, 0).x;
    if (dragged_piece->position.z > t->get_cell_center(0, max_z).z)
        dragged_piece->position.z = t->get_cell_center(0, max_z).z;
}

void ARMinisControl::set_view(ARMinisView *v)
{
    this->view = v;
}
