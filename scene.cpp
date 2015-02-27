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
#include "light.h"
#include "camera.h"

using namespace std;

Scene::Scene(const string path) {
    // On initialise à 0 les compteurs d'objects
    m_objectNumber = 0;
    m_sphereNumber= 0;
    m_lightNumber = 0;
    m_cameraNumber = 0;
    m_cubeNumber = 0;

    // pour le parcours des boucles
    int line_size = 0;

    // pour la sphere
    double nb_1, nb_2, nb_3, radius;

    // variables pour les couleurs
    double color_R, color_V, color_B;

    // variables pour les points (du cube notamment)
    double cp1_1, cp1_2, cp1_3, cp2_1, cp2_2, cp2_3, cp3_1, cp3_2, cp3_3, cp4_1, cp4_2, cp4_3;
    double cp5_1, cp5_2, cp5_3, cp6_1, cp6_2, cp6_3, cp7_1, cp7_2, cp7_3, cp8_1, cp8_2, cp8_3;

    // variables de point
    Point center, ar_1, ar_2, ar_3, ar_4, ar_5, ar_6, ar_7, ar_8;

    // pour la camera
    int width, height;
    Vector vec_1;

    // compteur pour parcourir les différents array
    int comp_sp = 0;
    int comp_cu = 0;
    int comp_ca = 0;
    int comp_li = 0;

    // variable de couleur
    Color color_object;

    // les variables temporaires des objects
    Sphere spr;
    Cube cu;
    Light li;
    Camera ca;

    // options pour l'ouverture du fichier
    string file_name = path;
    ifstream file_img;
    file_img.open(file_name.c_str());
    const char* line_img_str;

    // Si ouverture OK
    if(file_img) {
        string line_img;
        // Boucle sur les lignes
        while(getline(file_img, line_img)) {
            m_objectNumber++;
            line_img_str = line_img.c_str();
            // on compte le nombre d'objects de chaque type
            if(line_img_str[0]=='s'&&line_img_str[1]=='p') {
                m_sphereNumber++;
            }
            if(line_img_str[0]=='c'&&line_img_str[1]=='u') {
                m_cubeNumber++;
            }
            if(line_img_str[0]=='c'&&line_img_str[1]=='a') {
                m_cameraNumber++;
            }
            if(line_img_str[0]=='l'&&line_img_str[1]=='i') {
                m_lightNumber++;
            }
        }

        // On alloue la mémoire sur les variables de classe selon le nombre d'objects détectés
        m_arrayOfSphere = new Sphere[m_sphereNumber];
        m_arrayOfCube = new Cube[m_cubeNumber];
        m_arrayOfLight = new Light[m_lightNumber];
        m_arrayOfCamera = new Camera[m_cameraNumber];

        file_img.clear();
        file_img.seekg(0, file_img.beg);
        while(getline(file_img, line_img)) {
            line_img_str = line_img.c_str();
            line_size = line_img.size();
                // Si la ligne est de type sphere
            if(line_img_str[0]=='s'&&line_img_str[1]=='p') {
                sscanf(line_img_str, "sp (%lf %lf %lf) %lf (%lf %lf %lf)", &nb_1, &nb_2, &nb_3, &radius, &color_R, &color_V, &color_B);
                center.setPoint(nb_1, nb_2, nb_3);
                spr.setCenter(center);
                spr.setRadius(radius);
                color_object.setColor(color_R, color_V, color_B);
                spr.setColorObject(color_object);
                spr.setTypeObject("sphere");
                m_arrayOfSphere[comp_sp] = spr;
                comp_sp++;
            }
            // si la ligne est de type cube
            if(line_img_str[0]=='c'&&line_img_str[1]=='u') {
                sscanf(line_img_str, "cu (%lf %lf %lf) (%lf %lf %lf) (%lf %lf %lf) (%lf %lf %lf) (%lf %lf %lf) (%lf %lf %lf) (%lf %lf %lf) (%lf %lf %lf) (%lf %lf %lf)", &cp1_1, &cp1_2, &cp1_3, &cp2_1, &cp2_2, &cp2_3, &cp3_1, &cp3_2, &cp3_3, &cp4_1, &cp4_2, &cp4_3, &cp5_1, &cp5_2, &cp5_3, &cp6_1, &cp6_2, &cp6_3, &cp7_1, &cp7_2, &cp7_3, &cp8_1, &cp8_2, &cp8_3, &color_R, &color_V, &color_B);
                ar_1.setPoint(cp1_1, cp1_2, cp1_3);
                ar_2.setPoint(cp2_1, cp2_2, cp2_3);
                ar_3.setPoint(cp3_1, cp3_2, cp3_3);
                ar_4.setPoint(cp4_1, cp4_2, cp4_3);
                ar_5.setPoint(cp5_1, cp5_2, cp5_3);
                ar_6.setPoint(cp6_1, cp6_2, cp6_3);
                ar_7.setPoint(cp7_1, cp7_2, cp7_3);
                ar_8.setPoint(cp8_1, cp8_2, cp8_3);
                cu.setCube(ar_1, ar_2, ar_3, ar_4, ar_5, ar_6, ar_7, ar_8);
                color_object.setColor(color_R, color_V, color_B);
                cu.setColorObject(color_object);
                cu.setTypeObject("cube");
                m_arrayOfCube[comp_cu] = cu;
                comp_cu++;
            }
            // si la ligne est de type camera
            if(line_img_str[0]=='c'&&line_img_str[1]=='a') {
                sscanf(line_img_str, "ca (%lf %lf %lf) (%lf %lf %lf) %d %d %lf (%lf %lf %lf)", &cp1_1, &cp1_2, &cp1_3, &cp2_1, &cp2_2, &cp2_3, &width, &height, &nb_1, &color_R, &color_V, &color_B);
                ar_1.setPoint(cp1_1, cp1_2, cp1_3);
                vec_1.setVector(cp2_1, cp2_2, cp2_3);
                color_object.setColor(color_R, color_V, color_B);
                ca.setPosition(ar_1);
                ca.setDirection(vec_1);
                ca.setSize(width, height);
                ca.setAngle(nb_1);
                ca.setColorObject(color_object);
                ca.setTypeObject("camera");
                m_arrayOfCamera[comp_ca] = ca;
                comp_ca++;
            }
            // si la ligne est de type light
            if(line_img_str[0]=='l'&&line_img_str[1]=='i') {
                sscanf(line_img_str, "li (%lf %lf %lf) %lf (%lf %lf %lf)", &cp1_1, &cp1_2, &cp1_3, &nb_1, &color_R, &color_V, &color_B);
                center.setPoint(cp1_1, cp1_2, cp1_3);
                li.setSource(center);
                li.setIntensity(nb_1);
                li.setTypeObject("light");
                color_object.setColor(color_R, color_V, color_B);
                li.setColorObject(color_object);
                m_arrayOfLight[comp_li] = li;
                comp_li++;
            }
        }
    }
    // Message d'erreur en cas d'ouverture impossible
    else {
        cerr << "Error when opening input file" << endl;
    }
}

int Scene::getNumberOfObjects() {
    return m_objectNumber;
}
<<<<<<< HEAD

int Scene::getActiveCamera() {
    return m_arrayOfCamera[m_idActiveCamera];
}
// rajouter les test sur les conditions : comparaison de string c++
int Scene::getNumberOfObjects(string str) {
    string cam = "camera";
    string lig = "light";
    string cub = "cube";
    string sphere = "sphere";
    if() {
        return m_sphereNumber;
    }
    if() {
        return m_cubeNumber;
    }
    if() {
        return m_lightNumber;
    }
    if() {
        return m_cameraNumber;
    }
}

>>>>>>> almost finished
// Fonction de debug temporaire
void Scene::debugTest() {
    cout << "Nombre objects = " << m_objectNumber << endl;
    cout << "Nombre lights = " << m_lightNumber << endl;
    cout << "Nombre camera = " << m_cameraNumber << endl;
    cout << "Nombre cube = " << m_cubeNumber << endl;
    cout << "Nombre sphere = " << m_sphereNumber << endl;
    for(int i=0; i<m_sphereNumber; i++) {
        m_arrayOfSphere[i].printSphere();
    }
    for(int i=0; i<m_cameraNumber; i++) {
        m_arrayOfCamera[i].printCamera();
    }
    for(int i=0; i<m_cubeNumber; i++) {
        m_arrayOfCube[i].printCube();
    }
    for(int i=0; i<m_lightNumber; i++) {
        m_arrayOfLight[i].printLight();
    }
}
