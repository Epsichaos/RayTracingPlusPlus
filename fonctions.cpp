lancer_rayon(ray rayon, scene scene, int current_depth)
{
	color pixel_color;
	int number_of_objects=0;
	int indice_closest;
	color color_point;
	number_of_objects = scene.getNumberOfObjects();
	object* objets = new object[number_of_objects];
	point* intersections = new point[number_of_objects];
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
void tabToBMP(double r, double v, double b, int w, int h, string path)
{
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
			r = red[i][j]*255;
			g = green[i][j]*255;
			b = blue[i][j]*255;
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