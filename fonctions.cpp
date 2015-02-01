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
		pixel_color *= shadow_factor*(raytolight*normale)*objets[indice_closest].GetDiffuseFactor();
		pixel_color *= lights[j].getColor;
	}


	if(objets[indice_closest].hasReflexion())
	{

		ray* new_ray = new ray(intersections[indice_closest], rayon.direction()-2*(normale*rayon.direction())*normale);
		if(current_depth<MAX_RECCURSIVE_DEPTH)
			color_point = lancer_rayon(new_ray, scene, current_depth+1); // A voir plus tard pour passage par reference  /!\
	}
	if(objets[indice_closest].hasRefraction())
	{
		
	}

}