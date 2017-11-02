#include "../prend/prend.hpp"
#include "ModelThing.hpp"

using namespace Core;
using namespace Video;

ConsoleLogger *cLog;
FileLogger *fLog;

Matrix<4, 4> clipMatrix;

Window *window;
Shader *shader;
Material *material;
Model *model;

float CalcFrustumScale(float fov)
{
	const float degToRad = (float)(M_PI * 2.0f / 360.0f);
	float rad = fov * degToRad;
	return 1.0f / tan(rad / 2.0f);
}

void CreateClipMatrix()
{
	// un-hardcode this later
	float frustumScale = CalcFrustumScale(45.0f);
	float zNear = 1.0f;
	float zFar = 45.0f;
	
	// set up the matrix
	clipMatrix.Set(0, 0, frustumScale);
	clipMatrix.Set(1, 1, frustumScale);
	clipMatrix.Set(2, 2, (zFar + zNear) / (zNear - zFar));
	clipMatrix.Set(2, 3, -1.0f);
	clipMatrix.Set(3, 2, (2 * zFar * zNear) / (zNear - zFar));
}

Vector4 GetPosA()
{
	return Vector4(0.0f, 0.0f, -20.0f, 1.0f);
}

Vector4 GetPosB(float totalTime)
{
	// slerp settings
	const float fLoopDuration = 3.0f;
	const float fScale = (float)(M_PI * 2.0f / fLoopDuration);

	// loop t
	float fCurrTimeThroughLoop = fmodf(totalTime, fLoopDuration);

	// slerp position
	return Vector4(cosf(fCurrTimeThroughLoop * fScale) * 4.f,
		sinf(fCurrTimeThroughLoop * fScale) * 6.f,
		-20.0f,
		1.0f);
}

Vector4 GetPosC(float totalTime)
{
	// slerp settings
	const float fLoopDuration = 12.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	// loop t
	float fCurrTimeThroughLoop = fmodf(totalTime, fLoopDuration);

	// slerp position
	return Vector4(cosf(fCurrTimeThroughLoop * fScale) * 5.f,
		-3.5f,
		sinf(fCurrTimeThroughLoop * fScale) * 5.f - 20.0f,
		1.0f);
}

bool Init()
{
	// set up log
	cLog = new ConsoleLogger();
	fLog = new FileLogger("log.txt");		

	Logger::Default().AddLogger(cLog, LOG_DEBUG);
	Logger::Default().AddLogger(fLog, LOG_WARNING);
	
	Core::Init();
	Video::Init();
	
	CreateClipMatrix();
	
	// create window
	PixelRect wRect(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500);
	window = new Window("prend", wRect);
	
	// create shader program
	ShaderData vert("../../data/shader.vert", GL_VERTEX_SHADER);
	ShaderData frag("../../data/shader.frag", GL_FRAGMENT_SHADER);
	ShaderData shaderData[2] = { vert, frag };
	shader = new Shader(shaderData, 2);
	
	// create model material
	material = new Material(*shader);
	material->SetAttribute("cameraToClipMatrix", clipMatrix);
	
	// import model data
	FBXImporter importer;
	ModelData *data = importer.ImportModel("../../data/hello.fbx");
	if(!data)
	{ throw std::runtime_error("whoops! could't read model data from fbx"); }

	// create model
	model = new Model(*data);
	
	delete data;
	return true;
}

bool ShouldQuit()
{
	return SDL_QuitRequested();
}

void Frame()
{
	// clear window
	Vector4 clearColor(0.0f, 0.0f, 0.0f, 0.0f);
	window->Clear(clearColor, 1.0f);
	
	// get color interpolation time
	uint32 ticks = SDL_GetTicks();
	float totalTime = (float)(ticks) / 1000;
	float t = (float)(ticks % 5000) / 5000;
	material->SetAttribute("t", t);
	
	// init model transform matrix
	Matrix<4, 4> modelMatrix = Matrix<4, 4>::Identity();
	
	// draw first model using fixed position
	Vector4 posA = GetPosA();
	modelMatrix.SetColumn(3, posA);
	material->SetAttribute("modelToCameraMatrix", modelMatrix);
	window->DrawModel(*model, *material);
	
	// draw second model using slerped position
	Vector4 posB = GetPosB(totalTime);
	modelMatrix.SetColumn(3, posB);
	material->SetAttribute("modelToCameraMatrix", modelMatrix);
	window->DrawModel(*model, *material);
	
	// draw third model using a different slerped position
	Vector4 posC = GetPosC(totalTime);
	modelMatrix.SetColumn(3, posC);
	material->SetAttribute("modelToCameraMatrix", modelMatrix);
	window->DrawModel(*model, *material);
	
	window->Present();
	
	SDL_Delay(16);
}

int Quit(int code)
{
	delete model;
	delete material;
	delete shader;
	delete window;
	
	Video::Quit();
	Core::Quit();
	
	Logger::Default().RemoveLogger(fLog);
	Logger::Default().RemoveLogger(cLog);
	
	delete fLog;
	delete cLog;
	
	return code;
}

int main(int argc, char **argv)
{
	if(::Init())
	{
		while(!::ShouldQuit())
		{ ::Frame(); }
		
		return ::Quit(0);
	}
	
	return ::Quit(1);
}