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
    //for x
    //objPos += movement_x * scale * right_axis

    Vertex world_place;

    GLdouble mod_scr_x, mod_scr_y, mod_scr_z; 

    /* naw son:
    project dragged_piece's position to model.screen_x and model.screen_y
    if screen_x is less than dragged_piece.screen_x by 'a bunch' (trial/error)
     move_to model to go one x-tile less
    if screen_x is greater than model.screen_x by a bunch
     move_to model to go one x-tile more

    if screen_y is less than dragged_piece.screen_y by 'a bunch' (trial/error)
     move_to model to go one z-tile less
    if screen_y is greater than model.screen_y by a bunch
     move_to model to go one z-tile more
    */

    gluProject(dragged_piece->position.x, dragged_piece->position.y, dragged_piece->position.z, model, project, view, &mod_scr_x, &mod_scr_y, &mod_scr_z);

    //this only works if model is facing you
    //need to move to 'close to cursor' instead of 
    //adding or subtracting based one where cursor is

    if (screen_x - mod_scr_x <= -15.0)
        dragged_piece->position.x -= 25.0;

    if (mod_scr_x - screen_x <= -15.0)
        dragged_piece->position.x += 25.0;


    //move_to(dragged_piece, t, world_place.x, world_place.y, world_place.z);
}

void ARMinisControl::drop()
{
    dragged_piece = NULL;
}
