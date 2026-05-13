cmake_minimum_required(VERSION 3.20)
project(pacmem CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug build with symbols (important for a systems project)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # <-- critical for your LSP (clangd)

include(cmake/ImGui.cmake)

file(GLOB SOURCES "src/*.cpp")
add_executable(pacmem
	${SOURCES}
)

target_include_directories(pacmem PRIVATE 
    src
    ${glfw_SOURCE_DIR}/include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(pacmem PRIVATE imgui glfw GL)

add_custom_command(TARGET pacmem POST_BUILD
    COMMAND sudo setcap cap_sys_ptrace=eip $<TARGET_FILE:pacmem>
    COMMENT "Setting ptrace capability"
)
# Link capstone if you add disassembly later
# target_link_libraries(pacmem capstone)
