#include <stdio.h>
#include <math.h>

#include "ascii.h"
#include "3D.h"
#include "control.h"
#include "colors.h"

#include "cube.h"

int main() {
    init();

    World world = init_world();
    
    add_body(&world, CUBE2_BODY(-5.0f, 0.0f, 0.0f, 10.0f), 12);
    add_body(&world, CUBE_BODY(50.0f, 0.0f, 0.0f, 10.0f), 12);
    add_body(&world, CUBE_BODY(150.0f, 0.0f, 0.0f, 10.0f), 12);
    add_body(&world, CUBE_BODY(10.0f, 10.0f, 0.0f, 5.0f), 12);
    add_body(&world, CUBE_BODY(10.0f, -15.0f, 0.0f, 12.0f), 12);
    
    Photo photo = init_photo(200.0f);
    
    Camera cam;
    cam.pos.x = -40.0f;
    cam.pos.y = 5.0f;
    cam.pos.z = 5.0f;
    cam.pos.dx = 1.0f;
    cam.pos.dy = 0.0f;
    cam.pos.dz = 0.0f;

    while (control_cam(&cam)) {
        take_photo(&photo, &cam, &world);
        draw(&photo, &cam);
    }

    close();

    return 0;
}

