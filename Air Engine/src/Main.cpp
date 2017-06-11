#include <glad/glad.h>
#include <algorithm>
#include "graphics/Window.h"
#include "buffers\VertexArray.h"
#include "graphics\renderer\SimpleRenderer.h"

int main() {
	using namespace engine;
	using namespace graphics;
	using namespace buffer;
	using namespace renderer;

	Window* window = new Window("Engine", 800, 600);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	VertexArray* vertexArray = new VertexArray(std::move(vertices));
	SimpleRenderer* renderer = new SimpleRenderer();

	//std::cout << "1" << std::endl;
	
	while (!window->shouldClose()) {
		//std::cout << "2" << std::endl;

		glClear(GL_COLOR_BUFFER_BIT);
		//std::cout << "3" << std::endl;

		renderer->prepareRender();
		//std::cout << "4" << std::endl;

		renderer->render(vertexArray);
		//std::cout << "5" << std::endl;

	}

	vertexArray->unBind();

	delete vertexArray;
	delete renderer;
	delete window;
	

	return 0;
}