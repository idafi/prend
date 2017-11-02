#include "Video.hpp"

namespace Video
{
	Material::Material(Shader& shader) : shader(shader) { }
	
	void Material::SetAttribute(const char *name, float value)
	{
		f1Val[name] = value;
	}
	
	void Material::SetAttribute(const char *name, Matrix<4, 4> value)
	{
		m4Val[name] = value;
	}
	
	void Material::Use() const
	{
		shader.Use();
		
		ApplyAttributes<float>(f1Val);
		ApplyAttributes<Matrix<4, 4>>(m4Val);
	}
}