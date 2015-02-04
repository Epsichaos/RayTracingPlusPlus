#include <iostream>
#include <fstream>
#include <string>
//#include <cstdlib>
#include <stdlib.h>
#include "sphere.h"
#include "object.h"
#include "cube.h"
#include "material.h"
#include "point.h"
#include "color.h"
#include "scene.h"

using namespace std;

void Scene::loadScene(const string path) {

    int numberOfObjects = 0;
    int nb_sphere = 0;
    int nb_cube = 0;
    int nb_camera = 0;
    int nb_light = 0;
    int line_size = 0;
    int i,j;

    string nb_1, nb_2, nb_3, radius;
    string color_R, color_V, color_B;

    Color color_object;

    string file_name = "input";
    ifstream file_img;
    file_img.open(file_name.c_str());
    const char* line_img_str;

    // Si ouverture OK
    if(file_img) {
        string line_img;
        // Boucle sur les lignes
        while(getline(file_img, line_img)) {
            numberOfObjects++;
            cout << line_img << endl;
            line_img_str = line_img.c_str();
            if(line_img_str[0]=='s'&&line_img_str[1]=='p') {
                nb_sphere++;
            }
            if(line_img_str[0]=='c'&&line_img_str[1]=='u') {
                nb_cube++;
            }
            if(line_img_str[0]=='c'&&line_img_str[1]=='a') {
                nb_camera++;
            }
            if(line_img_str[0]=='l'&&line_img_str[1]=='i') {
                nb_light++;
            }
        }
        Object *arrayOfObjects = new Object[numberOfObjects];

        file_img.clear();
        file_img.seekg(0, file_img.beg);
        while(getline(file_img, line_img)) {
            line_img_str = line_img.c_str();
            line_size = line_img.size();
                // Si la ligne est de type sphere
                if(line_img_str[0]=='s'&&line_img_str[1]=='p') {
                    cout << "LEKOFJZOJRO" << endl;
                    j = 4;
                    Sphere spr;
                    nb_1 = "";
                    nb_2 = "";
                    nb_3 = "";
                    radius = "";
                    color_R = "";
                    color_V = "";
                    color_B = "";
                    while(line_img_str[j]!=' ') {
                        nb_1 = nb_1 + line_img_str[j];
                        j++;
                    }
                    j++;
                    while(line_img_str[j]!=' ') {
                        nb_2 = nb_2 + line_img_str[j];
                        j++;
                    }
                    j++;
                    while(line_img_str[j]!=' ') {
                        nb_3 = nb_3 + line_img_str[j];
                        j++;
                    }
                    Point center(stod((nb_1),NULL), stod((nb_2),NULL), stod((nb_3),NULL));
                    spr.setCenter(center);
                    j++;
                    while(line_img_str[j]!=' ') {
                        radius = radius + line_img_str[j];
                        j++;
                    }
                    spr.setRadius(stod(radius, NULL));
                    j++;
                    while(line_img_str[j]!=' ') {
                        color_R = color_R + line_img_str[j];
                        j++;
                    }
                    j++;
                    while(line_img_str[j]!=' ') {
                        color_V = color_V + line_img_str[j];
                        j++;
                    }
                    j++;
                    while(line_img_str[j]!=' ') {
                        color_B = color_B + line_img_str[j];
                        j++;
                    }
                    color_object.setColor(stod(color_R, NULL),stod(color_V, NULL),stod(color_B, NULL));
                    spr.setColorObject(color_object);
                    spr.printSphere();
                }
            /*
            // si la ligne est de type cube
            if(line_img[0]=="c"&&line_img[1]=="u") {

            }
            // si la ligne est de type camera
            if(line_img[0]=="c"&&line_img[1]=="a") {

            }
            // si la ligne est de type light
            if(line_img[0]=="l"&&line_img[1]=="i") {

            }
            */
        }
    }
    else {
        cerr << "Error when opening input file" << endl;
    }
}
