#include <iostream>
#include <fstream>
#include <string>
//#include <cstdlib>
#include <stdlib.h>
#include "sphere.h"
#include "object.h"
#include "material.h"
#include "point.h"
#include "color.h"
#include "scene.h"
#include "light.h"
#include "camera.h"
#include "mesh.h"
#include "operators.h"
using namespace std;

Scene::Scene(const string path,double refract_mesh) {
    // On initialise à 0 les compteurs d'objects
    m_objectNumber = 0;
    m_mesh = Mesh();
    m_sphereNumber= 0;
    m_lightNumber = 0;
    m_cameraNumber = 0;
    m_idActiveCamera = 0;
          // pour le parcours des boucles
    int line_size = 0;

    // pour la sphere
    double nb_1, nb_2, nb_3, radius;

    // coefficient reflexion refraction
    double reflexion, refraction;

    // variables pour les couleurs
    double color_R, color_V, color_B;

    // variables pour les points
    double cp1_1, cp1_2, cp1_3, cp2_1, cp2_2, cp2_3, cp3_1, cp3_2, cp3_3, cp4_1, cp4_2, cp4_3;

    // variables de point
    Point center, ar_1, ar_2, ar_3, ar_4, ar_5, ar_6, ar_7, ar_8;

    // pour la camera
    int width, height;
    Vector vec_1;
    char camera_state2[5];
    string camera_state;
    Vector ory,orx;
    // compteur pour parcourir les différents array
    int comp_sp = 0;
    int comp_ca = 0;
    int comp_li = 0;

    // variable de couleur
    Color color_object;

    // les variables temporaires des objects
    Sphere spr;
    Light li;
    Camera ca;
            // options pour l'ouverture du fichier
    Color a(1.0,0,0);
    unsigned int pointNumber=0;
    unsigned int faceNumber=0;
    unsigned int normaleNumber = 0;
    string file_name = path;
    ifstream file_img;
    file_img.open(file_name.c_str());
    const char* line_img_str;
    double x1,y1,z1;
    unsigned int n1,n2,n3;
    unsigned int normale1,normale2,normale3;

    // Si ouverture OK
    if(file_img) {
        string line_img;
        // Boucle sur les lignes
        while(getline(file_img, line_img)) {
            line_img_str = line_img.c_str();

            if(line_img_str[0]=='#') {
            }
            if(line_img_str[0]=='v' && line_img_str[1]==' ') {
                pointNumber++;
            }
            if(line_img_str[0]=='f' && line_img_str[1]==' ') {
                faceNumber++;
            }
            if(line_img_str[0]=='c'&&line_img_str[1]=='a') {
                m_cameraNumber++;
            }
            if(line_img_str[0]=='l'&&line_img_str[1]=='i') {
                m_lightNumber++;
            }
            if(line_img_str[0]=='v' && line_img_str[1]=='n') {
                normaleNumber++;
            }
            if(line_img_str[0]=='s'&&line_img_str[1]=='p') {
                m_sphereNumber++;
            }
        }
        unsigned int compteur_faces=0, compteur_points=0,compteur_normalespoints=0;
        m_arrayOfLight = new Light[m_lightNumber];
        m_arrayOfCamera = new Camera[m_cameraNumber];
        m_arrayOfSphere = new Sphere[m_sphereNumber];
        Point *tabPoints = new Point[pointNumber];
        Face *tabFaces = new Face[faceNumber];
        Vector *tabNormalesPoints = new Vector[normaleNumber];
        Vector *tabNormales = new Vector[faceNumber];
        file_img.clear();
        file_img.seekg(0, file_img.beg);
        while(getline(file_img, line_img)) {
            line_img_str = line_img.c_str();
            if(line_img_str[0]=='v' && line_img_str[1]==' ') {
                sscanf(line_img_str, "v %lf %lf %lf",&x1,&y1,&z1);
                    tabPoints[compteur_points].setPoint(x1,y1,z1);//Ici il faudrait tester si on peut accéder à ces cases, sinon déclencher une exception
                    compteur_points++;
                }
                if(line_img_str[0]=='v' && line_img_str[1]=='n') {
                    sscanf(line_img_str, "vn %lf %lf %lf",&x1,&y1,&z1);
                    tabNormalesPoints[compteur_normalespoints].setVector(-x1,-y1,-z1);//Ici il faudrait tester si on peut accéder à ces cases, sinon déclencher une exception
                    compteur_normalespoints++;
                }
                if(line_img_str[0]=='f' && line_img_str[1]==' ') {
                    sscanf(line_img_str, "f %u/%*u/%u %u/%*u/%u %u/%*u/%u",&n1,&normale1,&n2,&normale2,&n3,&normale3);
                    tabFaces[compteur_faces].setFace(tabPoints[n1-1],tabPoints[n2-1],tabPoints[n3-1]); //Ici il faudrait tester si on peut accéder à ces cases, sinon déclencher une exception
                    tabFaces[compteur_faces].setColor(a);
                    tabNormales[compteur_faces]=tabNormalesPoints[normale1-1]+tabNormalesPoints[normale2-1]+tabNormalesPoints[normale3-1]; //Ici il faudrait tester si on peut accéder à ces cases, sinon déclencher une exception
                    tabNormales[compteur_faces].normalize();
                    compteur_faces++;
                }
                if(line_img_str[0]=='s'&&line_img_str[1]=='p') {
                    sscanf(line_img_str, "sp (%lf %lf %lf) %lf (%lf %lf %lf) %lf %lf", &nb_1, &nb_2, &nb_3, &radius, &color_R, &color_V, &color_B, &refraction, &reflexion);
                    center.setPoint(nb_1, nb_2, nb_3);
                    spr.setCenter(center);
                    spr.setRadius(radius);
                    //mutateur pour le material
                    color_object.setColor(color_R, color_V, color_B);
                    spr.setColorObject(color_object);
                    spr.setReflexion(reflexion);
                    spr.setRefraction(refraction);
                    spr.setTypeObject("sphere");
                    spr.Object::setDiffuseFactor(0.7);
                    m_arrayOfSphere[comp_sp] = spr;
                    comp_sp++;
                }
                if(line_img_str[0]=='c'&&line_img_str[1]=='a') {
                    sscanf(line_img_str, "ca (%lf %lf %lf) (%lf %lf %lf) %d %d %lf (%lf %lf %lf) (%lf %lf %lf) (%lf %lf %lf) %s", &cp1_1, &cp1_2, &cp1_3, &cp2_1, &cp2_2, &cp2_3, &width, &height, &nb_1, &cp3_1, &cp3_2, &cp3_3, &cp4_1, &cp4_2, &cp4_3, &color_R, &color_V, &color_B, &camera_state2);
                    camera_state=camera_state2;
                    printf("\n%s\n",camera_state.c_str());
                    ar_1.setPoint(cp1_1, cp1_2, cp1_3);
                    vec_1.setVector(cp2_1, cp2_2, cp2_3);
                    ory.setVector(cp3_1,cp3_2,cp3_3);
                    orx.setVector(cp4_1,cp4_2,cp4_3);
                    color_object.setColor(color_R, color_V, color_B);
                    ca.setPosition(ar_1);
                    ca.setDirection(vec_1);
                    ca.setSize(width, height);
                    ca.setAngle(nb_1);
                    ca.setColorObject(color_object);
                    ca.setTypeObject("camera");
                    ca.setOrientationX(orx);
                    ca.setOrientationY(ory);
                    if(camera_state=="true") {
                        ca.setState("true");
                        m_idActiveCamera = comp_ca;
                    }
                    else if(camera_state=="false") {
                        ca.setState("false");
                    }
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
            m_mesh.defineFaces(tabFaces,faceNumber);
            m_mesh.defineNormales(tabNormales,faceNumber);
            m_mesh.setDiffuseFactor(0.7);
            m_mesh.setRefraction(refract_mesh);
            delete[] tabFaces;
            delete[] tabNormalesPoints;
            delete[] tabNormales;
            delete[] tabPoints;
        }
    }
    void Scene::getSpheres(Sphere *tab)
    {
        int i;
        for (i = 0; i < m_sphereNumber; ++i)
        {
            tab[i] = m_arrayOfSphere[i];
        }
    }
    void Scene::getLights(Light *tab)
    {
        int i;
        for (i = 0; i < m_lightNumber; ++i)
        {
            tab[i] = m_arrayOfLight[i];
        }
    }
    void Scene::getCameras(Camera *tab)
    {
        int i;
        for (i = 0; i < m_cameraNumber; ++i)
        {
            tab[i] = m_arrayOfCamera[i];
        }
    }
    int Scene::getNumberOfObjects() {
        return m_objectNumber;
    }

    Camera Scene::getActiveCamera() {
        return m_arrayOfCamera[m_idActiveCamera];
    }
// rajouter les test sur les conditions : comparaison de string c+
    int Scene::getNumberOfObjects(string str){
        string cam = "camera";
        string lig = "light";
        string spr = "sphere";
        if(str == spr) {
            return m_sphereNumber;
        }
        if(str == lig) {
            return m_lightNumber;
        }
        if(str == cam) {
            return m_cameraNumber;
        }
        else {
            return 0;
        }
    }

    unsigned int Scene::getNumberOfMeshFaces(){
        return m_mesh.getNumberOfFace();
    }
    void Scene::getFaces(Face* faces)
    {
        m_mesh.getFaceArray(faces);
    }
    void Scene::getNormales(Vector* normales)
    {
        m_mesh.getNormalesArray(normales);
    }
    Scene::~Scene()
    {
        delete[] m_arrayOfLight;
        delete[] m_arrayOfCamera;
        delete[] m_arrayOfSphere;
    }
void Scene::getMesh(Mesh* output)
{
    *output = m_mesh;
}