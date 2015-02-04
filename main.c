#include <iostream>
#include <fstream>
#define WIDTH 400
#define HEIGHT 400
using namespace std;
 
int main()
{
	Scene main_scene;
	Color *image = new Color[HEIGHT*WIDTH];
	main_scene.loadScene("example/sample01.txt");
	render(main_scene,image);
	getSeparatedRVB(image, r,v,b);
	tabToBMP(WIDTH,HEIGHT,"output/sample01.bmp")
	delete image[];
}