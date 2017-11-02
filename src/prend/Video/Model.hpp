#pragma once

// - - - - - -
// Drawable collection of vertex buffers and associated data
// - - - - - -

#include <GL/glew.h>
#include "Video.hpp"

namespace Video
{
	typedef GLuint vertex_array;
	typedef GLuint vertex_buffer;
	typedef GLuint index_buffer;
	
	struct ModelData
	{
		const float * const positions;
		const float * const colors;
		const int vertexCount;
		
		const uint16 * const indices;
		const int indexCount;
		
		ModelData(const float * const positions, const float * const colors, const int vertexCount,
		const uint16 * const indices, const int indexCount) :
			positions(positions),
			colors(colors),
			vertexCount(vertexCount),
			indices(indices),
			indexCount(indexCount)
		{
			AssertPtr(positions);
			AssertPtr(colors);
			AssertSign(vertexCount);
			AssertPtr(indices);
			AssertSign(indexCount);
		}
		
		~ModelData()
		{
			delete[] positions;
			delete[] colors;
			delete[] indices;
		}
	};
	
	class Model
	{
		public:
			Model(const ModelData& data);
			~Model();
			
			void Draw() const;
		private:
			vertex_array vao;
			vertex_buffer vbos[2];
			index_buffer ibo;
			
			int indexCount;
	};
}