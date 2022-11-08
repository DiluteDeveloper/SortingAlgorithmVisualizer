#include "gui_system.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glfw/glfw3.h>

#include "array/sorts/bubble_sort_system.h"
#include "array/sorts/bogo_sort_system.h"


#include "helper.h"



GUISystem::GUISystem(GLFWwindow* window) : window(window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    aSystem = std::make_unique<ArraySystem>(persistentSize, persistentHeightComplexity);

}

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

    if (!sorting) {
        sortingGUI();
        generationGUI();
        renderingGUI();
        miscGUI();
    }
    else {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            sorting = false;
            sortFinishTime = ImGui::GetTime();
            goto exit_sort;
        }

        ImGui::Text("ESC to cancel...");
        ImGui::Separator();

        aSystem->sort();

        if (aSystem->aSorted) {
            sortFinishTime = ImGui::GetTime();
            sorting = false;
        }
    }
    exit_sort:
        
    ImGui::End();

    ImGui::Begin("Statistics", nullptr,
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar);

    SortData s = aSystem->getSortData();

    ImGui::Text("sorted: %s", aSystem->aSorted ? "true" : "false");
    ImGui::Text("swaps: %d", s.swaps);
    ImGui::Text("comparisons: %d", s.comparisons);
    ImGui::Text("iterations: %d", s.iterations);

    if(sorting)
        ImGui::Text("time elapsed: %.3f (restarts when sort is cancelled)", ImGui::GetTime() - sortStartTime);
    else
        ImGui::Text("time elapsed: %.3f (restarts when sort is cancelled)", sortFinishTime - sortStartTime);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUISystem::sortingGUI() {

    ImGui::Text("Sorting");
    ImGui::Separator();

    ImGui::PushItemWidth(100.0f);

    if (ImGui::Button("Sort")) {
        if (!aSystem->aSorted) {
            sorting = true;
            sortStartTime = ImGui::GetTime();
        }

    }



    if (ImGui::BeginCombo("Sort Type", aSystem->getSortData().name.data())) {
        if (ImGui::Button("Bubble Sort")) {
            aSystem->SetSorter<BubbleSortSystem>();
        }

        ImGui::EndCombo();
    }

    ImGui::Separator();
    ImGui::PopItemWidth();

}

void GUISystem::miscGUI() {
    ImGui::Text("Miscellaneous");
    ImGui::Separator();

    static std::string sync = "On";

    if (ImGui::BeginCombo("V Sync", sync.c_str())) {
        if (ImGui::Button("On")) {
            glfwSwapInterval(1);
            sync = "On";
        }
        if (ImGui::Button("Off")) {
            glfwSwapInterval(0);
            sync = "Off";
        }

        ImGui::EndCombo();
    }

    ImGui::Separator();
}

void GUISystem::generationGUI() {

    ImGui::Text("Generation");
    ImGui::Separator();

    ImGui::PushItemWidth(100.0f);
    DragU32("Array Elements", &persistentSize, 5, 500);
    DragU32("Array Height Complexity", &persistentHeightComplexity, 5, 500);

    if (ImGui::Button("Generate Array")) {
        aSystem.reset();
        aSystem = std::make_unique<ArraySystem>(persistentSize, persistentHeightComplexity);
        aSystem->getRenderOptions() = persistentRO;
        aSystem->updateMesh(); // remove this and see what happens
    }

    ImGui::Separator();
    ImGui::PopItemWidth();
}

void GUISystem::renderingGUI() {

    ImGui::Text("Rendering");
    ImGui::Separator();

    ImGui::PushItemWidth(200.0f);
    if (ImGui::DragFloat4("Constraints", &persistentRO.maxRight, 0.1f, -1.0f, 1.0f, "%.2f")) {
        aSystem->getRenderOptions() = persistentRO;
        aSystem->updateMesh();
    }


    ImGui::Separator();
    ImGui::PopItemWidth();
}