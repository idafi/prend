#pragma once

// - - - - - -
// Compiled GLSL shader program, used to create Materials
// - - - - - -

#include <GL/glew.h>
#include <string>
#include "Video.hpp"

namespace Video
{
	typedef GLuint shader_program;
	typedef GLuint shader_object;
	
	struct ShaderData
	{
		std::string FilePath;
		GLenum Type;
		
		ShaderData(const std::string& filePath, const GLenum type)
		{
			FilePath = filePath;
			Type = type;
		}
	};
	
	class Shader
	{
		public:
			Shader(const ShaderData * const data, const int dataCount);
			~Shader();
			
			void Use() const;
			
			void SetUniform(const char * const name, const float value);
			void SetUniform(const char * const name, const Matrix<4, 4>& value);
			
		private:
			shader_program programID;
			
			shader_object LoadShaderObject(const ShaderData& data);
			void LogShaderError(const shader_object objectID, const std::string& filePath);
			void LogProgramError(const shader_program program);
	};
}