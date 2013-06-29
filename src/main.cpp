#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>

#include "timing.h"
#include "events.h"
#include "art.h"

void init_octree();
void draw_octree();

using namespace std;

SDL_PixelFormat fmt = {
  NULL,
  32,
  4,
  0,0,0,0,
  16,8,0,24,
  0xff0000, 0xff00, 0xff, 0xff000000,
  0,
  0
};

void load_cubemap(SDL_Surface ** cubemap) {
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    cubemap[0] = SDL_ConvertSurface(IMG_Load("img2/cubemap0.jpg"), &fmt, SDL_SWSURFACE);
    cubemap[1] = SDL_ConvertSurface(IMG_Load("img2/cubemap1.jpg"), &fmt, SDL_SWSURFACE);
    cubemap[2] = SDL_ConvertSurface(IMG_Load("img2/cubemap2.jpg"), &fmt, SDL_SWSURFACE);
    cubemap[3] = SDL_ConvertSurface(IMG_Load("img2/cubemap3.jpg"), &fmt, SDL_SWSURFACE);
    cubemap[4] = SDL_ConvertSurface(IMG_Load("img2/cubemap4.jpg"), &fmt, SDL_SWSURFACE);
    cubemap[5] = SDL_ConvertSurface(IMG_Load("img2/cubemap5.jpg"), &fmt, SDL_SWSURFACE);
}

SDL_Surface* create_surface(Uint32 flags,int width,int height) {
  return SDL_CreateRGBSurface(flags,width,height,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}

void create_cubemap(SDL_Surface ** cubemap, int size) {
    for (int i=0; i<6; i++) 
        cubemap[i] = create_surface(SDL_SWSURFACE, size, size);
}

void copy_cubemap(SDL_Surface ** src, SDL_Surface ** dest) {
    for (int i=0; i<6; i++) {
        assert(src[i]->w == dest[i]->w);
        assert(src[i]->h == dest[i]->h);
        memcpy(dest[i]->pixels, src[i]->pixels, 4*src[i]->w*src[i]->h);
    }
}


///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    init_screen("Voxel renderer");
    
    position = glm::dvec3(0, -1000000, 0);

    init_octree();
    
    //SDL_Surface * back[6];
    //load_cubemap(back);

    // mainloop
    while (!quit) {
        Timer t;
        if (moves) {
            draw_octree();
            flip_screen();
            
            glm::dvec3 eye(orientation[2]);
            //printf("%6.2f | %lf %lf %lf | %.3lf %.3lf %.3lf \n", t.elapsed(), 
            //       position.x,position.y,position.z, eye.x,eye.y,eye.z);
            fflush(stdout);
        }
        next_frame(t.elapsed());
        handle_events();
    }
    
    return 0;
}

// kate: space-indent on; indent-width 4; mixedindent off; indent-mode cstyle; 
