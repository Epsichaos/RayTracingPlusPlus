#include "object.h"
#include <string>
#include "struct.h"

using namespace std;

void Object::setColorObject(Color color_obj) {
    m_mat.setColorMat(color_obj);
}

void Object::setTypeObject(string str) {
    if(str=="camera") {
        //m_type = Camera;
        m_type = 0;
    }
    if(str=="light") {
        //m_type = Light;
        m_type = 1;
    }
    if(str=="cube") {
        //m_type = Cube;
        m_type = 2;
    }
    if(str=="sphere") {
        //m_type = Sphere;
        m_type = 3;
    }
    if(str=="mesh") {
        //m_type = Mesh;
        m_type = 4;
    }
}
