# PPM Image Viewer (SDL2)

This project implements a simple image viewer for **binary PPM (P6)** image files using **SDL2**. It reads a P6-formatted PPM image from standard input, creates an SDL window matching the image dimensions, and renders the image pixel-by-pixel onto the window surface.

## Features
- Supports **PPM P6 (binary)** format.
- Parses image header (magic number, comment, dimensions, max value).
- Reads raw RGB triplets directly from stdin.
- Renders the image using SDL2 surfaces.
- Displays the image until the user closes the window.

## PPM Format Support

Supported P6 PPM structure:

```
P6
# optional comment
WIDTH HEIGHT
MAXVAL
<raw RGB byte stream>
```

Each pixel is three bytes: `R G B`  
Only `MAXVAL = 255` is supported.

## How It Works

1. Reads magic number (`P6`) and one comment line.
2. Reads `width` and `height`.
3. Reads maximum color value.
4. Creates an SDL window and obtains its surface.
5. Reads each RGB triplet and maps it to a surface pixel.
6. Updates the window and waits for a quit event.

## Build Instructions

### Dependencies
- GCC or Clang
- SDL2 development files
- `sdl2-config` available in `PATH`

### Compile

```sh
gcc -Wall -Wextra -g -o iv iv.c `sdl2-config --cflags --libs`
```

## Run

```sh
cat image.ppm | ./iv
```

or:

```sh
./iv < image.ppm
```

The file must be a valid **P6** PPM image.

## Example P6 Format

```
P6
# example
4 4
255
<48 raw RGB bytes>
```

## Limitations
- Only supports 8‑bit maxval (`255`).
- Only P6 (binary) PPM.
- Assumes exactly one header comment line.
- Uses SDL surface rendering (no GPU acceleration).

## References
- [SDL2 Docs](https://wiki.libsdl.org/SDL2/FrontPage)
- [PPM Format Doc](https://netpbm.sourceforge.net/doc/ppm.html)
- [Input and Parsing in C](https://stackoverflow.com/questions/22330969/using-fscanf-vs-fgets-and-sscanf)

## License
Not Licensed
