#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "ModuleImgui.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include "IMGUI/imgui_impl_sdl.h"


ModuleImgui::ModuleImgui()
{
}


ModuleImgui::~ModuleImgui()
{
}

bool ModuleImgui::Init()
{
	bool ret = true;
	ImGui_ImplSDL2_InitForOpenGL(, );
	return ret;
}