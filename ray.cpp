#include "ray.h"
#include "point.h"
#include "vector.h"

Vector Ray::getDirection() {
	return m_direction;
}
void Ray::setStart(Point const A) {
	m_start = A;
}
void Ray::setDirection(Vector const A) {
	m_direction = A;
}
Ray::Ray(){

}
Ray::Ray(Point const A, Vector const B):m_start(A),m_direction(B){

}
