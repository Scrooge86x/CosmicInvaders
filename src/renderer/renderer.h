#include "model.h"
#include "shader.h"

class Renderer {
public:
	void Draw(const Model& object, Shader& shader) const;
};