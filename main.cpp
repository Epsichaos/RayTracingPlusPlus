#include <iostream>
#include <fstream>
#include "fonctions.h"
#define WIDTH 800
#define HEIGHT 800
using namespace std;
#include "scene.h"

int main()
{
	Scene main_scene("input",0);
	Color *image = new Color[HEIGHT*WIDTH];
    // La fonction loadScene a été supprimée, utiliser le constructeur
    // pour initialiser la scene
	render(main_scene,image, WIDTH, HEIGHT);
	tabToBMP(image,WIDTH,HEIGHT,"output/sample01.bmp");
	delete[] image;

}
