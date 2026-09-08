#include "graphics/ascii.h"
#include "graphics/colors.h"

#include "3D/engine.h"
#include "3D/control.h"

#include "3D/body/cube.h"

int main() {
    init_ascii();

    World world = init_world();
    
    add_body(&world, CUBE_BODY(-5.0f, 0.0f, 0.0f, 10.0f), 12);
    add_body(&world, CUBE_BODY(50.0f, 0.0f, 0.0f, 10.0f), 12);
    add_body(&world, CUBE_BODY(150.0f, 0.0f, 0.0f, 10.0f), 12);
    add_body(&world, CUBE_BODY(10.0f, 10.0f, 0.0f, 5.0f), 12);
    add_body(&world, CUBE_BODY(10.0f, -15.0f, 0.0f, 12.0f), 12);
    add_body(&world, CUBE_BODY(10.0f, -15.0f, 20.0f, 12.0f), 12);
    
    Photo photo = init_photo(ascii_w(), ascii_h());
    
    Camera cam = init_cam();
    cam.pos.x = -40.0f;
    cam.pos.y = 5.0f;
    cam.pos.z = 5.0f;
    cam.pos.dx = 1.0f;
    cam.pos.dy = 0.0f;
    cam.pos.dz = 0.0f;
    cam.pos.fov = 200.0f;

    while (control_cam(&cam)) {
        take_photo(&photo, &cam, &world);
        draw_ascii(&photo, &cam);
    }

    close_ascii();

    return 0;
}

