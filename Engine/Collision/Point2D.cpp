#include "Point2D.h"


Point2D operator*(int x, const Point2D& p)
{
	return Point2D(p.x * x, p.y * x);
}