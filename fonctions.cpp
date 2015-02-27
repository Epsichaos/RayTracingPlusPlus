#include <maths.h>
#include <string>
#include <iostream>
#include "scene.h"
#include "ray.h"
#include "object.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "camera.h"
#include "cube.h"
#include "light.h"
#include "sphere.h"

void render(Scene const& Mainscene, Color* image int width, int height)
{
	int i,j;
	double **tabX = new double* [height];	 // Ces tableaux 2D doivent contenir la position du centre des cases
	double **tabY = new double* [height];
	for (i = 0; i < height; ++i)
	{
		*tabX[i] = new double[width];
		*tabY[i] = new double[width];
	}
	Camera activeCamera = Mainscene.getActiveCamera();
	fill_tabX_tabY(tabX,tabY,Mainscene.activeCamera.getPosition(),activeCamera.getDirection(),activeCamera.getAngle());

	ray rayon_init;
	for(i=0;i<height)
	{
		for (j = 0; i < width; ++j)
		{
			rayon_init.setStart(Mainscene.getActiveCamera().getPosition());
			rayon_init.setDirection(tabX[i][j]-Mainscene.getActiveCamera().getPosition().x(), tabY[i][j]-Mainscene.getActiveCamera().getPosition().y()); // en X puis en Y
			image[i][j]=lancer_rayon(rayon_init, Mainscene,0);
		}
	}

}
void fill_tabX_tabY(double **tabX,double **tabY,Point camerapos,Vector cameradir)
{
	int i,j;
	double pixel_size = 2*DIST_FROM_CAMERA*tan(2*3.1415926535/360*VIEWING_ANGLE);
	Vector getNormalVector(cameradir)

}
Color lancer_rayon(ray rayon, scene scene, int current_depth)
{
	Color pixel_color;
	int number_of_objects=0;
	int indice_closest;
	Color color_point;
	number_of_objects = scene.getNumberOfObjects();
	Object* objets = new object[number_of_objects];
	Point* intersections = new point[number_of_objects];
	scene.getObjects(objets);
	for(int i=0;i<number_of_objects;i++)
	{
		intersections[i] = compute_intersection(rayon,objets[i]);
	}
	indice_closest = findClosest(rayon, objets);

	pixel_color = objets[indice_closest].getColor;
	number_of_lights = scene.getNumberOfObjects("Light");
	light* lights = new light[number_of_lights];
	vector normale = objets[indice_closest].computeNormale(intersections[indice_closest]);
	for(int j=0;j<number_of_lights;j++)
	{
		shadow_factor = computeShadow(intersections[indice_closest], objets[indice_closest],lights[j]); // penser à mettre l'atténuation dedans
		vector ray_to_light = lights[j].computeRayToLight(intersections[indice_closest]);
		this_difuse_color *= shadow_factor*(raytolight*normale)*objets[indice_closest].GetDiffuseFactor();
		this_difuse_color *= lights[j].getColor;
		difuse_color+=this_difuse_color;
	}
	return difuse_color;

	/*
	if(objets[indice_closest].hasReflexion())
	{

		ray* new_ray = new ray(intersections[indice_closest], rayon.direction()-2*(normale*rayon.direction())*normale);
		if(current_depth<MAX_RECCURSIVE_DEPTH)
			color_point = lancer_rayon(new_ray, scene, current_depth+1); // A voir plus tard pour passage par reference  /!\
	}
	if(objets[indice_closest].hasRefraction())
	{

	}
	*/

}
void tabToBMP(Color *image, int w, int h, string path)
{
	int r,v,b;
	FILE *f;
	unsigned char *img = NULL;
	int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int
	if( img )
		free( img );
	img = (unsigned char *)malloc(3*w*h);
	memset(img,0,sizeof(img));

	for(int i=0; i<w; i++)
	{
		for(int j=0; j<h; j++)
		{
			x=i; y=(yres-1)-j;
			r = image[i*h+j].getRed()*255;
			g = image[i*h+j].getGreen()*255;
			b = image[i*h+j].getBlue()*255;
			if (r > 255) r=255;
			if (g > 255) g=255;
			if (b > 255) b=255;
			img[(x+y*w)*3+2] = (unsigned char)(r);
			img[(x+y*w)*3+1] = (unsigned char)(g);
			img[(x+y*w)*3+0] = (unsigned char)(b);
		}
	}

	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);

	f = fopen(path.c_str(),"wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(i=0; i<h; i++)
	{
		fwrite(img+(w*(h-i-1)*3),3,w,f);
		fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}
	fclose(f);
}


Point operator+(Point const& a, Vector const& b)
{
	Point c(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
	return c;
}
Point operator+(Vector const& a, Point const& b)
{
	Point c(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
	return c;
}
Vector operator*(Vector const& a, float const& b)
{
	Vector c(a.x()*b, a.y()*b, a.z()*b);
	return c;
}
Vector operator*(float const& b, Vector const& a)
{
	Vector c(a.x()*b, a.y()*b, a.z()*b);
	return c;
}
double operator*(Vector const& a, Vector const& b)
{
	return (a.x()*b.x()+a.y()*b.y()+a.z()*b.z());
}
Vector operator+(Vector const& a, Vector const& b)
{
	Vector c(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
	return c;
}
Color operator+(Color const& a, Color const& b)
{
	Color c(a.getGreen()+b.getGreen(),a.getRed()+b.getRed(),a.getBlue()+b.getBlue());
	return c;
}
Color operator*(Color const& a, Color const& b)
{
	Color c(a.getGreen()*b.getGreen(),a.getRed()*b.getRed(),a.getBlue()*b.getBlue());
	return c;
}


Point computeIntersection(Ray rayon, Object objet)
{
	if(Object.getType()=="sphere")
	{
		double t1,t2,
		int a = rayon.getDirection()*rayon.getDirection();
		int b = rayon.getDirection().x()*rayon.getStart().x()+rayon.getDirection().y()*rayon.getStart().y()+rayon.getDirection().z()*rayon.getStart().z();
		int c = rayon.getStart().x()*rayon.getStart().x()+rayon.getStart().y()*rayon.getStart().y()+rayon.getStart().z()*rayon.getStart().z()-;
		r = objet::Sphere.getRadius();
		c -= r*r;
		delta = b*b-4*a*c;
		if(delta>0)
		{
			t1=(-b-sqrt(delta))/2/a;
			t2=(-b+sqrt(delta))/2/a;
			if(t1>0)
			{
				t=t1;
			}
			else if(t1<0&& t2>0)
			{
				t=t2;
			}
			else
			{
				t=MAX_DISTANCE
			}

		}
		if(delta==0)
			t = -b/2/a;
		else
			t=MAX_DISTANCE;
		Point A= rayon.getStart()+rayon.getDirection()*t;
		return A;

	}
}
