#ifndef FONCTIONS_H
#define FONCTIONS_H

void render(scene const& Mainscene, color* image);
Point computeIntersection(ray rayon, object objet);
int findClosest(ray rayon, object* objet);
Vector operator*(Vector const& a, Vector const& b);
Vector operator+(Vector const& a, Vector const& b);
Color operator+(Color const& a, Color const& b);
Color operator*(Color const& a, Color const& b);

#endif
