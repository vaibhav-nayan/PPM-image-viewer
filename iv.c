#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

  // ---------------- Reading The File -------------------------
  // FORMAT OF HEADER OF A PPM IMAGE FILE
  /*
      P3         <--  Magic Number : P3 for Ascii & P6 for Binary
      # feep.ppm <-- Comment for the image
      4 4        <-- Dimensions of the image
      15         <-- Maximum color value for the image (typically 255)
      // image data begins containing (r, g, b) value for each pixel
      0  0  0    0  0  0    0  0  0   15  0 15
      0  0  0    0 15  7    0  0  0    0  0  0
      0  0  0    0  0  0    0 15  7    0  0  0
      15  0 15    0  0  0    0  0  0    0  0  0
  */

  // Step-1 : Import the image file
  FILE *in = stdin;

  // Step-2 : Define some variables to read the ppm file
  char *pthroway = calloc(1000, sizeof(char));
  char *pdimensions = calloc(1000, sizeof(char));

  // Step-3 : Read first line (specifier P3 or P6) and second line (comment)
  /*
      * These values are not useful for us, as we aim to specifically
        read for binary file type and ignore the comment
  */
  fgets(pthroway, 1000, in);
  fgets(pthroway, 1000, in);

  // Step-4 : Read third line (dimensions: width, height)
  /*
      * This information is useful to determine the window size and
        for rendering purpose
  */
  fgets(pdimensions, 1000, in);

  // Step-5 : Read the fourth line (maximum color value : defaults to 255)
  // (not useful for us)
  fgets(pthroway, 1000, in);

  // Step-6 : Parse the string read from the file to determine the dimensions
  int width;
  int height;
  sscanf(pdimensions, "%d %d\n", &width, &height);

  // Step-7 : free the variables
  free(pdimensions);
  free(pthroway);

  // -----------------------------------------------------------

  // --------------- Creating The Window -----------------------

  // Step-1 : Create a window pointer with the determined width, height
  SDL_Window *pwindow =
      SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, width, height, 0);

  // Step-2 : Extract the surface of window to render the image in that
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  // ------------------------------------------------------------

  // ---------------- Rendering the Image -----------------------

  // Step-1 : Initialize the color variable , pixel variable
  /*
      * Color : would store the color value in an Uint32 format
      * pixel : would store a pixel(rectangle) at a specific (x,y)
                of a specific color determined by the color variable
  */
  Uint32 color = 0;
  SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};

  // Step-2 : get value of (r,g,b) for each pixel and render it
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Uint8 r, g, b;
      r = (char)getchar();
      g = (char)getchar();
      b = (char)getchar();
      color = SDL_MapRGB(psurface->format, r, g, b);
      pixel.x = x;
      pixel.y = y;
      SDL_FillRect(psurface, &pixel, color);
    }
  }

  // Step-3 : Tell the window to update its surface according to the render
  SDL_UpdateWindowSurface(pwindow);

  // --------------------------------------------------------------

  // ----------------- Keeping the window open --------------------

  // Step-1 : Initialize a is_running variable
  int app_is_running = 1;

  // Step-2 : Infinite loop and keep polling event until a "QUIT" event is
  // occured
  while (app_is_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_is_running = 0;
      }
    }
    SDL_Delay(100);
  }
  // ----------------------------------------------------------------
}

// Compile Command : gcc -Wall -Wextra -g -o iv iv.c `sdl2-config --cflags
// --libs` Run Command : cat image_file.ppm | ./iv;
