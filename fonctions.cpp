#include "fonctions.h"
#include "parameters.h"
#include <stdio.h>
void render(Scene & Mainscene, Color* image, int width, int height)
{
	int i,j;
	Vector buffer;
	Point **tabCenters = new Point*[height];	 // Ces tableaux 2D doivent contenir la position du centre des cases
	for (i = 0; i < height; ++i)
		tabCenters[i] = new Point[width];

	Camera activeCamera = Mainscene.getActiveCamera();
	fill_tabX_tabY(tabCenters,activeCamera.getPosition(),activeCamera.getDirection(),activeCamera.getOrientationX(),activeCamera.getOrientationY(),width,height);
	Ray rayon_init;
	for(i=0;i<height;i++)
	{
		for (j = 0; j < width; ++j)
		{
			rayon_init.setStart(Mainscene.getActiveCamera().getPosition());
			buffer = tabCenters[i][j]-Mainscene.getActiveCamera().getPosition();
			buffer.normalize();
			rayon_init.setDirection(buffer); // en X puis en Y
			image[i*width+j]=lancer_rayon(rayon_init, Mainscene,0);
		}
	}

}
void fill_tabX_tabY(Point **tabCenters,Point camerapos,Vector cameradir, Vector orientationX,Vector orientationY, int width, int height)
{
	int i,j;
	double real_width = tan(M_PI/2*VIEWING_ANGLEX/180);
	double real_height = tan(M_PI/2*VIEWING_ANGLEY/180);
	double focal_lenght = sqrt(real_width*real_width + real_height*real_height) / ( 2*tan( 45/2 ) );
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
			{
			double alpha = tan(M_PI/2*VIEWING_ANGLEX/180)*(j-width/2)/(width/2);
			double beta = tan(M_PI/2*VIEWING_ANGLEY/180)*(height/2-i)/(height/2);
				tabCenters[i][j] = camerapos+cameradir*1+orientationX*alpha+orientationY*beta;// à vérifier !!
			};
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
	else
		printf("");
	pixel_color = spheres[indice_closest].getColor();
	diffuse_color = pixel_color*0.05;
	Vector normale = spheres[indice_closest].computeNormale(intersections[indice_closest]);
	normale.normalize();
	for(int j=0;j<number_of_lights;j++)
	{
		this_diffuse_color = pixel_color;
		shadow_factor = computeShadow(intersections[indice_closest], spheres, number_of_spheres,lights[j],indice_closest); // penser à mettre l'atténuation dedans
		Vector ray_to_light = lights[j].getSource()-intersections[indice_closest];
		ray_to_light.normalize();
		this_diffuse_color = this_diffuse_color*shadow_factor*((ray_to_light*normale)>0?(ray_to_light*normale):0)*(spheres[indice_closest].Object::getDiffuseFactor());
		this_diffuse_color = this_diffuse_color*lights[j].getColor()*lights[j].getColor()*lights[j].getIntensity();
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
void tabToBMP(Color *image, int w, int h, std::string filename)
{
	FILE *f;
	int dpi = 500;
	int k=w*h;
	int s=4*k;
	int filesize = 54 + s;
	
	double factor=39.375;
	int m=static_cast<int>(factor);
	
	int ppm=dpi*m;
	
	unsigned char bmpfileheader[14]={'B', 'M',0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40]={40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
	
	bmpfileheader[ 2]=(unsigned char)(filesize);
	bmpfileheader[ 3]=(unsigned char)(filesize>>8);
	bmpfileheader[ 4]=(unsigned char)(filesize>>16);
	bmpfileheader[ 5]=(unsigned char)(filesize>>24);
	
	bmpinfoheader[4]=(unsigned char)(w);
	bmpinfoheader[5]=(unsigned char)(w>>8);
	bmpinfoheader[6]=(unsigned char)(w>>16);
	bmpinfoheader[7]=(unsigned char)(w>>24);
	
	bmpinfoheader[8]=(unsigned char)(h);
	bmpinfoheader[9]=(unsigned char)(h>>8);
	bmpinfoheader[10]=(unsigned char)(h>>16);
	bmpinfoheader[11]=(unsigned char)(h>>24);
	
	bmpinfoheader[21]=(unsigned char)(s);
	bmpinfoheader[22]=(unsigned char)(s>>8);
	bmpinfoheader[23]=(unsigned char)(s>>16);
	bmpinfoheader[24]=(unsigned char)(s>>24);
	
	bmpinfoheader[25]=(unsigned char)(ppm);
	bmpinfoheader[26]=(unsigned char)(ppm>>8);
	bmpinfoheader[27]=(unsigned char)(ppm>>16);
	bmpinfoheader[28]=(unsigned char)(ppm>>24);	
	
	bmpinfoheader[29]=(unsigned char)(ppm);
	bmpinfoheader[30]=(unsigned char)(ppm>>8);
	bmpinfoheader[31]=(unsigned char)(ppm>>16);
	bmpinfoheader[32]=(unsigned char)(ppm>>24);	
	
	f=fopen(filename.c_str(),"wb");
	
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	
	for(int i=0; i<k; i++){
		
		double red=(image[i].getRed())*255;
		double green=(image[i].getGreen())*255;
		double blue=(image[i].getBlue())*255;
		
		unsigned char color[3]={(int)floor(blue),(int)floor(green),(int)floor(red)};
		
		fwrite(color,1,3,f);
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
	Color c(a.getRed()*b.getRed(),a.getGreen()*b.getGreen(),a.getBlue()*b.getBlue());
	return c;
}
Color operator*(double const& a, Color const& b)
{
	Color c(a*b.getRed(),a*b.getGreen(),a*b.getBlue());
	return c;
}
Color operator*(Color const& a, double const& b)
{
	Color c(a.getRed()*b,a.getGreen()*b,a.getBlue()*b);
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
		if(rayon.getDirection().y()<0.01 && rayon.getDirection().z()<0.01 && rayon.getDirection().y()>-0.01 && rayon.getDirection().z()>-0.01)
		{
		
		}
		double t1,t2,r, delta, t;
		double a = (rayon.getDirection())*(rayon.getDirection());
		//double b = rayon.getDirection().x()*rayon.getStart().x()+rayon.getDirection().y()*rayon.getStart().y()+rayon.getDirection().z()*rayon.getStart().z();
		//double b = 2*rayon.getDirection().x()*(rayon.getStart().x()-sphere.getCenter().x())+2*rayon.getDirection().y()*(rayon.getStart().y()-sphere.getCenter().y())+2*rayon.getDirection().z()*(rayon.getStart().z()-sphere.getCenter().z());
		double b = 2*rayon.getDirection().x()*(rayon.getStart().x()-sphere.getCenter().x())+2*rayon.getDirection().y()*(rayon.getStart().y()-sphere.getCenter().y())+2*rayon.getDirection().z()*(rayon.getStart().z()-sphere.getCenter().z());
		//double c = rayon.getStart().x()*rayon.getStart().x()+rayon.getStart().y()*rayon.getStart().y()+rayon.getStart().z()*rayon.getStart().z();
		//double c = rayon.getStart().x()*rayon.getStart().x()+rayon.getStart().y()*rayon.getStart().y()+rayon.getStart().z()*rayon.getStart().z()+sphere.getCenter().x()*sphere.getCenter().x()+sphere.getCenter().y()*sphere.getCenter().y()+sphere.getCenter().z()*sphere.getCenter().z()-2*(sphere.getCenter().x()*rayon.getStart().x()+sphere.getCenter().y()*rayon.getStart().y()+sphere.getCenter().z()*rayon.getStart().z());
		double c =(rayon.getStart().x()-sphere.getCenter().x())*(rayon.getStart().x()-sphere.getCenter().x())+(rayon.getStart().y()-sphere.getCenter().y())*(rayon.getStart().y()-sphere.getCenter().y())+(rayon.getStart().z()-sphere.getCenter().z())*(rayon.getStart().z()-sphere.getCenter().z());
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
			else if(t1<0 && t2>0)
			{
				t=t2;
			}
			else
			{
				t=MAX_DISTANCE;
			}

		}
		else if(delta==0)
			t = -b/2/a;
		else
			t=MAX_DISTANCE;
		Point A= rayon.getStart()+rayon.getDirection()*t;
		return A;

	}
}
double computeShadow(Point p, Sphere *s,int number_of_spheres, Light l,int id)
{
	int i;
	Point* intersections = new Point[number_of_spheres];
	Ray rayon(p, l.getSource()-p);
	Point useless(MAX_DISTANCE,0,0);
	for (i = 0; i <  number_of_spheres; ++i)
	{
		if(i != id)
			intersections[i]=computeIntersection(rayon ,s[i]);
		else
			intersections[i]=useless;
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