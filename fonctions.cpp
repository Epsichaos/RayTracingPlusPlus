#include "fonctions.h"
#include "parameters.h"
#include <stdio.h>
#include "operators.h"
#include <ctime>
#include <pthread.h>
#include <iostream>
struct thread_data{
	Color *retour;
	Ray rayon;
	Scene *scene;
	int current_depth;
	Face *faces;
	Vector *normales;
	Sphere *spheres;
	Light *lights;
	Camera *cameras;
	int number_of_spheres;
	int number_of_cameras;
	int number_of_lights;
	unsigned int number_of_intersections_mesh;
	Point **tabCenters;
	int i;
	int width;
};
void render(Scene & Mainscene, Color* image, int width, int height)
{
	pthread_t *threads = new pthread_t[height];
	struct thread_data *td= new thread_data[height];
	int i,j,temp;
	clock_t temps_init;
	double pourcentage, temps_restant;
	Vector buffer;
	Point **tabCenters = new Point*[height];	 // Ces tableaux 2D doivent contenir la position du centre des cases
	for (i = 0; i < height; ++i)
		tabCenters[i] = new Point[width];

	Camera activeCamera = Mainscene.getActiveCamera();
	fill_tabX_tabY(tabCenters,activeCamera.getPosition(),activeCamera.getDirection(),activeCamera.getOrientationX(),activeCamera.getOrientationY(),width,height);




	int number_of_spheres = Mainscene.getNumberOfObjects("sphere");
	int number_of_cameras = Mainscene.getNumberOfObjects("camera");
	int number_of_lights = Mainscene.getNumberOfObjects("light");
	unsigned int number_of_intersections_mesh = Mainscene.getNumberOfMeshFaces();
	Sphere* spheres = new Sphere[number_of_spheres];
	Light* lights = new Light[number_of_lights];
	Camera* cameras = new Camera[number_of_cameras];
	Face* faces = new Face[number_of_intersections_mesh];
	Vector* normales = new Vector[number_of_intersections_mesh];


	Mainscene.getFaces(faces);
	Mainscene.getNormales(normales);
	Mainscene.getSpheres(spheres);
	Mainscene.getLights(lights);
	Mainscene.getCameras(cameras);



	for(i=0;i<height;i++)
	{
		temps_init = clock();

		td[i].retour = &(image[i*width]);
		td[i].scene = &Mainscene;
		td[i].current_depth =0;
		td[i].faces = faces;
		td[i].normales = normales;
		td[i].spheres = spheres;
		td[i].lights = lights;
		td[i].cameras = cameras;
		td[i].number_of_spheres = number_of_spheres;
		td[i].number_of_cameras = number_of_cameras;
		td[i].number_of_lights = number_of_lights;
		td[i].number_of_intersections_mesh = number_of_intersections_mesh;
		td[i].width = width;
		td[i].tabCenters = tabCenters;
		td[i].i = i;

		int rc = pthread_create(&threads[i], NULL,lancer_rayon, (void *)&(td[i]));
		if (rc){
			std::cout << "Error:unable to create thread," << rc << std::endl;
		}

	}
	for( i=0; i < height; i++ ){
				pthread_join (threads[i], NULL);
				
	}
		/*pourcentage = 100*((i+1)*width);
		pourcentage/=height;
		pourcentage/=width;
		temps_restant = (100-pourcentage)*(double)(clock()-temps_init)/(pourcentage/(i+1))/CLOCKS_PER_SEC;
		if(temps_restant/60<1)
		{
			printf("%f secondes restantes \n",temps_restant );

		}
		else
		{
			printf("%f minutes de calcul restantes \n",temps_restant/60 );
		}
*/
		delete[] spheres;
		delete[] lights;
		delete[] cameras;
		delete[] faces;
		delete[] normales;
		for (i = 0; i < height; ++i)
			delete[] tabCenters[i];
		delete[] tabCenters;

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

	void* lancer_rayon(void* arg)
	{
		struct thread_data *my_data;
		my_data = (struct thread_data *) arg;
		Color* retour = my_data->retour;
		Scene *scene = my_data->scene;
		int current_depth =my_data->current_depth;
		Face *faces = my_data->faces;
		Vector *normales = my_data->normales;
		Sphere *spheres = my_data->spheres;
		Light *lights = my_data->lights;
		Camera *cameras = my_data->cameras;
		Point **tabCenters = my_data->tabCenters;
		int width = my_data->width;
		int number_of_spheres = my_data->number_of_spheres;
		int number_of_cameras = my_data->number_of_cameras;
		int number_of_lights = my_data->number_of_lights;
		int t = my_data->i;
		Vector buffer;
		unsigned int number_of_intersections_mesh = my_data->number_of_intersections_mesh;
		Ray rayon;

		Point* intersections = new Point[number_of_spheres];
		Point* intersections2 = new Point[number_of_intersections_mesh];
		int sortie_deja_definie;
		for (int j = 0; j < width; ++j)
		{
			sortie_deja_definie =0;
			rayon.setStart((*scene).getActiveCamera().getPosition());
			buffer = tabCenters[t][j]-(*scene).getActiveCamera().getPosition();
			buffer.normalize();
			rayon.setDirection(buffer); // en X puis en Y
			Color pixel_color;
			bool mesh_closest=false;
			int indice_closest;
			int indice_closest2;
			Color this_diffuse_color;
			Color color_point, color_black(0,0,0),diffuse_color;
			double shadow_factor;
			for(int i=0;i<number_of_spheres;i++)
			{
				intersections[i] = computeIntersection(rayon,spheres[i]);
			}
			for(int i=0;i<number_of_intersections_mesh;i++)
			{
				intersections2[i] = computeIntersection(rayon,faces[i], normales[i]);
			}
			indice_closest = findClosest(rayon, intersections,number_of_spheres);
			indice_closest2 = findClosest(rayon, intersections2,number_of_intersections_mesh);
			if(indice_closest==-1 && indice_closest2==-1)
			{
				*(retour+j) = color_black;
				sortie_deja_definie =1;
			}
			else if(indice_closest != -1 && indice_closest2==-1)
				pixel_color = spheres[indice_closest].getColor();
			else if(indice_closest == -1 && indice_closest2!=-1)
			{
				mesh_closest=true;
				pixel_color = faces[indice_closest2].getColor();
			}
			else
			{
				if((intersections[indice_closest]-rayon.getStart()).getNorm()<(intersections2[indice_closest2]-rayon.getStart()).getNorm())
				{
					pixel_color = spheres[indice_closest].getColor();
				}
				else
				{
					mesh_closest=true;
					pixel_color = faces[indice_closest2].getColor();
				}
			}
				diffuse_color = pixel_color*0.05;
				Vector normale = (mesh_closest?normales[indice_closest2]:spheres[indice_closest].computeNormale(intersections[indice_closest]));
				normale.normalize();
				for(int j=0;j<number_of_lights;j++)
				{
					this_diffuse_color = pixel_color;
		shadow_factor = (mesh_closest?computeShadow(intersections2[indice_closest2], faces,normales, number_of_intersections_mesh,lights[j],indice_closest2):computeShadow(intersections[indice_closest], spheres, number_of_spheres,lights[j],indice_closest)); // penser à mettre l'atténuation dedans
		Vector ray_to_light = lights[j].getSource()-(mesh_closest?intersections2[indice_closest2]:intersections[indice_closest]);
		ray_to_light.normalize();
		this_diffuse_color = this_diffuse_color*shadow_factor*((ray_to_light*normale)>0?(ray_to_light*normale):0)*((mesh_closest?1.0:spheres[indice_closest].Object::getDiffuseFactor()));
		this_diffuse_color = this_diffuse_color*lights[j].getColor()*lights[j].getColor()*lights[j].getIntensity();
		diffuse_color= diffuse_color + this_diffuse_color;
	}
	if(sortie_deja_definie!=1)
		*(retour+j) = diffuse_color;

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
delete[] intersections;
delete[] intersections2;
return NULL;
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
Point computeIntersection(Ray rayon, Face face, Vector normale)
{
	Point useless;
	useless = rayon.getStart()+rayon.getDirection()*MAX_DISTANCE;
	double xa = face.p1().x();
	double ya = face.p1().y();
	double za = face.p1().z();
	double a = normale.x();
	double b = normale.y();
	double c = normale.z();
	double e = rayon.getDirection().x();
	double f = rayon.getDirection().y();
	double g = rayon.getDirection().z();
	double xb = rayon.getStart().x();
	double yb = rayon.getStart().y();
	double zb = rayon.getStart().z();
	double t = (a*(xa-xb)+b*(ya-yb)+c*(za-zb))/(a*e+b*f+c*g);
	if(t<=0)
	{
		return useless;
	}
	double xm = xb+t*e;
	double ym = yb+t*f;
	double zm = zb+t*g;
	Point intersect(xm,ym,zm);
	Vector app(xm-xa,ym-ya,zm-za);
	Vector v1 = face.p2()-face.p1();
	Vector v2 = face.p3()-face.p1();
	v1.normalize();
	v2.normalize();
	app.normalize();
	double angle1 = acos(v2*v1);
	double angle2 = acos(app*v1);
	if(angle2>angle1+0.00001)
	{
		return useless;
	}
	else
	{
		angle1 = acos(v2*v1);
		angle2 = acos(app*v2);
		if(angle2>angle1+0.00001)
			return useless;
		else
		{
			Vector app(xm-face.p2().x(),ym-face.p2().y(),zm-face.p2().z());
			v1 = face.p1()-face.p2();
			v2 = face.p3()-face.p2();
			v1.normalize();
			v2.normalize();
			app.normalize();
			angle1 = acos(v2*v1);
			angle2 = acos(app*v1);
			if(angle2>angle1+0.00001)
				return useless;
			else
				return intersect;
		}
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
	{
		delete[] intersections;
		return 0.0;
	}
	else 
	{
		delete[] intersections;
		return 1.0;
	}
}

double computeShadow(Point p, Face *f,Vector *n, unsigned int number_of_faces, Light l,int id)
{
	int i;
	Point* intersections = new Point[number_of_faces];
	Ray rayon(p, l.getSource()-p);
	Point useless(MAX_DISTANCE,0,0);
	for (i = 0; i <  number_of_faces; ++i)
	{
		if(i != id)
			intersections[i]=computeIntersection(rayon ,f[i],n[i]);
		else
			intersections[i]=useless;
	}
	if(findClosest(rayon, intersections, number_of_faces)>-1)
	{
		delete[] intersections;
		return 0.0;
	}
	else 
	{
		delete[] intersections;
		return 1.0;
	}
	
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