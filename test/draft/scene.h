#include "object.h"

class Scene
{
public:
	void load_scene(const string path);
protected:
	int m_objectNumber;
	object* arrayOfObjects;
};
