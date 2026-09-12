//////////////////////////////////////////
////[ ASCII3D ]///////////////////////////
//////////////////[ Author: Micha Wu ]////
//////////////////////////////////////////

#include "graphics/ascii.h"
#include "graphics/color.h"

#include "3D/engine.h"
#include "3D/control.h"

int main() {
    init_ascii();

    World world = init_world();

    add_body(world, quad_body(&world,
        (P){0.0f, 0.0f, -5.0f}, (P){500.0f, -0.0f, -5.0f},
        (P){0.0f, 30.0f, -5.0f}, (P){500.0f, -10.0f, -5.0f}, WHITE, 0
    ));
    add_body(world, quad_body(&world,
        (P){0.0f, 0.0f, 15.0f}, (P){500.0f, -0.0f, 15.0f},
        (P){0.0f, 30.0f, 15.0f}, (P){500.0f, -10.0f, 15.0f}, GREEN, 0
    ));
    add_body(world, cube_body(&world, (P){0.0f, 20.0f, 0.0f}, 10.0f));
    add_body(world, cube_body(&world, (P){-50.0f, -10.0f, -50.0f}, 50.0f));
    
    Photo photo = init_photo(ascii_w(), ascii_h());
    
    Camera cam = init_cam();
    cam.pos.pos.x = 52.0f;
    cam.pos.pos.y = 10.0f;
    cam.pos.pos.z = 36.0f;
    cam.pos.dir.x = 0.8f;
    cam.pos.dir.y = 0.0f;
    cam.pos.dir.z = -0.2f;
    cam.pos.fov = 200.0f;

    while (control_cam(&cam)) {
        take_photo(&photo, &cam, &world);
        draw_ascii(&photo, &cam);
    }

    close_ascii();

    return 0;
}

