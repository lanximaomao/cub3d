#include "cub3D.h"

// make a perfect cubic map by filling the irregular shapes with _
// size_x and size_y
// which way the player is facing.
// check for memory leak

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
	if (cub->input->map->direction != 0)
		printf("\n\ndirection=%d\n\n", cub->input->map->direction);
}

static void display_map(char **matrix)
{
	int i;
	int j;

	i = 0;
	printf("\n\nmap matrix:\n\n");
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == ' ')
				matrix[i][j] = '_';
			printf("%c", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

static void display_texture(t_input *input)
{
	printf("\n\nt_north=%s\n", input->t_north);
	printf("t_south=%s\n", input->t_south);
	printf("t_west=%s\n", input->t_west);
	printf("t_east=%s\n\n", input->t_east);
}

static void display_color(t_input *input)
{
	int i;

	i = 0;
	printf("floor color = %d, %d, %d\n", input->color_f->r, input->color_f->g, input->color_f->b);
	printf("ceiling color = %d, %d, %d\n", input->color_c->r, input->color_c->g, input->color_c->b);
}

static int valid_char(char* str)
{
	int i;
	int player_flag;

	i = 0;
	player_flag = 0;
	while (str[i])
	{
		printf("%c", str[i]);
		if (str[i] != '\n' && str[i] != '0' && str[i] != '1' &&  str[i] != ' ')
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W'|| str[i] == 'E' )
				player_flag++;
			else
				return (-1);
		}
		i++;
	}
	if (player_flag != 1)
		return (-1);
	return (0);
}

// direction
static int get_matrix(t_cub *cub)
{
	int i;
	int j;
	char **tmp_matrix;

	i = 0;
	if (!cub->input->map->map_1d || valid_char(cub->input->map->map_1d) == -1)
		exit (1);
	tmp_matrix = ft_split(cub->input->map->map_1d, '\n'); // to be freed
	if (!tmp_matrix)
		exit(1);
	cub->input->map->matrix = ft_calloc(sizeof(char *), cub->input->map->size_y + 1);
	cub->input->map->matrix[cub->input->map->size_y] = NULL;
	while (i < cub->input->map->size_y)
	{
		cub->input->map->matrix[i] = ft_calloc(sizeof(char), cub->input->map->size_x + 1);
		if (!cub->input->map->matrix[i])
			exit(1);
		cub->input->map->matrix[i][cub->input->map->size_x] = '\0';
		i++;
	}
	i = 0;
	while (i < cub->input->map->size_y)
	{
		j = 0;
		while (j < cub->input->map->size_x)
		{
			if (j >= ft_strlen(tmp_matrix[i]))
				cub->input->map->matrix[i][j] = '_';
			else if (tmp_matrix[i][j] == ' ')
				cub->input->map->matrix[i][j] = '_';
			else
				cub->input->map->matrix[i][j] = tmp_matrix[i][j];
			j++;
		}
		i++;
	}
	display_map(cub->input->map->matrix);
	display_texture(cub->input);
	display_color(cub->input);
	return (0);
}

static int	get_map_x(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	return (len);
}

static int get_map(t_cub *cub, char* line)
{
	// check out whether at this point all the necessary parameters are passed.
	if (cub->input->count != 6)
		return (-1); // map errpr

	// check for unclosed maps

	// calculate size_x of map
	if ((int)ft_strlen(line) > cub->input->map->size_x)
		cub->input->map->size_x = get_map_x(line);
	cub->input->map->size_y += 1; 	// calculate size_y of the map
	// parsing
	cub->input->map->map_1d = ft_strjoin_gnl(cub->input->map->map_1d, line); // if null
	if (!cub->input->map->map_1d)
		exit (1); // update to error msg
	//printf("1d=%s\n\n\n", cub->input->map->map_1d);
	return (0);
}

static int	ft_atoi_isnum(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0' && (*str < 9 || *str > 13))
		return (-1);
	if (result * sign >= 0 && result * sign <= 255)
		return (result * sign);
	return (-1);
}

static int how_many(char* str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

static void	free_char(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}
// 1 for F, 2 for c
static int get_color(t_cub *cub, char* line, int flag)
{
	char *line_with_color;
	char **color_split;
	t_color_rgb *color;

	if (ft_strncmp(cub->input->map->map_1d, "", 1)) // still something after map even after 6 parameters are given
		exit (1);
	if ((flag == 1 && cub->input->color_f) // duplicate color definition // add error msg
		|| (flag == 2 && cub->input->color_c))
		exit (1);
	if (how_many(line, ',') != 2) // check number of semicolons;
		exit (1);
	if(flag == 1)
		line_with_color = ft_strtrim(line, "F \n"); // to be freed
	if (flag == 2)
		line_with_color = ft_strtrim(line, "C \n"); // to be freed
	if (!line_with_color)
		exit(1);
	color_split = ft_split(line_with_color, ','); // to be freed
	if (!color_split)
		exit(1);
	color = ft_calloc(sizeof(t_color_rgb), 1);
	if (!color)
		exit(1);
	if (flag == 1)
		cub->input->color_f = color;
	if (flag == 2)
		cub->input->color_c = color;
	color->r = ft_atoi_isnum(color_split[0]);
	color->g = ft_atoi_isnum(color_split[1]);
	color->b = ft_atoi_isnum(color_split[2]);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		exit(1);
	free(line_with_color);
	free_char(color_split);
	cub->input->count++;
	return (0);
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

static int line_processor(t_cub *cub, char* line)
{
	int i;

	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i] == ' ')
			i++;
	if (line[i+1] && line[i+1] == '\n') // empty line, just return
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

static void init_map(t_map *map)
{
	map->size_x = 0;
	map->size_y = 0;
	map->direction = 0;
	map->matrix = NULL;
	map->map_1d = ft_strdup(""); // to be freed
	if (!map->map_1d)
		exit(1);
}

static void init_input(t_input *input)
{
	input->count = 0;
	input->t_north = NULL;
	input->t_south = NULL;
	input->t_west = NULL;
	input->t_east = NULL;
	input->color_c = NULL;
	input->color_f = NULL;
	input->position->x_p = -1;
	input->position->y_p = -1;
	init_map(input->map);
}

// to be fix: change exit(1) to clean_exit function
static void init_cub(t_cub *cub)
{
	cub->img = ft_calloc(sizeof(t_img), 1);
	if (!cub->img)
		exit(1);
	cub->var = ft_calloc(sizeof(t_vars), 1);
	if (!cub->var)
		exit(1);
	cub->input = ft_calloc(sizeof(t_input), 1);
	if (!cub->input)
		exit(1);
	cub->input->map = ft_calloc(sizeof(t_map), 1);
	if (!cub->input->map)
		exit(1);
	cub->input->position = ft_calloc(sizeof(t_position), 1);
	if (!cub->input->position)
		exit(1);
	init_input(cub->input);
}


int parser(int fd, t_cub *cub)
{
	char* line;

	line = NULL;
	init_cub(cub);
	while (42)
	{
		line = get_next_line(fd); // to be freed // error catch?
		if (!line)
		{
			printf("size of map is %d*%d\n", cub->input->map->size_x, cub->input->map->size_y);
			get_matrix(cub); // check here whether it is null
			get_direction(cub);
			return (0); // finish reading or not able to read?
		}
		//process each line
		if (line_processor(cub, line) == -1)
			exit (1); //
		free(line);
		line = NULL;
	}
	return (0);
}
