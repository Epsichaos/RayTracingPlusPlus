#ifndef FONCTIONS_H
#define FONCTIONS_H

void render(Scene const& Mainscene, Color* image);
Point computeIntersection(Ray rayon, Object objet);
int findClosest(Ray rayon, object* Objet);
Vector operator*(Vector const& a, Vector const& b);
Vector operator+(Vector const& a, Vector const& b);
Color operator+(Color const& a, Color const& b);
Color operator*(Color const& a, Color const& b);

#endif
