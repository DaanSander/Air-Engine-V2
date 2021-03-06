#include "VertexArray.h"

namespace engine {
	namespace buffer {

		VertexArray::VertexArray(std::vector<fl32> data, std::vector<unsigned int> indices) {
			glGenVertexArrays(1, &mBufferID);
			glBindVertexArray(mBufferID);

			mElementBuffer = new BufferObject(GL_ELEMENT_ARRAY_BUFFER, (void*)&indices[0], indices.size() * sizeof(uint32));
			mVertexBuffer = new BufferObject(GL_ARRAY_BUFFER, (void*)&data[0], data.size() * sizeof(fl32));
			//glBindBuffer(GL_ARRAY_BUFFER, VBO);

			//glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(fl32), (void*)&data[0], GL_STATIC_DRAW);
			/*
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(fl32), (void *) NULL);
			*/
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), (void*)&indices[0], GL_STATIC_DRAW);

			//glBindVertexArray(mBufferID);
			
		}

		VertexArray::VertexArray(const void* data, uint32 size, std::vector<unsigned int> indices) {
			glGenVertexArrays(1, &mBufferID);
			glBindVertexArray(mBufferID);

			mElementBuffer = new BufferObject(GL_ELEMENT_ARRAY_BUFFER, (void*)&indices[0], indices.size() * sizeof(unsigned int));
			mVertexBuffer = new BufferObject(GL_ARRAY_BUFFER, data, size);
		}

		VertexArray::~VertexArray() {
			//glDeleteBuffers(1, &VBO);
			delete mVertexBuffer;
			delete mElementBuffer;
			glDeleteVertexArrays(1, &mBufferID);
		}

		void VertexArray::assignAttribPointer(uint32 index, unsigned int size, uint32 dataType, uint32 stride,
			void* offset, const BufferObject* bufferObject, GLboolean normalized) {

			bind();
			if (bufferObject != 0)
				bufferObject->bind();

			if (!isBound(GL_ARRAY_BUFFER)) {
				std::cout << "ERROR: No array buffer currently bound!" << std::endl;
					return;
			}

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, size, dataType, normalized, stride, offset);
		}

		void VertexArray::setAttribDivisor(uint32 index, uint32 value) const {
			bind();
			glVertexAttribDivisor(index, value);
		}

		void VertexArray::bind() const {
			glBindVertexArray(mBufferID);
			boundBuffers[GL_VERTEX_ARRAY] = mBufferID;
		}

		void VertexArray::unBind() const {
			glBindVertexArray(0);
			boundBuffers[GL_VERTEX_ARRAY] = 0;
		}
	}
}