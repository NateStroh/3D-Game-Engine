#pragma once





class Point2D
{

public:

	Point2D() noexcept
	{
		x = 0;
		y = 0;
	}
	Point2D(int _x, int _y) noexcept
	{
		x = _x;
		y = _y;
	}


	Point2D operator+(const Point2D& p)
	{
		return Point2D(this->x + p.x, this->y + p.y);
	}
	Point2D operator+=(const Point2D& p)
	{
		this->x += p.x;
		this->y += p.y;
		return *this;
	}
	Point2D operator-(const Point2D& p)
	{
		return Point2D(this->x - p.x, this->y - p.y);
	}
	Point2D operator-=(const Point2D& p)
	{
		this->x -= p.x;
		this->y -= p.y;
		return *this;
	}
	bool operator==(const Point2D& p)
	{
		return (this->x == p.x && this->y == p.y);
	}
	bool operator!=(const Point2D& p)
	{
		return (this->x != p.x && this->y != p.y);
	}

	Point2D operator*(int x)
	{
		return Point2D(this->x * x, this->y * x);
	}
	
	Point2D operator*=(int x)
	{
		this->x *= x;
		this->y *= x;
		return *this;
	}
	Point2D operator/(int x)
	{
		return Point2D(this->x / x, this->y / x);
	}
	Point2D operator/=(int x)
	{
		this->x /= x;
		this->y /= x;
		return *this;
	}

	Point2D operator-()
	{
		return Point2D(this->x * -1, this->y * -1);
	}

	int x, y;

private:


};

