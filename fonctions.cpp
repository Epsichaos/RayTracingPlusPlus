#include "fonctions.h"
#include "parameters.h"
#include <stdio.h>
#include "operators.h"
#include <ctime>
#include <pthread.h>
#include <iostream>

struct thread_data{
	Color *retour;
	Scene *scene;
	Face *faces;
	Vector *normales;
	Sphere *spheres;
	Light *lights;
	Camera *cameras;
	int number_of_spheres;
	int number_of_cameras;
	int number_of_lights;
	unsigned int number_of_intersections_mesh;
	Mesh  *mesh;
	Point **tabCenters;
	int i;
	int width;
};

void render(Scene & Mainscene, Color* image, int width, int height)
{
	pthread_t *threads = new pthread_t[height];
	struct thread_data *td= new thread_data[height];
	int i,j;
	clock_t temps_init;
	double pourcentage, temps_restant;
	double temps[K_MOYENNE],sum;
	Vector buffer;
	int index, indexmod;
	// Ces tableaux 2D doivent contenir la position du centre des cases
	Point **tabCenters = new Point*[height];	 
	for (i = 0; i < height; ++i) {
		tabCenters[i] = new Point[width];
	}
	Camera activeCamera = Mainscene.getActiveCamera();
	fill_tabX_tabY(tabCenters,activeCamera.getPosition(),activeCamera.getDirection(),activeCamera.getOrientationX(),activeCamera.getOrientationY(),width,height);
	Ray rayon_init;

	int number_of_spheres = Mainscene.getNumberOfObjects("sphere");
	int number_of_cameras = Mainscene.getNumberOfObjects("camera");
	int number_of_lights = Mainscene.getNumberOfObjects("light");
	unsigned int number_of_intersections_mesh = Mainscene.getNumberOfMeshFaces();
	Sphere* spheres = new Sphere[number_of_spheres];
	Light* lights = new Light[number_of_lights];
	Camera* cameras = new Camera[number_of_cameras];
	Face*  faces = new Face[number_of_intersections_mesh];
	Vector*  normales = new Vector[number_of_intersections_mesh];
	Mesh* mesh= new Mesh();

	Mainscene.getFaces(faces);
	Mainscene.getNormales(normales);
	Mainscene.getSpheres(spheres);
	Mainscene.getLights(lights);
	Mainscene.getCameras(cameras);
	Mainscene.getMesh(mesh);
	index=0;
	temps_init = clock();
	for(i=0;i<height;i++)
	{
		//temps_init = clock();
		td[i].retour = &(image[i*width]);
		td[i].scene = &Mainscene;
		td[i].faces = faces;
		td[i].normales = normales;
		td[i].spheres = spheres;
		td[i].lights = lights;
		td[i].cameras = cameras;
		td[i].number_of_spheres = number_of_spheres;
		td[i].number_of_cameras = number_of_cameras;
		td[i].number_of_lights = number_of_lights;
		td[i].number_of_intersections_mesh = number_of_intersections_mesh;
		td[i].number_of_intersections_mesh = number_of_intersections_mesh;
		td[i].mesh=mesh;
		td[i].width = width;
		td[i].tabCenters = tabCenters;
		td[i].i = i;
		indexmod = i%NB_THREADS;
		int rc = pthread_create(&threads[i], NULL,lancer_rayon_thread, (void *)&(td[i]));
		if (rc){
			std::cout << "Error:unable to create thread," << rc << std::endl;
		}
		if(indexmod==NB_THREADS-1)
		{
			for( j=0; j < NB_THREADS; j++ )
			{
				pthread_join (threads[i-j], NULL);
			}
			pourcentage = 100*((i+1)*width);
			pourcentage/=height;
			pourcentage/=width;
			//std::cout<<pourcentage<<" pourcents"<<std::endl;
			if(i<K_MOYENNE)
			{
				temps[i] = (double)(clock()-temps_init);
			}
			else
			{
				sum=0;
				for (int k = 0; k < K_MOYENNE-1; ++k)
				{
					temps[k]=temps[k+1];
					sum+=temps[k];
				}	
				temps[K_MOYENNE-1]=(double)(clock()-temps_init);
				sum+=temps[K_MOYENNE-1];
				sum /=K_MOYENNE;
				temps_restant = (100-pourcentage)*(sum/CLOCKS_PER_SEC)/(pourcentage);
				if(temps_restant/60<1)
				{
					std::cout<<temps_restant<<" secondes restantes         "<<std::endl;
				}
				else
				{
					std::cout<<temps_restant/60<<" minutes de calcul restantes "<<std::endl;
				}
				temps_init = clock();

			}
			indexmod=height%NB_THREADS;
			for( j=0; j < indexmod; j++ )
			{
				pthread_join (threads[i+j], NULL);
			}
		}
	}
		
		
			/*		}
		
*/
	//}
		delete[] spheres;
		delete[] lights;
		delete[] cameras;
		delete[] faces;
		delete[] normales;
		for (i = 0; i < height; ++i) {
			delete[] tabCenters[i];
		}
		delete[] tabCenters;
	}

	void fill_tabX_tabY(Point **tabCenters,Point camerapos,Vector cameradir, Vector orientationX,Vector orientationY, int width, int height)
	{
		int i,j;
		for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++)
			{
				double alpha = tan(M_PI/2*VIEWING_ANGLEX/180)*(j-width/2)/(width/2);
				double beta = tan(M_PI/2*VIEWING_ANGLEY/180)*(height/2-i)/(height/2);
				tabCenters[i][j] = camerapos+cameradir*1+orientationX*alpha+orientationY*beta;
			}
		}
	}
	void* lancer_rayon_thread(void* arg)
	{
		struct thread_data *my_data;
		my_data = (struct thread_data *) arg;
		Color *retour= my_data -> retour;
		Scene *scene = my_data-> scene;
		Face *faces = my_data->faces;
		Vector *normales = my_data->normales;
		Sphere *spheres = my_data->spheres;
		Light *lights = my_data->lights;
		Camera *cameras = my_data->cameras;
		int number_of_spheres = my_data->number_of_spheres;
		int number_of_cameras = my_data->number_of_cameras;
		int number_of_lights = my_data->number_of_lights;
		unsigned int number_of_intersections_mesh = my_data->number_of_intersections_mesh;
		Mesh  *mesh = my_data->mesh;
		Point **tabCenters = my_data->tabCenters;
		int width = my_data->width;
		int i = my_data->i;
		Vector buffer;
		Ray rayon_init;
		for (int j = 0; j < width; ++j)
		{
			rayon_init.setStart((*scene).getActiveCamera().getPosition());
			buffer = tabCenters[i][j]-(*scene).getActiveCamera().getPosition();
			buffer.normalize();
		rayon_init.setDirection(buffer); // en X puis en Y
		*(retour+j)= lancer_rayon(rayon_init, *scene,0,faces,normales,spheres,lights,cameras, number_of_spheres, number_of_cameras, number_of_lights, number_of_intersections_mesh,1.0,0,*mesh);
	}


}

Color lancer_rayon(Ray rayon, Scene &scene, int current_depth, Face *faces,Vector *normales, Sphere *spheres, Light *lights,Camera *cameras,int number_of_spheres,int number_of_cameras,int number_of_lights,unsigned	int number_of_intersections_mesh, double  indice_refract, int inside, Mesh & mesh)
{
	Point* intersect_spheres = new Point[number_of_spheres];
	Point* intersect_mesh = new Point[number_of_intersections_mesh];
	Color pixel_color;
	bool mesh_closest=false;
	int indice_closest;
	int indice_closest2;
	Color this_diffuse_color;
	Color color_point, color_black(0,0,0),diffuse_color;
	double shadow_factor;
	for(int i=0;i<number_of_spheres;i++)
	{
		intersect_spheres[i] = computeIntersection(rayon,spheres[i]);

	}
	for(unsigned int i=0;i<number_of_intersections_mesh;i++)
	{
		intersect_mesh[i] = computeIntersection(rayon,faces[i], normales[i]);
	}
	indice_closest = findClosest(rayon, intersect_spheres,number_of_spheres);
	indice_closest2 = findClosest(rayon, intersect_mesh,number_of_intersections_mesh);
	if(indice_closest==-1 && indice_closest2==-1)
	{
		delete[] intersect_spheres;
		delete[] intersect_mesh;
		return color_black;
	}
	else if(indice_closest != -1 && indice_closest2==-1) 
	{
		pixel_color = spheres[indice_closest].getColor();
	}	
	else if(indice_closest == -1 && indice_closest2!=-1)
	{
		mesh_closest=true;
		pixel_color = faces[indice_closest2].getColor();
	}
	else {
		if((intersect_spheres[indice_closest]-rayon.getStart()).getNorm()<(intersect_mesh[indice_closest2]-rayon.getStart()).getNorm())
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
	Vector normale = ((1-inside)*2-1)*(mesh_closest==1?normales[indice_closest2]:spheres[indice_closest].computeNormale(intersect_spheres[indice_closest]));
	normale.normalize();
	double opacity = 1;
	if(mesh_closest!=1)
	{
		if(spheres[indice_closest].hasRefraction()) 
		{
			opacity = 0.05;
			double coeff_fresnel = fresnel(normale, rayon.getDirection(),indice_refract, spheres[indice_closest].getRefraction());
			double cosI = -(normale*rayon.getDirection());
			Vector temp = rayon.getDirection()+2*cosI*normale;
			temp.normalize();
			Ray new_ray = Ray(intersect_spheres[indice_closest], temp);
			Ray rayon_translate = Ray(new_ray.getStart()-normale*0.0001, new_ray.getDirection());	
			
			if(current_depth<MAX_RECCURSIVE_DEPTH_REFLEXION)
			{
				color_point = lancer_rayon(rayon_translate, scene, current_depth+1,faces,normales,
					spheres,lights,cameras,number_of_spheres,number_of_cameras,
			number_of_lights,number_of_intersections_mesh, spheres[indice_closest].getRefraction(),1-inside,mesh); // A voir plus tard pour passage par reference
				diffuse_color = diffuse_color + (1-opacity)*color_point*(coeff_fresnel);
			}

			double n_rapport = indice_refract/spheres[indice_closest].getRefraction();
			double cosXi = -(rayon.getDirection()*normale);
			double sinXr = n_rapport*n_rapport*(1-cosXi*cosXi);

			if(sinXr<=1)
			{
				Vector refractdir = n_rapport*rayon.getDirection()+(n_rapport*cosXi-sqrt(1-sinXr))*normale;
				refractdir.normalize();
				Ray new_ray1 = Ray(intersect_spheres[indice_closest],refractdir);
				Ray rayon_translate = Ray(new_ray1.getStart()-normale*0.0001, new_ray1.getDirection());		
				if(current_depth<MAX_RECCURSIVE_DEPTH_REFRACTION)
				{
					color_point = lancer_rayon(rayon_translate, scene, current_depth+1,
						faces,normales,spheres,lights,cameras,
						number_of_spheres,number_of_cameras,number_of_lights,
						number_of_intersections_mesh,1.0,1-inside,mesh);
					diffuse_color = diffuse_color+ (1-opacity)*color_point*(1-coeff_fresnel);
				}
			}
		}
	}
	else
	{
		if(mesh.hasRefraction()) 
		{
			opacity = 0.05;
			double coeff_fresnel = fresnel(normale, rayon.getDirection(),indice_refract, mesh.getRefraction());
			double cosI = -(normale*rayon.getDirection());
			Vector temp = rayon.getDirection()+2*cosI*normale;
			temp.normalize();
			Ray new_ray = Ray(intersect_mesh[indice_closest2], temp);
			Ray rayon_translate = Ray(new_ray.getStart()-normale*0.001, new_ray.getDirection());	
			
			if(current_depth<MAX_RECCURSIVE_DEPTH_REFLEXION)
			{
				color_point = lancer_rayon(rayon_translate, scene, current_depth+1,faces,normales,
					spheres,lights,cameras,number_of_spheres,number_of_cameras,
			number_of_lights,number_of_intersections_mesh, mesh.getRefraction(),1-inside,mesh); // A voir plus tard pour passage par reference
				diffuse_color = diffuse_color + (1-opacity)*color_point*(coeff_fresnel);
			}

			double n_rapport = indice_refract/mesh.getRefraction();
			double cosXi = -(rayon.getDirection()*normale);
			double sinXr = n_rapport*n_rapport*(1-cosXi*cosXi);

			if(sinXr<=1)
			{
				Vector refractdir = n_rapport*rayon.getDirection()+(n_rapport*cosXi-sqrt(1-sinXr))*normale;
				refractdir.normalize();
				Ray new_ray1 = Ray(intersect_mesh[indice_closest2],refractdir);
				Ray rayon_translate = Ray(new_ray1.getStart()-normale*0.001, new_ray1.getDirection());		
				if(current_depth<MAX_RECCURSIVE_DEPTH_REFRACTION)
				{
					color_point = lancer_rayon(rayon_translate, scene, current_depth+1,
						faces,normales,spheres,lights,cameras,
						number_of_spheres,number_of_cameras,number_of_lights,
						number_of_intersections_mesh,1.0,1-inside,mesh);
					diffuse_color = diffuse_color+ (1-opacity)*color_point*(1-coeff_fresnel);
				}
			}

		}	
	}
	/* Shading	*/
	Color sum_shading(0,0,0);
	Color temp_shading;
	double ks = 0.5; // coefficient speculaire
	
	for(int j=0;j<number_of_lights;j++)
	{
		this_diffuse_color = pixel_color;
		temp_shading = lights[j].getColor();
		shadow_factor=(inside==1?1.0:computeShadow((mesh_closest==true?intersect_mesh[indice_closest2]:intersect_spheres[indice_closest]), spheres, number_of_spheres,lights[j],(mesh_closest==false?indice_closest:-1)));
		
		shadow_factor*=+(0.1*(inside==1?1.0:computeShadow((mesh_closest==true?intersect_mesh[indice_closest2]:intersect_spheres[indice_closest]), faces,normales, number_of_intersections_mesh,lights[j],(mesh_closest==true?indice_closest2:-1)))+0.9);

		Vector ray_to_light = lights[j].getSource()-(mesh_closest?intersect_mesh[indice_closest2]:intersect_spheres[indice_closest]);
		ray_to_light.normalize();
		this_diffuse_color = this_diffuse_color*shadow_factor*((ray_to_light*normale)>0?(ray_to_light*normale):0)*((mesh_closest==1?1.0:spheres[indice_closest].Object::getDiffuseFactor()));
		this_diffuse_color = this_diffuse_color*lights[j].getColor()*lights[j].getColor()*lights[j].getIntensity();
		diffuse_color= diffuse_color + opacity*this_diffuse_color;

		/* Specular shading */
		/* /!\ Ne marche pas /!\<--- Ah en fait si !
		*/
		Camera camera_active = scene.getActiveCamera();
		Vector camera_direction = camera_active.getDirection();
		double cosI = -(normale*rayon.getDirection());
		Vector rayon_reflechi = rayon.getDirection()+2*cosI*normale;
		double cos_Shade =-(camera_direction*rayon_reflechi);
		if(cos_Shade>0) {
			temp_shading = temp_shading * ks * pow(cos_Shade,200);
			diffuse_color = diffuse_color + temp_shading*shadow_factor;
		}
		
	}
	//diffuse_color = diffuse_color + sum_shading;
	//diffuse_color= diffuse_color + this_diffuse_color;
	delete[] intersect_spheres;
	delete[] intersect_mesh;
	return diffuse_color;
}
double fresnel(const Vector& v_normal, const Vector& v_incident,double n1, double n2)
{
	double r0 = (n1-n2)/(n1+n2);
	r0 *= r0;
	double cosx = -(v_normal*v_incident);
	if(n1>n2)
	{
		const double n=n1/n2;
		const double sint2 = n*n*(1.0-cosx*cosx);
		if(sint2>1)
		{
			return 1.0;
		}
		cosx = sqrt(1.0-sint2);
	}
	const double x = 1.0-(cosx>0?cosx:-cosx);
	return r0+(1.0-r0)*x*x*x*x*x;	
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

	for(int i=k; i>0; i--){

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
		double t1,t2,r, delta, t;
		//Eviter de considerer le point de départ comme une intersection
		double a = (rayon.getDirection())*(rayon.getDirection());
		double b = 2*rayon.getDirection().x()*(rayon.getStart().x()-sphere.getCenter().x())+2*rayon.getDirection().y()*(rayon.getStart().y()-sphere.getCenter().y())+2*rayon.getDirection().z()*(rayon.getStart().z()-sphere.getCenter().z());
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
		{
			t = -b/2/a;
		}
		else {
			t=MAX_DISTANCE;
		}
		Point A= rayon.getStart()+rayon.getDirection()*t;
		return A;

	}
	else {
		double t;
		t=MAX_DISTANCE;
		Point A= rayon.getStart()+rayon.getDirection()*t;
		return A;
	}
}

Point computeIntersection(Ray rayon, Face face, Vector normale)
{
	double epsilon = 0.0001;
	Point intersect = rayon.getStart()+rayon.getDirection()*MAX_DISTANCE;;
	Vector u= face.v1();
	Vector v= face.v2();
	Point A= face.p1();
	Vector w = Vector(rayon.getStart().x()-A.x(),rayon.getStart().y()-A.y(),rayon.getStart().z()-A.z());
	double D = -((u^v)*rayon.getDirection());
	double a = -(((w^v)*rayon.getDirection())/D);
	double b = -(((u^w)*rayon.getDirection())/D);
	if(a>-epsilon && b>-epsilon && a+b<=1+epsilon)
	{
		double t = (u^v)*w/D;
		if(t>=epsilon)
		{
			intersect = rayon.getStart()+t*rayon.getDirection();
		}
	}
	return intersect;
}

double computeShadow(Point p, Sphere *s,int number_of_spheres, Light l,int id)
{
	int i;
	Point* intersect_spheres = new Point[number_of_spheres];
	Ray rayon(p, l.getSource()-p);
	Point useless(MAX_DISTANCE,0,0);
	for (i = 0; i <  number_of_spheres; ++i)
	{
		if(i != id)
			intersect_spheres[i]=computeIntersection(rayon ,s[i]);
		else
			intersect_spheres[i]=useless;
	}
	if(findClosest(rayon, intersect_spheres, number_of_spheres)>-1)
	{
		delete[] intersect_spheres;
		return 0.0;
	}
	else
	{
		delete[] intersect_spheres;
		return 1.0;
	}
}

double computeShadow(Point p, Face *f,Vector *n, unsigned int number_of_faces, Light l,int id)
{
	int i;
	Point* intersections = new Point[number_of_faces];
	Ray rayon(p+n[id]*0.0001, l.getSource()-p);
	Point useless(MAX_DISTANCE,0,0);
	for (i = 0; (unsigned int)i <  number_of_faces; ++i)
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