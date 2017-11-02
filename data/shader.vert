#version 330

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 _color;

out vec4 color;

void main()
{
	vec4 cameraPos = modelToCameraMatrix * position;
	gl_Position = cameraToClipMatrix * cameraPos;
	
	color = _color;
}