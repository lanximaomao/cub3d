#include "../includes/cub3D.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"
#include "../includes/color.h"

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
	printf("floor color:");
	while (i < 3)
	{
		printf("%d ", input->color_f[i]);
		i++;
	}
	printf("\n");
	i = 0;
	printf("ceiling color:");
	while (i < 3)
	{
		printf("%d ", input->color_c[i]);
		i++;
	}
	printf("\n");
}

static int get_matrix(t_cub *cub)
{
	int i;

	i = 0;
	if (!cub->input->map->map_1d)
		return (-1);
	//printf("1D map = %s\n", cub->input->map->map_1d);
	//printf(COLOR_BLUE "size_x=%d\n" COLOR_RESET, cub->input->map->size_x);
	//printf(COLOR_BLUE "size_y=%d\n" COLOR_RESET, cub->input->map->size_y);
	cub->input->map->matrix = ft_split(cub->input->map->map_1d, '\n');
	if (!cub->input->map->matrix)
		exit(1); // malloc fail
	display_map(cub->input->map->matrix);
	display_texture(cub->input);
	display_color(cub->input);
	return (0);
}
// note: change map structure; add one more function into libft which is needed by gnl
//cub->input->map->matrix needs malloc
// size_x includes the new line character

static int get_map(t_cub *cub, char* line)
{
	// check out whether at this point all the necessary parameters are passed.
	if (cub->input->count != 6)
		return (-1); // map errpr
	// only 6 chars

	// check for unclosed maps

	// calculate size_x of map
	if ((int)ft_strlen(line) > cub->input->map->size_x)
		cub->input->map->size_x = ft_strlen(line);
	//printf("count=%d\n", cub->input->count);
	//printf("size_x=%d\n", cub->input->map->size_x);
	// calculate size_y of the map
	cub->input->map->size_y += 1;
	// parsing
	cub->input->map->map_1d = ft_strjoin_gnl(cub->input->map->map_1d, line); // if null
	if (!cub->input->map->map_1d)
		return (-1);
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

// flag -1 means floor, flag 1 means ceiling
// remember to change count;
// if things goes wrong, return -1;
static int get_color_c(t_cub *cub, char* line)
{
	int i;
	char** split_c;

	i = 2;
	//if ((flag == -1 && cub->input->color_f)
	//	|| (flag == 1 && cub->input->color_c))
	//	return (-1); // duplicate color definition
	cub->input->color_c = malloc(sizeof(int) * 3);
	if (!cub->input->color_c)
		exit(1);
	//split
	while (line[i] >= 9 && line[i] <= 13)//skil white spaces
		i++;
	line += i;
	if (line[i])
	{
		split_c = ft_split(line, ',');
		if (!split_c)
			return (-1);
	}
	else
		return (-1);
	i = 0;
	while (i < 3)
	{
		if (split_c[i])
		{
			cub->input->color_c[i] = ft_atoi_isnum(split_c[i]);
			if (cub->input->color_c[i] == -1)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	if (split_c[i]) // more than three color
		return (-1);
	return (0);
}

static int get_color_f(t_cub *cub, char* line)
{
	int i;
	char** split_f;

	i = 2;
	//if ((flag == -1 && cub->input->color_f)
	//	|| (flag == 1 && cub->input->color_c))
	//	return (-1); // duplicate color definition
	cub->input->color_f = malloc(sizeof(int) * 3);
	if (!cub->input->color_f)
		exit(1);
	//split
	while (line[i] >= 9 && line[i] <= 13)//skil white spaces
		i++;
	line += i;
	if (line[i])
	{
		split_f = ft_split(line, ',');
		if (!split_f)
			return (-1);
	}
	else
		return (-1);
	i = 0;
	while (i < 3)
	{
		if (split_f[i])
		{
			cub->input->color_f[i] = ft_atoi_isnum(split_f[i]);
			if (cub->input->color_f[i] == -1)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	if (split_f[i]) // more than three color
		return (-1);
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
	char *texture;

	i = 3;
	texture = NULL;
	if ((flag == 1 && cub->input->t_north)
		|| (flag == 2 && cub->input->t_south)
		|| (flag == 3 && cub->input->t_west)
		|| (flag == 4 && cub->input->t_east))
		return (-1); // duplicate texture definition
	while (line[i] >= 9 && line[i] <= 13)//skil white spaces
		i++;
	line += i;
	i = 0;
	while (line[i] < 9 || line[i] > 13)
		i++;
	texture = malloc(sizeof(char) * (i + 1));
	if (!texture)
		exit(-1);
	i = 0;
	while (line[i])
	{
		texture[i] = line[i];
		i++;
		if (line[i]>= 9 && line[i] <= 13)
			break;
	}
	texture[i] = '\0';
	//check if file path is valid or not
	if (flag == 1)
		cub->input->t_north = texture;
	else if (flag == 2)
		cub->input->t_south = texture;
	else if (flag == 3)
		cub->input->t_west = texture;
	else if (flag == 4)
		cub->input->t_east = texture;
	//printf("texture=%s\n", texture);
	return (0);
}

static int line_processor(t_cub *cub, char* line)
{
	int i;

	i = 0;
	//printf(COLOR_RED "line=%s\n" COLOR_RESET, line);
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	if (!line[i+1]) // empty line, just return
		return (0);
	if (line[i] == 'N' && line[i+1] == 'O')
	{
		if (get_texture(cub, line, 1) == -1)
			return (-1);
	}
	else if (line[i] == 'S' && line[i+1] == 'O')
	{
		if (get_texture(cub, line, 2) == -1)
			return (-1);
	}
	else if (line[i] == 'W' && line[i+1] == 'E')
	{
		if (get_texture(cub, line, 3) == -1)
			return (-1);
	}
	else if (line[i] == 'E' && line[i+1] == 'A')
	{
		if (get_texture(cub, line, 4) == -1)
			return (-1);
	}
	else if (line[i] == 'F')
	{
		if (get_color_f(cub, line) == -1)
			return (-1);
	}
	else if (line[i] == 'C')
	{
		if (get_color_c(cub, line) == -1)
			return (-1);
	}
	else if (get_map(cub, line) == -1)
		return (-1); // if this returns -1;
	return (0);
}

static void init_input(t_input *input)
{
	input->count = 6;
	input->color_f = NULL;
	input->color_c = NULL;
	input->t_north = NULL;
	input->t_south = NULL;
	input->t_west = NULL;
	input->t_east = NULL;
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
// pls also add map init
int parser(int fd, t_cub *cub)
{
	t_map map;
	t_input input;

	char* line;
	line = NULL;
	init_input(&input);
	init_map(&map);
	cub->input = &input;
	cub->input->map = &map;
	while (42)
	{
		line = get_next_line(fd); // to be freed // error catch?
		if (!line)
		{
			get_matrix(cub); // check here whether it is null
			return (0); // finish reading or not able to read?
		}
		//process each line
		if (line_processor(cub, line) == -1)
			return (-1);
		free(line);
		line = NULL;
	}
	return (0);
}
