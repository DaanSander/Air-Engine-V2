#include "SimpleRenderer.h"

namespace engine {
	namespace renderer {

		SimpleRenderer::SimpleRenderer() {

		}

		void SimpleRenderer::prepareRender() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void SimpleRenderer::render(const buffer::VertexArray* vertexArray) const {
			glBindVertexArray(vertexArray->getBufferID());

			glDrawElements(GL_TRIANGLES, vertexArray->getIndicesCount(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}
} }