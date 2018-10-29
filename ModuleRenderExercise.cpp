#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleProgram.h"
#include "ModuleWindow.h"
#include "SDL.h"

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	if (!App->program->program)
	{
		LOG("Error: Program cannot be compiled");
		return false;
	}

	glUseProgram(App->program->program);

	float vertex_buffer_data[] =
	{
		//triangle 1
		1.0f,-1.0f,0.0f,
		-1.0f,1.0f,0.0f,
		-1.0f,-1.0f,0.0f,

		//triangle 2
		1.0f,1.0f,0.0f,
		-1.0f,1.0f,0.0f,
		1.0f,-1.0f,0.0f,

		//triangle 1 uv0
		1.0f,0.0f,
		0.0f,1.0f,
		0.0f,0.0f,

		//triangle 2 uv0
		1.0f,1.0f,
		0.0f,1.0f,
		1.0f,0.0f
	};

	for (int i = 0; i < 30; ++i)
	{
		triangle[i] = vertex_buffer_data[i];
	}



	//for (int i = 0; i < 3; ++i)
	//{
	//	float4 res = Transform(eye, target) * float4(triangle[i], 1.0f);
	//	triangle[i] = res.xyz() / res.w;
	//}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);



    return vbo;
}

update_status ModuleRenderExercise::PreUpdate()
{
	float3 front = eye - target;
	front.Normalize();
	target = eye - front;
	float3 side = front.Cross(up);
	float3 upwards = front.Cross(side);

	side.Normalize();
	side = side / 5;
	upwards = upwards / 5;

	if (App->input->GetKey(SDL_SCANCODE_Q))
	{
		eye += up/5;
		target += up/5;
	}
	if (App->input->GetKey(SDL_SCANCODE_E))
	{
		eye -= up/5;
		target -= up/5;
	}
	if (App->input->GetKey(SDL_SCANCODE_W))
	{
		eye -= front;
		target -= front;
	}
	if (App->input->GetKey(SDL_SCANCODE_S))
	{
		eye += front;
		target += front;
	}
	if (App->input->GetKey(SDL_SCANCODE_A))
	{
		eye += side;
		target += side;
	}
	if (App->input->GetKey(SDL_SCANCODE_D))
	{
		eye -= side;
		target -= side;
	}
	//Accelration isn't adequate but gets job done, missing some tweeking, angle checking

	if (App->input->GetKey(SDL_SCANCODE_DOWN))
	{
		target += upwards/4;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP))
	{
		target -= upwards/4;
	}

	//triangle disappears when looked from behind "SOLVED"

	if (App->input->GetKey(SDL_SCANCODE_LEFT))
	{
		target += side/5;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT))
	{
		target -= side/5;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{

	transformationMatrix = Transform(eye, target);



	glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
	

	float4x4 Model(math::float4x4::identity); // Not moving anything

	glUniformMatrix4fv(glGetUniformLocation(App->program->program, "model"), 1, GL_TRUE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program, "view"), 1, GL_TRUE, &App->exercise->viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program, "proj"), 1, GL_TRUE, &App->exercise->projectionMatrix[0][0]);

	//AXIS

	glLineWidth(2.0f);

	// red X
	int xAxis = glGetUniformLocation(App->program->program, "newColor");
	float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glUniform4fv(xAxis, 1, red);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);
	glEnd();

	// green Y
	int yAxis = glGetUniformLocation(App->program->program, "newColor");
	float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	glUniform4fv(yAxis, 1, green);

	glBegin(GL_LINES);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);
	glEnd();

	// blue Z
	int zAxis = glGetUniformLocation(App->program->program, "newColor");
	float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glUniform4fv(zAxis, 1, blue);

	glBegin(GL_LINES);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);
	glEnd();

	//GRID

	glLineWidth(1.0f);
	float d = 200.0f;
	glBegin(GL_LINES);
	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}
	glEnd();

	

	int fragUnifLocation = glGetUniformLocation(App->program->program, "newColor");
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glUniform4fv(fragUnifLocation, 1, color);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // number of componentes (3 floats)
		GL_FLOAT,           // data type
		GL_FALSE,           // should be normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,
		(void*)(sizeof(float) * 3 * 6) // buffer offset
	);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, App->textures->loadImg("../Lenna.png"));
	glUniform1i(glGetUniformLocation(App->program->program, "texture0"), 0);

	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 6 vertices total -> 2 triangle
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	

	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    if(vbo != 0)
    {
        glDeleteBuffers(1, &vbo);
    }

	return true;
}


float4x4 ModuleRenderExercise::Transform(float3 eye, float3 target)
{
	float4x4 resultMatrix;

	float3 f(target - eye);
	f.Normalize();
	float3 s(f.Cross(up));
	s.Normalize();
	float3 u(s.Cross(f));

	viewMatrix[0][0] = s.x; viewMatrix[0][1] = s.y; viewMatrix[0][2] = s.z; viewMatrix[3][0] = 0;
	viewMatrix[1][0] = u.x; viewMatrix[1][1] = u.y; viewMatrix[1][2] = u.z; viewMatrix[3][1] = 0;
	viewMatrix[2][0] = -f.x; viewMatrix[2][1] = -f.y; viewMatrix[2][2] = -f.z; viewMatrix[3][2] = 0;
	viewMatrix[0][3] = -s.Dot(eye); viewMatrix[1][3] = -u.Dot(eye); viewMatrix[2][3] = f.Dot(eye); viewMatrix[3][3] = 1;

	Frustum frustum;
	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)) * aspect;
	math::float4x4 proj = frustum.ProjectionMatrix();

	this->viewMatrix = viewMatrix;
	this->projectionMatrix = proj;

	resultMatrix = proj * viewMatrix;


	return resultMatrix;
}