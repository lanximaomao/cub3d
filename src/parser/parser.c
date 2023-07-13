#include "cub3D.h"

// define error code, 1 for malloc fail, 2 for wrong color, 3 for other validation error, 4 for function fail
// check for memory leak
// check for unclosed maps

static void get_direction(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (i < cub->input->map->size_y)
	{
		j = 0;
		while (j < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[i][j] == 'E')
				cub->input->map->direction = 0;
			else if (cub->input->map->matrix[i][j] == 'N')
				cub->input->map->direction = 90;
			else if (cub->input->map->matrix[i][j] == 'W')
				cub->input->map->direction = 180;
			else if (cub->input->map->matrix[i][j] == 'S')
				cub->input->map->direction = 270;
			j++;
		}
		i++;
	}
}

//line is a non null string
// first skip the space/tabs
// flag == 1, means north texture
// flag == 2, means south texture
// flag == 3, means west texture
// flag == 4, means east texture
// remember to change count;
// if things goes wrong, return -1;
// one exception to be added:  EA textures/simonkraft/wet_sponge.xpm    stillsomething
static int get_texture(t_cub *cub, char*line, int flag)
{
	int i;

	i = 0;
	if (ft_strncmp(cub->input->map->map_1d, "", 1)) // still something after map even after 6 parameters are given
		exit (1);
	if ((flag == 1 && cub->input->t_north) // duplicate texture definition // add error msg
		|| (flag == 2 && cub->input->t_south)
		|| (flag == 3 && cub->input->t_west)
		|| (flag == 4 && cub->input->t_east))
		exit (1);
	//check if file path is valid or not
	if (flag == 1)
		cub->input->t_north = ft_strtrim(line, "NO \n");
	else if (flag == 2)
		cub->input->t_south = ft_strtrim(line, "SO \n");
	else if (flag == 3)
		cub->input->t_west = ft_strtrim(line, "WE \n");
	else if (flag == 4)
		cub->input->t_east = ft_strtrim(line, "EA \n");
	cub->input->count++;
	return (0);
}

// Can player stand outside the wall?
static int line_processor(t_cub *cub, char* line)
{
	int i;

	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i] == ' ')
			i++;
	if (line[i] == '\n') // empty line, just return
		return (0);
	if (line[i] == 'N' && line[i+1] == 'O')
		get_texture(cub, line, 1);
	else if (line[i] == 'S' && line[i+1] == 'O')
		get_texture(cub, line, 2);
	else if (line[i] == 'W' && line[i+1] == 'E')
		get_texture(cub, line, 3);
	else if (line[i] == 'E' && line[i+1] == 'A')
		get_texture(cub, line, 4);
	else if (line[i] == 'F')
		get_color(cub, line, 1);
	else if (line[i] == 'C')
		get_color(cub, line, 2);
	else
		get_map(cub, line);
	return (0);
}

int parser(int fd, t_cub *cub)
{
	char* line;

	line = NULL;
	init_cub(cub);
	while (42)
	{
		line = get_next_line(fd); // to be freed // error catch?
		//printf("line=%s\n", line);
		if (!line)
		{
			printf("size of map is %d*%d\n", cub->input->map->size_y, cub->input->map->size_x);
			get_matrix(cub); // check here whether it is null
			get_direction(cub);
			return (0); // finish reading or not able to read?
		}
		if (line_processor(cub, line) == -1) 		//process each line
			exit (1); //
		free(line);
		line = NULL;
	}
	return (0);
}
