#include <math.h>
#include <stdio.h>

typedef struct
{
	float	x;
	float	y;
}			Point2D;

typedef struct
{
	Point2D	position;
	float direction; // Angle in degrees
}			Ray;

typedef struct
{
	Point2D	position;
	float	width;
	float	height;
}			Rectangle;

int	raycast(Ray ray, Rectangle rectangle)
{
	float	xMin;
	float	xMax;
	float	yMin;
	float	yMax;
	float	angleRad;
	float	dx;
	float	dy;
	int		stepX;
	int		stepY;
	float	deltaX;
	float	deltaY;
	float	xDist;
	float	yDist;

	// Calculate the bounds of the rectangle
	xMin = rectangle.position.x;
	xMax = rectangle.position.x + rectangle.width;
	yMin = rectangle.position.y;
	yMax = rectangle.position.y + rectangle.height;
	// Convert the angle to radians
	angleRad = ray.direction * M_PI / 180.0;
	// Calculate the direction ratios
	dx = cos(angleRad);
	dy = sin(angleRad);
	// Initialize the step values and distances
	stepX = (dx > 0) ? 1 : -1;
	stepY = (dy > 0) ? 1 : -1;
	deltaX = fabs(1 / dx);
	deltaY = fabs(1 / dy);
	// Calculate the initial distances to the intersection points
	xDist = (dx > 0) ? (xMax - ray.position.x) : (ray.position.x - xMin);
	yDist = (dy > 0) ? (yMax - ray.position.y) : (ray.position.y - yMin);
	// Perform the raycasting
	while (xDist >= 0 && yDist >= 0)
	{
		// Check if the ray intersects the current cell
		if (xDist < yDist)
		{
			xDist -= deltaX;
			ray.position.x += stepX;
		}
		else
		{
			yDist -= deltaY;
			ray.position.y += stepY;
		}
		// Check for intersection with the rectangle
		if (ray.position.x >= xMin && ray.position.x <= xMax &&
			ray.position.y >= yMin && ray.position.y <= yMax)
		{
			return (1); // Intersection found
		}
	}
	return (0); // No intersection found
}

int	main(void)
{
	Ray			ray;
	Rectangle	rectangle;
	int			intersection;

	// Create a ray and a rectangle for testing
	ray.position.x = 2.0;
	ray.position.y = 2.0;
	ray.direction = 45.0; // 45 degrees (northeast direction)
	rectangle.position.x = 1.0;
	rectangle.position.y = 1.0;
	rectangle.width = 4.0;
	rectangle.height = 4.0;
	// Perform raycasting
	intersection = raycast(ray, rectangle);
	// Output the result
	if (intersection)
	{
		printf("Intersection found!\n");
	}
	else
	{
		printf("No intersection found.\n");
	}
	return (0);
}
