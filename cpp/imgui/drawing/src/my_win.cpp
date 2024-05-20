#include "my_win.h"

ImVec4 clear_color = ImVec4(0.638f, 0.884f, 0.859f, 1.00f);

void dockspace() {
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    // Full Screen
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    window_flags |= ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    
    // Dock space window
    ImGui::Begin("Docking Space", NULL, window_flags);
    // Submit the DockSpace 
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    ImGui::End();

    ImGui::PopStyleVar(3); // pop sll style from ImGui::PushStyleVar
}

void properties_window() {
    ImGuiIO& io = ImGui::GetIO();
    static bool show_metrics_window = false;
    static bool lock_window = false;
    ImGuiWindowFlags imgui_window_flags = 0;
    if (lock_window) imgui_window_flags |= (ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    if (show_metrics_window) ImGui::ShowMetricsWindow();

    ImGui::Begin("Properties", NULL, imgui_window_flags);
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::Text("Frame Time : %.1f ms/frame", 1000.0f / io.Framerate);
    ImGui::Text("Frame Rate : %d FPS", static_cast<int>(io.Framerate));
    ImGui::Separator();
    ImGui::ColorEdit3("BG", (float*)&clear_color, ImGuiColorEditFlags_DisplayRGB);
    ImGui::Separator();
    ImGui::Text("Work Size (%dx%d)", (int)viewport->WorkSize.x, (int)viewport->WorkSize.y);
    ImGui::Text("Viewport Size (%dx%d)", (int)viewport->Size.x, (int)viewport->Size.y);
    ImGui::Text("Work Pos (%d, %d)", (int)viewport->WorkPos.x, (int)viewport->WorkPos.y);
    ImGui::Text("Pos (%d, %d)", (int)viewport->Pos.x, (int)viewport->Pos.y);
    ImGui::Separator();
    ImGui::Checkbox("Lock Window", &lock_window);
    ImGui::Checkbox("Show Metrics Window", &show_metrics_window);
    ImGui::CheckboxFlags("Enable DockSpace", &io.ConfigFlags, ImGuiConfigFlags_DockingEnable);
    ImGui::End();
}

void drawing_area() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    const ImU32 color = ImColor(ImVec4(1.0f, 0.764f, 0.00f, 1.0f));

    ImGui::Begin("Drawing##Drawing");
        const ImVec2 p = ImGui::GetCursorScreenPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddText(ImVec2(p.x + 100.0f,p.y + 100.0f), color, "Hello", NULL);
    ImGui::End();
    ImGui::PopStyleVar(2);
}