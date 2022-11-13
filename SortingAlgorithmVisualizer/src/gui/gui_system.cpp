#include "gui_system.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glfw/glfw3.h>

#include "array/sorts/bubble_sort_system.h"
#include "array/sorts/bogo_sort_system.h"
#include "array/sorts/insertion_sort_system.h"
#include "array/sorts/selection_sort_system.h"


#include "helper.h"



GUISystem::GUISystem(GLFWwindow* window) : window(window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    aSystem.SetSorter<BubbleSortSystem>();
    aSystem.generateArray(persistentSize);

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

        if (aSystem.sort().status == ComparisonData::Status::DONE)
            sorted = true;

        if (sorted) {
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

    SortData s = aSystem.getSortData();

    ImGui::Text("sort: %s", s.name.data());
    ImGui::Text("sorted: %s", sorted ? "true" : "false");
    ImGui::Text("swaps: %d", s.swaps);
    ImGui::Text("array accesses: %d", s.array_accesses);

    if(sorting)
        ImGui::Text("time elapsed: %.3f (restarts when sort is cancelled)", ImGui::GetTime() - sortStartTime);
    else
        ImGui::Text("time elapsed: %.3f (restarts when sort is cancelled)", sortFinishTime - sortStartTime);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUISystem::sortingGUI() {

    ImGui::PushItemWidth(100.0f);

    if (ImGui::Button("Sort")) {
        if (!sorted) {
            sorting = true;
            sortStartTime = ImGui::GetTime();
        }

    }



    if (ImGui::BeginCombo("Sort Type", aSystem.getSortData().name.data())) {
        if (ImGui::Button("Bubble Sort")) {
            aSystem.SetSorter<BubbleSortSystem>();
        }
        if (ImGui::Button("Bogo Sort")) {
            aSystem.SetSorter<BogoSortSystem>();
        }
        if (ImGui::Button("Insertion Sort")) {
            aSystem.SetSorter<InsertionSortSystem>();
        }
        if (ImGui::Button("Selection Sort")) {
            aSystem.SetSorter<SelectionSortSystem>();
        }
        ImGui::EndCombo();
    }

    ImGui::Separator();
    ImGui::PopItemWidth();

}

void GUISystem::miscGUI() {
    ImGui::Text("Miscellaneous");
    ImGui::Separator();

    static std::string sync = "Off";

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