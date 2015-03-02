#include "fonctions.h"
#include "parameters.h"
#include <stdio.h>
void render(Scene & Mainscene, Color* image, int width, int height)
{
	int i,j;
	Point **tabCenters = new Point*[height];	 // Ces tableaux 2D doivent contenir la position du centre des cases
	for (i = 0; i < height; ++i)
		tabCenters[i] = new Point[width];
	Camera activeCamera = Mainscene.getActiveCamera();
	fill_tabX_tabY(tabCenters,activeCamera.getPosition(),activeCamera.getDirection(),activeCamera.getOrientationX(),activeCamera.getOrientationY(),width,height);

	Ray rayon_init;
	for(i=0;i<height;i++)
	{
		for (j = 0; i < width; ++j)
		{
			rayon_init.setStart(Mainscene.getActiveCamera().getPosition());
			rayon_init.setDirection(tabCenters[i][j]-Mainscene.getActiveCamera().getPosition()); // en X puis en Y
			image[i*height+j]=lancer_rayon(rayon_init, Mainscene,0);
		}
	}

}
void fill_tabX_tabY(Point **tabCenters,Point camerapos,Vector cameradir, Vector orientationX,Vector orientationY, int width, int height)
{
	int i,j;
	double pixel_size = 2*DIST_FROM_CAMERA*tan(2*3.1415926535/360*VIEWING_ANGLE);
	Vector deltaX = pixel_size*orientationX, deltaY = pixel_size*orientationY;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
			{
				tabCenters[i][j] = camerapos+cameradir*DIST_FROM_CAMERA+(((double)height/2)*orientationY)*pixel_size-deltaY*i-width/2*pixel_size*orientationX+deltaX*j+0.5*pixel_size*orientationX+0.5*pixel_size*orientationY;// à vérifier !!
			}
	}
}

Color lancer_rayon(Ray rayon, Scene scene, int current_depth)
{
	Color pixel_color;
	int indice_closest;
	Color this_diffuse_color;
	Color color_point, color_black(0,0,0),diffuse_color;
	double shadow_factor;
	int number_of_spheres = scene.getNumberOfObjects("sphere");
	int number_of_cameras = scene.getNumberOfObjects("camera");
	int number_of_lights = scene.getNumberOfObjects("light");
	Sphere* spheres = new Sphere[number_of_spheres];
	Light* lights = new Light[number_of_lights];
	Camera* cameras = new Camera[number_of_cameras];
	Point* intersections = new Point[number_of_spheres];
	scene.getSpheres(spheres);
	scene.getLights(lights);
	scene.getCameras(cameras);
	for(int i=0;i<number_of_spheres;i++)
	{
		intersections[i] = computeIntersection(rayon,spheres[i]);
	}
	indice_closest = findClosest(rayon, intersections,number_of_spheres);
	if(indice_closest==-1)
		return color_black;
	pixel_color = spheres[indice_closest].getColor();
	this_diffuse_color = pixel_color;
	Vector normale = spheres[indice_closest].computeNormale(intersections[indice_closest]);
	for(int j=0;j<number_of_lights;j++)
	{
		shadow_factor = computeShadow(intersections[indice_closest], spheres, number_of_spheres,lights[j]); // penser à mettre l'atténuation dedans
		Vector ray_to_light = lights[j].getSource()-intersections[indice_closest];
		this_diffuse_color = this_diffuse_color*shadow_factor*(ray_to_light*normale)*(spheres[indice_closest].Object::getDiffuseFactor());
		this_diffuse_color = this_diffuse_color*lights[j].getColor();
		diffuse_color= diffuse_color + this_diffuse_color;
	}
	return diffuse_color;

	/*
	if(spheres[indice_closest].hasReflexion())
	{

		ray* new_ray = new ray(intersections[indice_closest], rayon.direction()-2*(normale*rayon.direction())*normale);
		if(current_depth<MAX_RECCURSIVE_DEPTH)
			color_point = lancer_rayon(new_ray, scene, current_depth+1); // A voir plus tard pour passage par reference  /!\
	}
	if(spheres[indice_closest].hasRefraction())
	{

	}
	*/

}
void tabToBMP(Color *image, int w, int h, std::string path)
{
	int r,g,b,x,y,i;
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
			x=i; y=(h-1)-j;
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

Vector operator+(Vector const &a, Vector const &b)
{
	Vector c(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
	return c;
}

Color operator+(Color const& a, Color const& c)
{
	double r =a.getRed()+c.getRed() ,v = a.getGreen()+c.getGreen(),b=a.getBlue()+c.getBlue();
	Color d((r<=1?r:1.0),(v<=1?v:1.0),(b<=1?b:1.0));
	return d;
}

Point operator+(Point const& a, Vector const& b)
{
	Point c(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
	return c;
}
Point operator-(Point const& a, Vector const& b)
{
	Point c(a.x()-b.x(), a.y()-b.y(), a.z()-b.z());
	return c;
}
Point operator+(Vector const& a, Point const& b)
{
	Point c(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
	return c;
}
Vector operator*(Vector const& a, double const& b)
{
	Vector c(a.x()*b, a.y()*b, a.z()*b);
	return c;
}
Vector operator*(double const& b, Vector const& a)
{
	Vector c(a.x()*b, a.y()*b, a.z()*b);
	return c;
}
double operator*(Vector const& a, Vector const& b)
{
	return (a.x()*b.x()+a.y()*b.y()+a.z()*b.z());
}

Color operator*(Color const& a, Color const& b)
{
	Color c(a.getGreen()*b.getGreen(),a.getRed()*b.getRed(),a.getBlue()*b.getBlue());
	return c;
}
Color operator*(double const& a, Color const& b)
{
	Color c(a*b.getGreen(),a*b.getRed(),a*b.getBlue());
	return c;
}
Color operator*(Color const& a, double const& b)
{
	Color c(a.getGreen()*b,a.getRed()*b,a.getBlue()*b);
	return c;
}

Vector operator-(Point const& a, Point const& b)
{
	Vector c(a.x()-b.x(),a.y()-b.y(),a.z()-b.z());
	return c;
}

Point computeIntersection(Ray rayon, Sphere sphere)
{
	if(sphere.Object::getType()=="sphere")
	{
		double t1,t2,r, delta, t;
		int a = rayon.getDirection()*rayon.getDirection();
		int b = rayon.getDirection().x()*rayon.getStart().x()+rayon.getDirection().y()*rayon.getStart().y()+rayon.getDirection().z()*rayon.getStart().z();
		int c = rayon.getStart().x()*rayon.getStart().x()+rayon.getStart().y()*rayon.getStart().y()+rayon.getStart().z()*rayon.getStart().z();
		r = sphere.Sphere::getRadius();
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
				t=MAX_DISTANCE;
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
double computeShadow(Point p, Sphere *s,int number_of_spheres, Light l)
{
	int i;
	Point* intersections = new Point[number_of_spheres];
	Ray rayon(p, l.getSource()-p);
	for (i = 0; i <  number_of_spheres; ++i)
	{
		intersections[i]=computeIntersection(rayon ,s[i]);
	}
	if(findClosest(rayon, intersections, number_of_spheres)>-1)
		return 0.0;
	else 
		return 1.0;
}
int findClosest(Ray r, Point *p, int number_of_points)
{
int i,i_closest=-1;
double min = MAX_DISTANCE;
for (i = 0; i < number_of_points; ++i)
{
	if((p[i]-r.getStart())*(p[i]-r.getStart())<min)
	{
		min = (p[i]-r.getStart())*(p[i]-r.getStart());
		i_closest = i;
	}
}
return i_closest;
}