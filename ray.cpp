#include "ray.h"
#include "point.h"
#include "vector.h"

Ray::Ray(){

}
Ray::Ray(Point const A, Vector const B):m_start(A),m_direction(B){

}

Vector Ray::getDirection() {
	return m_direction;
}

Point Ray::getStart() {
	return m_start;
}

void Ray::setStart(Point const A) {
	m_start = A;
}

void Ray::setDirection(Vector const A) {
	m_direction = A;
}
