#include "cub3D.h"

void	display_map(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	printf("\n\nmap matrix:\n\n");
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			//if (matrix[i][j] == ' ')
			//	matrix[i][j] = '_';
			printf("%c", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	display_texture(t_input *input)
{
	printf("\n\nt_north=%s\n", input->t_north);
	printf("t_south=%s\n", input->t_south);
	printf("t_west=%s\n", input->t_west);
	printf("t_east=%s\n\n", input->t_east);
}

void	display_color(t_input *input)
{
	int	i;

	i = 0;
	printf("floor color = %d, %d, %d\n", input->color_f->r, input->color_f->g,
			input->color_f->b);
	printf("ceiling color = %d, %d, %d\n", input->color_c->r, input->color_c->g,
			input->color_c->b);
}
