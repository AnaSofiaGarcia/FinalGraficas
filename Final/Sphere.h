#include <glm/glm.hpp>


class Sphere
{
public:
	Sphere();
	~Sphere();
	void CreateSphere(glm::vec3 c, float r);

private: 
	glm::vec3 _center;
	float _radius;

};
