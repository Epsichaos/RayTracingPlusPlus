#include <iostream>
#include <fstream>
#include "fonctions.h"
#include <string>
#include <sstream>
#include <cstdlib>

#define WIDTH 1000
#define HEIGHT 1000
using std::endl;
using std::cout;
using std::string;
using std::ostringstream;
using std::ofstream;

#include "scene.h"

   template<typename T>
   T StringToNumber(const std::string& numberAsString)
   {
      T valor;

      std::stringstream stream(numberAsString);
      stream >> valor;
      return valor;
   }

int main(int argc, char* argv[])
{
	if(argc==2)
	{
		if(strcmp(argv[1],"-video")==0)
		{
			string input_file = argv[1];
			ostringstream a;
			clock_t temps_init; 
			double hauteur_debut = 2;
			double hauteur_fin = -2;
			double temps_simulation = 3.0;
			double ips = 30;
			double n = temps_simulation*ips;
			for(int i=0;i<n;i++)
			{
				temps_init = clock();
				ofstream fichier("input/input", std::ios::out | std::ios::trunc);
				fichier<<"sp (0.0 0 0) 2 (0 1 0) 0 0.0"<<endl;
				fichier<<"sp (3 1.5 "<<(i/n)*(hauteur_fin-hauteur_debut)+hauteur_debut<<") 0.5 (0 0 1) 1.15 0.5"<<endl;
				fichier<<"sp (0 0 -3.5) 3 (1 0 0) 0 0.0"<<endl;
				fichier<<"ca (13.0 0.0 0.0) (-1.0 0.0 0.0) 20 10 5.0 (0.0 0.0 1.0) (0.0 -1.0 0.0) (1.0 1.0 1.0) true"<<endl;
				fichier<<"li (8 2 4) 0.7 (1.0 1.0 1.0)"<<endl;
				fichier<<"li (8 1 4) 0.7 (1.0 1.0 1.0)"<<endl;
				Scene main_scene("input/input",1.1);
				Color *image = new Color[HEIGHT*WIDTH];
				render(main_scene,image, WIDTH, HEIGHT);
				ostringstream a;
				a<<"output/sample";
				a<<i;
				a<<".bmp";
				tabToBMP(image,WIDTH,HEIGHT,a.str());

				double pourcentage = 100*((i+1));
				pourcentage/=n;
				double temps_restant = (100-pourcentage)*(double)(clock()-temps_init)/(pourcentage/(i+1))/CLOCKS_PER_SEC;
				if(temps_restant/60<1)
				{
					printf("%f secondes restantes \n",temps_restant );

				}
				else
				{
					printf("%f minutes de calcul restantes \n",temps_restant/60 );
				}
				delete[] image;
			}
		}
	}
	else if(argc==3)
	{
		string input_file = argv[1];
		double indice_refract = StringToNumber<double>(argv[2]);
		double hauteur_debut = 2;
		double hauteur_fin = -2;
		double temps_simulation = 3.0;
		double ips = 30;
		double n = temps_simulation*ips;
		Scene main_scene(input_file,indice_refract);
		Color *image = new Color[HEIGHT*WIDTH];

		render(main_scene,image, WIDTH, HEIGHT);
		ostringstream a;
		a<<"output/sample";
		a<<".bmp";
		tabToBMP(image,WIDTH,HEIGHT,a.str());
		delete[] image;
	}
	else
	{
		cout<<"Error"<<endl;
		cout<<"usage : ./raytracing inputfile indice_refraction"<<endl;
		cout<<"or"<<endl;
		cout<<"usage : ./raytracing -video"<<endl;
	}
}
