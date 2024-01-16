#include "gui_system.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glfw/glfw3.h>

#include "array/sorts/bubble_sort_system.h"
#include "array/sorts/insertion_sort_system.h"
#include "array/sorts/gnome_sort_system.h"
#include "array/sorts/cycle_sort_system.h"


#include "helper.h"

#include <format>


double t = 0, t0 = 0, fps = 0;
int frames = 0;


GUISystem::GUISystem(GLFWwindow* window) : window(window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    aSystem.SetSorter<BubbleSortSystem>();
    aSystem.generateArray(persistentSize);

    t0 = glfwGetTime();

}

float realFPS = 20;
double lastUpdateTime = 0;  // number of seconds since the last loop
double lastFrameTime = 0;

void GUISystem::update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoScrollbar);

    double now = glfwGetTime();
    double deltaTime = now - lastUpdateTime;

    if (!sorting) {
        
            sortingGUI();
            generationGUI();
            renderingGUI();
            miscGUI();

    }
    else {


        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            if (showMouseDuringSort == false)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            sorting = false;
            goto exit_sort;
        }

        if (showSortUI) {
            ImGui::Text("ESC to cancel...");
            ImGui::Separator();
        }

        if ((now - lastFrameTime) >= fpsLimit)
        {
            if (aSystem.sort().status == SwapStatus::DONE) {

                if (showMouseDuringSort == false)
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                sorting = false;
                sorted = true;
            }

            lastFrameTime = now;
        }

        lastUpdateTime = now;


    }
    exit_sort:
        
    ImGui::End();

    if (showSortUI) {

        ImGui::Begin("Statistics", nullptr,
            ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar);

        SortData s = aSystem.getSortData();


        ImGui::Text("sort: %s", s.name.data());
        ImGui::Text("sorted: %s", sorted ? "true" : "false");
        ImGui::Text("swaps: %d", s.swaps);
        ImGui::Text("array accesses: %d", s.array_accesses);

        ImGui::End();
    }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUISystem::sortingGUI() {

    ImGui::PushItemWidth(100.0f);

    if (ImGui::Button("Sort") ) {
        if (!sorted) {
            if (showMouseDuringSort == false) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }

            sorting = true;
        }

    }


    if (ImGui::BeginCombo("Sort Type", aSystem.getSortData().name.data())) {
        if (ImGui::Button("Bubble Sort")) {
            aSystem.SetSorter<BubbleSortSystem>();
        }
        if (ImGui::Button("Insertion Sort")) {
            aSystem.SetSorter<InsertionSortSystem>();
        }
        if (ImGui::Button("Gnome Sort")) {
            aSystem.SetSorter<GnomeSortSystem>();
        }
        if (ImGui::Button("Cycle Sort")) {
            aSystem.SetSorter<CycleSortSystem>();
        }
        ImGui::EndCombo();
    }

    ImGui::Separator();
    ImGui::PopItemWidth();

}
void GUISystem::miscGUI() {
    ImGui::Text("Miscellaneous");
    ImGui::Separator();
    
    if (ImGui::DragFloat("Simulation Framerate", &realFPS, 2, 0.1f, 2000, "%.1f", ImGuiSliderFlags_Logarithmic)) {
        fpsLimit = 1 / realFPS;
    }

    if (ImGui::Button(std::format("Show sorting UI statistics({})", showSortUI).c_str())) {
        showSortUI = !showSortUI;
    }
    if (ImGui::Button(std::format("Show mouse during sort({})", showMouseDuringSort).c_str())) {
        showMouseDuringSort = !showMouseDuringSort;
    }
    if (aSystem.mesh.renderMode == ArrayMesh2D::ArrayMeshRenderMode::HARD) {
        if (ImGui::Button("Rendering mode(HARD)")) {
            aSystem.mesh.renderMode = ArrayMesh2D::ArrayMeshRenderMode::SMOOTH;
            aSystem.mesh.generateMesh(aSystem.sArray);
        }
    }
    else if (aSystem.mesh.renderMode == ArrayMesh2D::ArrayMeshRenderMode::SMOOTH) {
        if (ImGui::Button("Rendering mode(SMOOTH)")) {
            aSystem.mesh.renderMode = ArrayMesh2D::ArrayMeshRenderMode::HARD;
            aSystem.mesh.generateMesh(aSystem.sArray);
        }
    }

}

void GUISystem::generationGUI() {

    ImGui::Text("Generation");
    ImGui::Separator();

    ImGui::PushItemWidth(100.0f);
    if (DragU32("Array Elements", &persistentSize, 5, 5000)) {
        aSystem.generateArray(persistentSize);
        sorted = true;
    }
    if (ImGui::Button("Shuffle")) {
        aSystem.shuffle();
        sorted = false;
    }

    ImGui::Separator();
    ImGui::PopItemWidth();
}

void GUISystem::renderingGUI() {

    ImGui::Text("Rendering");
    ImGui::Separator();

    ImGui::PushItemWidth(200.0f);

    ImGui::Separator();
    ImGui::PopItemWidth();
}