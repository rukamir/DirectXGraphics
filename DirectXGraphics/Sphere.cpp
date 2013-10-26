#include "Sphere.h"

Sphere::Sphere(int id){
	m_id			=	id;
}

Sphere::~Sphere(){
	if (m_Graphics)
		delete m_Graphics;
}