#ifndef GREOMETRY_H_
#define GREOMETRY_H_

#include <math.h>

class Point;
class Rect;

class Rect{
	
public:
		float x;
		float y;
		float w;
		float h;
		
		Rect();
		Rect(float, float, float, float);
		
		void SetX(float);
		void SetY(float);
		void SetWidth(float);
		void SetHeight(float);
		
		float GetX();
		float GetY();
		float GetWidth();
		float GetHeight();
		
		Rect* SumRect(Point, Rect);
		Point CenterRect() const;
		float Distance(Rect, Rect);
		bool IsInside(float, float);
	
};

class Point {
	public:
		float x;
		float y;
		
		Point();
		Point(float, float);
		
		void setX(float);
		void setY(float);
		
		float getX();
		float getY();
		
		float Distance(Point, Point);
		Point* SumPoint(Point, Point);
		float InclinacaoReta(Point, Point);
		Point operator+(const Point& rhs) const;
		Point operator-(const Point& rhs) const;
		
		
		
};

#endif
