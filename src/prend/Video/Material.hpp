#pragma once

// - - - - - -
// Instance of a Shader + "attributes" (uniform variables), used by a Model
// - - - - - -

#include <map>
#include "Video.hpp"

namespace Video
{
	class Material
	{
		public:
			Material(Shader& shader);
			
			void SetAttribute(const char *name, float value);
			void SetAttribute(const char *name, Matrix<4, 4> value);
			
			void Use() const;
			
		private:
			Shader& shader;
			
			std::map<const char *, float> f1Val;
			std::map<const char *, Matrix<4, 4>> m4Val;
			
			template<typename T>
			void ApplyAttributes(std::map<char const *, T> attributes) const
			{
				for(auto pair : attributes)
				{ shader.SetUniform(pair.first, pair.second); }
			}
	};
}