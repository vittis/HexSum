#include "Geometry.h"

Rect::Rect() : x(0), y(0), w(0) ,h(0){	
}

Rect::Rect(float x, float y, float w, float h): x(x), y(y), w(w), h(h){
	
}

void Rect::SetHeight(float height){
	h = height;
}

void Rect::SetWidth(float width){
	w = width;
}

void Rect::SetX(float x1){
	x = x1;
}

void Rect::SetY(float y1){
	y = y1;
}

float Rect::GetX(){
	return x;
}

float Rect::GetY(){
	return y;
}


float Rect::GetHeight(){
	return h;
}

float Rect::GetWidth(){
	return w;
}

Point Rect::CenterRect() const{
	return Point(x+(h/2),y+(w/2));
}

Rect* Rect::SumRect(Point point, Rect rect){	
	return new Rect(point.getX()+rect.GetX(), point.getY()+rect.GetY(), rect.GetWidth(), rect.GetHeight());	
}

float Rect::Distance(Rect r1, Rect r2){
	return sqrt(pow(r1.CenterRect().getX()-r2.CenterRect().getX(),2) + pow(r1.CenterRect().getY() - r2.CenterRect().getY(),2));
}

bool Rect::IsInside(float x1, float y1){
	return (x1 >= x && x1 <= x + w  && y1 >= y && y1 <= y + h );
}

Point::Point(): x(0) , y(0){
	
}

Point::Point(float x, float y) : x(x), y(y){
	
}

float Point::getX(){
	return x;
}

float Point::getY(){
	return y;
}

void Point::setY(float y){
	this->y = y;
}

void Point::setX(float x){
	this->x = x;
}


float Point::Distance(Point p1, Point p2){
	return sqrt(pow(p1.getX()-p2.getX(),2) + pow(p1.getY() - p2.getY(),2));
}

Point* Point::SumPoint(Point p1, Point p2){
	return new Point(p1.getX()+p2.getX(), p1.getY()+p2.getY());
}

float Point::InclinacaoReta(Point p1, Point p2){
	return 0;
}


Point Point::operator+(const Point& rhs) const {
	return Point(x + rhs.x, y + rhs.y);
 }

Point Point::operator-(const Point& rhs) const {
	return Point(x - rhs.x, y - rhs.y);
}

