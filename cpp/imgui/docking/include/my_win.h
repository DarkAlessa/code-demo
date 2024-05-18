#ifndef MY_WIN
#define MY_WIN

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_sdlrenderer2.h"

extern ImVec4 clear_color;
extern ImVec4 rect_color;

void dockspace();
void my_window();

#endif