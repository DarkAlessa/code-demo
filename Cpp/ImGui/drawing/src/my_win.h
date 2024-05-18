#ifndef MY_WIN
#define MY_WIN

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"

extern ImVec4 clear_color;

void dockspace();
void properties_window();
void drawing_area();

#endif