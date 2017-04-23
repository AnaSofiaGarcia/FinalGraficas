#include <glm/glm.hpp>

class Ray
{
public:
	Ray();
	void CreatRay(glm::vec3 o, glm::vec3 d);
	~Ray();

private:
	glm::vec3 _origin;
	glm::vec3 _direction; 
};
