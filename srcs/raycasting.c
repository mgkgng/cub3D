#include "cub3D.h"

/* direction should be
(x, y) = (sin(a), cos(a)) with mouse hook -> let's implement the speed of chaning direction;
*/

t_raycast	get_raycast(t_point p1, t_point p2, t_point p3, t_point p4)
{
	t_raycast	raycast;

	raycast.x1 = p1.x;
	raycast.y1 = p1.y;
	raycast.x2 = p2.x;
	raycast.y2 = p2.y;
	raycast.x3 = p3.x;
	raycast.y3 = p3.y;
	raycast.x4 = p4.x;
	raycast.y4 = p4.y;
}

bool	raycasting(t_map map)
{
	t_raycast	cast;
	double		div;
	double		t;
	double		u;

	cast = get_raycast(p1, p2, map.pos, map.dir);
	div = (cast.x1 - cast.x2) * (cast.y3 - cast.y4) - (cast.y1 - cast.y2) * (cast.x3 - cast.x4);
	t = ((cast.x1 - cast.x3) * (cast.y3 - cast.y4) - (cast.y1 - cast.y3) * (cast.x3 - cast.x4)) / div;
	u = -((cast.x1 - cast.x2) * (cast.y1 - cast.y3) - (cast.y1 - cast.y2) * (cast.x1 - cast.x3)) / div;
	if (t > 0 && t < 1 && u > 0)
		return (true);
	return (false);
}