#ifndef __ModuleRenderExercise_h__
#define __ModuleRenderExercise_h__

#include "Module.h"
#include "GL/glew.h"
#include "MathGeoLib.h"

class ModuleRenderExercise : public Module
{
public:
    ModuleRenderExercise();
    ~ModuleRenderExercise();

	bool            Init    ();
	update_status	PreUpdate ();
	update_status   Update  ();
	bool            CleanUp ();
	float4x4 Transform(float3 eye, float3 target);

private:
    unsigned vbo,vao = 0;
	float3 target = { 0,0,0};
	float3 eye = {1,1,5};
	float3 up = { 0,1,0 };
	float triangle[30];
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	float4x4 transformationMatrix;
	float pitch;
};

#endif /* __ModuleRenderExercise_h__ */
