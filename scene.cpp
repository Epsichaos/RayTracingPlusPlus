#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void Scene::load_scene(const string path) {

    int numberOfObjects = 0;
    int line_size = 0;
    int i;
    string file_name = "input";
    ifstream file_img;
    file_img.open(file_name.c_str());

    // Si ouverture OK
    if(file_img) {
        string line_img;
        // Boucle sur les lignes
        while(getline(file_img, line_img)) {
            numberOfObjects++;
            line_size = line_img.size();

        }
    }
    // Si erreur
    else {
        cerr << "Error when opening input file" << endl;
    }
    return 0;
}
