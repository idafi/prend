#include "Video.hpp"

namespace Video
{
	enum VertexAttribute
	{
		ATTR_POSITION,
		ATTR_COLOR
	};
	
	Model::Model(const ModelData& data)
	{		
		// set up buffers
		glGenVertexArrays(1, &vao);
		glGenBuffers(2, vbos);
		glGenBuffers(1, &ibo);
		
		glBindVertexArray(vao);
		
		// add position data
		glBindBuffer(GL_ARRAY_BUFFER, vbos[ATTR_POSITION]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * data.vertexCount, data.positions, GL_STATIC_DRAW);
		glEnableVertexAttribArray(ATTR_POSITION);
		glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		// add color data
		glBindBuffer(GL_ARRAY_BUFFER, vbos[ATTR_COLOR]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * data.vertexCount, data.colors, GL_STATIC_DRAW);
		glEnableVertexAttribArray(ATTR_COLOR);
		glVertexAttribPointer(ATTR_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
		
		// add data indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16) * data.indexCount, data.indices, GL_STATIC_DRAW);
		
		glBindVertexArray(0);
		
		indexCount = data.indexCount;
	}
	
	Model::~Model()
	{
		glDeleteBuffers(1, &ibo);
		glDeleteBuffers(2, vbos);
		glDeleteVertexArrays(1, &vao);
	}
	
	void Model::Draw() const
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
	}
}