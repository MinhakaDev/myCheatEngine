#include "Menu.h"
#include "imgui.h"
#include <cstdint>
#include <cstdlib>
#include <print>


void Menu::renderSelected()
{
}

void Menu::renderResults()
{
    std::vector<uintptr_t> memoryAddrList = sc.getMemoryAddrList();
    
    if (ImGui::BeginTable("results", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Address");
        ImGui::TableSetupColumn("Value");
        ImGui::TableHeadersRow();

        int totalPages = (memoryAddrList.size() + perPage - 1) / perPage;
        int start = currentPage * perPage;
        int end = std::min(start + perPage, (int)memoryAddrList.size());

        for (int i = start; i < end; i++)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);

            bool selected = (selectedIndex == i);
            char label[32];
            snprintf(label, sizeof(label), "0x%llX", memoryAddrList[i]);

            if (ImGui::Selectable(label, selected, ImGuiSelectableFlags_SpanAllColumns))
                selectedIndex = i;

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
                ImGui::OpenPopup("edit_value");

            ImGui::TableSetColumnIndex(1);
            switch (selectedType)
            {
                case 0: ImGui::Text("%d",  sc.getMemoryValue<int32_t>(memoryAddrList[i])); break;
                case 1: ImGui::Text("%lld", sc.getMemoryValue<int64_t>(memoryAddrList[i])); break;
                case 2: ImGui::Text("%f",  sc.getMemoryValue<float>(memoryAddrList[i])); break;
            }
        }

        if (ImGui::BeginPopup("edit_value"))
        {
            ImGui::InputText("New Value", editInput, sizeof(editInput));
            if (ImGui::Button("Write"))
            {
                try {
                    switch (selectedType) {
                        case 0: sc.write<int32_t>(selectedIndex, std::stoi(editInput)); break;
                        case 1: sc.write<int64_t>(selectedIndex, std::stoll(editInput)); break;
                        case 2: sc.write<float>(selectedIndex, std::stof(editInput)); break;
                    }
                } catch (...) {}
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }

        ImGui::EndTable();
    }

}

void Menu::renderToolbar()
{
	const char* types[] = { "int32", "int64", "float", "double", "uint8" };

	ImGui::Combo("Type", &selectedType, types, IM_ARRAYSIZE(types));

}

bool Menu::update()
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();



	ImGui::Begin("pacmem - test");
	renderToolbar();
	ImGui::Separator();
	renderResults();
	ImGui::Separator();
	renderSelected();
	//deletar dps
	ImGui::InputText("Value", searchInput, sizeof(searchInput));
	if (ImGui::Button("Scan") && searchInput[0] != '\0') {
		try {
			std::println("button scan clicked");
			switch (selectedType) {
				case 0: sc.scanUnknown<int32_t>(); break;
				case 1: sc.scanExact<int64_t>(std::stoll(searchInput)); break;
				case 2: sc.scanExact<float>(std::stof(searchInput)); break;
			}
		} catch (...) {
			// invalid input, do nothing
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("ReScan") && searchInput[0] != '\0') {
		try {
			std::println("button scan clicked");
			switch (selectedType) {
				case 0: sc.rescanExact<int32_t>(std::stoi(searchInput)); break;
				case 1: sc.rescanExact<int64_t>(std::stoll(searchInput)); break;
				case 2: sc.rescanExact<float>(std::stof(searchInput)); break;
			}
		} catch (...) {
			// invalid input, do nothing
		}
	}

	ImGui::End();


	ImGui::Render();
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);

	if(glfwWindowShouldClose(window))
	{
		return false;
	}
	return true;
}

Menu::Menu()
{
	if (!glfwInit())
	{
		std::println("error creating glwINIT");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Menu::window = glfwCreateWindow(800, 600, "pacmem", nullptr, nullptr);
	if (!window) { glfwTerminate();}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();
}

Menu::~Menu()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

