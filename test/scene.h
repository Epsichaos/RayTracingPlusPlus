#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	void loadScene(const std::string path);
	int getNumberOfObjects();
	//int getNumberOfObjects(enum m_type type);
	//void getObjects(Object* input_array);
	//void getObjects(Object* input_array, enum m_type type);
protected:
	int m_objectNumber;
	Object* m_arrayOfObjects;
};

#endif
