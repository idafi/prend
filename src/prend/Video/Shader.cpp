#include "Video.hpp"

namespace Video
{
	Shader::Shader(const ShaderData * const data, const int dataCount)
	{
		AssertPtr(data);
		AssertSign(dataCount);
		
		programID = glCreateProgram();
		
		// compile shaders, attach compiled objects
		shader_object *objectIDs = new shader_object[dataCount];
		for(int i = 0; i < dataCount; i++)
		{
			objectIDs[i] = LoadShaderObject(data[i]);
			glAttachShader(programID, objectIDs[i]);
		}
		
		// link objects
		glLinkProgram(programID);
		
		// detach and delete shader objects
		for(int i = 0; i < dataCount; i++)
		{
			glDetachShader(programID, objectIDs[i]);
			glDeleteShader(objectIDs[i]);
		}
		
		delete[] objectIDs;
		
		// make sure things went ok
		GLint result;
		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		if(result != GL_TRUE)
		{
			LogProgramError(programID);
			glDeleteProgram(programID);
		}
	}
	
	Shader::~Shader()
	{
		glDeleteProgram(programID);
	}
	
	void Shader::Use() const
	{
		glUseProgram(programID);
	}
	
	void Shader::SetUniform(const char * const name, const float value)
	{
		AssertPtr(name);
		
		GLint loc = glGetUniformLocation(programID, name);
		if(loc > -1)
		{ glUniform1f(loc, value); }
	}
	
	void Shader::SetUniform(const char * const name, const Matrix<4, 4>& value)
	{
		AssertPtr(name);
		
		GLint loc = glGetUniformLocation(programID, name);
		if(loc > -1)
		{ glUniformMatrix4fv(loc, 1, GL_FALSE, value.Data()); }
	}
	
	shader_object Shader::LoadShaderObject(const ShaderData& data)
	{
		shader_object objectID = glCreateShader(data.Type);
		if(objectID > 0)
		{
			std::string srcStr = IO::ReadFile(data.FilePath);
			if(srcStr.length() > 0)
			{
				// load the shader source code and compile it
				const char *src = srcStr.c_str();
				glShaderSource(objectID, 1, (const GLchar **)(&src), NULL);
				glCompileShader(objectID);
				
				// make sure everything went ok
				GLint result;
				glGetShaderiv(objectID, GL_COMPILE_STATUS, &result);
				if(result == GL_TRUE)
				{
					return objectID;
				}
				else
				{ LogShaderError(objectID, data.FilePath); }
			}
			
			glDeleteShader(objectID);
		}
		else
		{ LogError("failed to create shader object"); }
		
		return 0;
	}
	
	void Shader::LogShaderError(const shader_object objectID, const std::string& filePath)
	{
		Assert(objectID > 0, "invalid shader ID");
	
		GLint infoLen;
		glGetShaderiv(objectID, GL_INFO_LOG_LENGTH, &infoLen);

		GLchar *err = new GLchar[infoLen];
		glGetShaderInfoLog(objectID, infoLen, NULL, err);

		LogError("failed to compile shader object at '%s'!\n\n%s", filePath.c_str(), err);
		delete[] err;
	}
	
	void Shader::LogProgramError(const shader_program programID)
	{
		GLint infoLen;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLen);			
		
		GLchar *err = new GLchar[infoLen];
		glGetProgramInfoLog(programID, infoLen, NULL, err);
		
		LogError("failed to link shader program!\n\n%s", err);
		delete[] err;
	}
}