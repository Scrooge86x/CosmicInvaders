#include "model.h"
#include "shader.h"

class Renderer {
public:
	void draw(const Model& object, Shader& shader) const;
};