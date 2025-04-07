# cub3D
![cub3d img](./img/cub3d.gif)

cub3D is a project inspired by the classic 90's game Wolfenstein 3D, aiming to create a dynamic 3D maze experience using ray-casting techniques. Developed in C, this project utilizes the [MLX42](https://github.com/codam-coding-college/MLX42) library for graphics rendering.

## Features

- **3D Rendering**: Implements ray-casting to render a 3D view from a 2D map.
- **Customizable Maps**: Supports external map files for flexible environment design.
- **Texture Mapping**: Applies textures to walls for a realistic appearance.
- **Player Navigation**: Allows movement and view adjustments within the maze.
- **Collision Detection**: Prevents movement through walls and enforces maze boundaries.

## Prerequisites

Ensure your system has the following installed:

- C compiler (e.g., `gcc`)
- CMake
- GLFW
- [MLX42](https://github.com/codam-coding-college/MLX42)

## Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/fclaus-g/cub3d.git
   cd cub3d
   ```

2. **Build the Project**:

   ```bash
   make
   ```

   This will compile the source files and produce the `cub3D` executable.

## Usage

To run the game with a specific map:

```bash
./cub3D path/to/map.cub
```

Replace `path/to/map.cub` with the path to your `.cub` map file.

## Controls

- `W`: Move forward  
- `S`: Move backward  
- `A`: Move left  
- `D`: Move right  
- `Left Arrow`: Turn left  
- `Right Arrow`: Turn right  
- `ESC`: Exit the game  

## Map File Format

Map files (`.cub`) define the layout and textures of the maze. A typical map file includes:

- **Textures**: Paths to texture images for walls, floor, and ceiling.
- **Colors**: RGB values for floor and ceiling colors.
- **Map Layout**: A grid representing walls (`1`), open spaces (`0`), and the player's starting position (`N`, `S`, `E`, `W`).

Example:

```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 225,30,0

111111
100101
102001
100001
111111
```

In this example:

- `NO`, `SO`, `WE`, `EA` specify the textures for the north, south, west, and east walls.
- `F` and `C` define the floor and ceiling colors in RGB format.
- The grid represents the map layout, where `1` is a wall, `0` is an open space, and `2` indicates the player's starting position facing north.

## Acknowledgments

This project is part of the curriculum at 42 School, designed to provide experience with graphics programming and deepen understanding of ray-casting techniques.
