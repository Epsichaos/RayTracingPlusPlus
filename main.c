#include <iostream>
#include <fstream>
#define WIDTH 400
#define HEIGHT 400
using namespace std;

int main()
{
	Scene main_scene("example/sample01.txt");
	Color *image = new Color[HEIGHT*WIDTH];
    // La fonction loadScene a été supprimée, utiliser le constructeur
    // pour initialiser la scene
	render(main_scene,image, WIDTH, HEIGHT);
	tabToBMP(image,WIDTH,HEIGHT,"output/sample01.bmp")
	delete image[];
}
