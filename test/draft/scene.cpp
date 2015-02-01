#include <iostream>
#include <fstream>
#include <string>
#include "scene.h"

using namespace std;

void Scene::load_scene(const string path) {

    int numberOfObjects = 0;
    int nb_sphere = 0;
    int nb_cube = 0;
    int nb_camera = 0;
    int nb_light = 0;
    int line_size = 0;
    int i,j;

    string nb_1, nb_2, nb_3;
    nb_1 = "";
    nb_2 = "";
    nb_3 = "";

    string file_name = "input";
    ifstream file_img;
    file_img.open(file_name.c_str());

    // Si ouverture OK
    if(file_img) {
        string line_img;
        // Boucle sur les lignes
        while(getline(file_img, line_img)) {
            numberOfObjects++;
            if(line_img[0]="s"&&line_img[1]="p") {
                nb_sphere++;
            }
            if(line_img[0]="c"&&line_img[1]="u") {
                nb_cube++;
            }
            if(line_img[0]="c"&&line_img[1]="a") {
                nb_camera++;
            }
            if(line_img[0]="l"&&line_img[1]="i") {
                nb_light++;
            }
        }
        object *arrayOfObjects = new object[numberOfObjects];
        file_img.seekg(0, ios::beg);
        while(getline(file_img, line_img)) {
            line_size = line_img.size();
            for(i=0; i<line_size; i++) {
                if(line_img[0]="s"&&line_img[1]="p") {
                    j = 5;
                    Sphere spr;
                    while(line_img[j]!=" ") {
                        nb_1 = nb_1 + line_img[j];
                        j++;
                    }
                    j++;
                    while(line_img[j]!=" ") {
                        nb_2 = nb_2 + line_img[j];
                        j++;
                    }
                    j++;
                    while(line_img[j]!=" ") {
                        nb_3 = nb_3 + line_img[j];
                        j++;
                    }
                    point center(atoi(nb_1), atoi(nb_2), atoi(nb_3));
                    spr.setCenter(center);
                }
            }
            // si la ligne est de type sphere
            if(line_img[0]="s"&&line_img[1]="p") {
                j = 4;
                Sphere spr;
                //Sphere.setCenter
            }
            // si la ligne est de type cube
            if(line_img[0]="c"&&line_img[1]="u") {

            }
            // si la ligne est de type camera
            if(line_img[0]="c"&&line_img[1]="a") {

            }
            // si la ligne est de type light
            if(line_img[0]="l"&&line_img[1]="i") {

            }
            // Si erreur
        }
    else {
            cerr << "Error when opening input file" << endl;
    }
    return 0;
}
