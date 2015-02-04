#ifndef FONCTIONS_H
#define FONCTIONS_H

void render(scene const& Mainscene, color* image);
point computeIntersection(ray rayon, object objet);
int findClosest(ray rayon, object* objet)

#endif
