#include <stdio.h>

#include "ascii.h"
#include "3D.h"
#include "control.h"
#include "colors.h"

int main() {
    init();

    World world = init_world();
    
    add_body(&world, CUBE_BODY(-5.0f, 0.0f, 0.0f, 10.0f), 12);
    
    Photo photo = init_photo(1.0f);
    
    Camera cam;
    cam.x = -7.0f;
    cam.y = 5.0f;
    cam.z = 5.0f;
    cam.dx = 1.0f;
    cam.dy = 0.0f;
    cam.dz = 0.0f;
    
    while (control_cam(&cam)) {
        take_photo(&photo, &cam, &world);
        draw(&photo);
    }

    close();

    return 0;
}

