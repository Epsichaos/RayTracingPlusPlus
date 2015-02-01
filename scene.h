class Scene
{
public:
	void loadScene(const string path);
	int getNumberOfObjects();
	int getNumberOfObjects(enum m_type type);
	void getObjects(object* input_array);
	void getObjects(object* input_array, enum m_type type);
protected:
	m_objectNumber;
	object* arrayOfObjects;
};