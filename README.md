# cub3D - My first RayCaster with miniLibX

## Description

cub3D creates a “realistic” 3D graphical representation of the inside of a maze from a first-person perspective using the Ray-Casting and 42 school's own graphic library miniLibX.

## Language Used

[![Language Used](https://skills.thijs.gg/icons?i=c)](https://skills.thijs.gg)

## Install and Run

**1. Compilation:**

To compile the program, run the following command:

**2. Running the Program:**

	make

**3. Run programme:**

The program takes a map in format of *.cub as argument:
	`map.cub`

An example of map loos like this:

	F 76,76,76
	C 99,99,99

	NO textures/simonkraft/cobblestone.xpm
	SO textures/simonkraft/cobblestone_01.xpm
	WE textures/simonkraft/mossy_cobblestone1.xpm
	EA textures/simonkraft/cobblestone_02.xpm

	1111111111111111111
	10W1001001001000001
	1011000001000001001
	1001001001111101111
	1001111000001001001
	1000000000000001001
	1001111111111001001
	1111000000000001011
	1000000001000000001
	1111111111111111111

Use the following command format to run the program:

	./cub3d map.cub

## External resources

+ [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
+ [Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
+ [Flood fill algorithm](https://en.wikipedia.org/wiki/Flood_fill)
+ [MiniLibX documentation by Gontjarow](https://gontjarow.github.io/MiniLibX/)
+ [MiniLibX documentation by Harm Smits](https://harm-smits.github.io/42docs/)
+ [42docs](https://harm-smits.github.io/42docs/projects/cub3d)
