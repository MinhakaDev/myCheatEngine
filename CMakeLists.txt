cmake_minimum_required(VERSION 3.20)
project(pacmem CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug build with symbols (important for a systems project)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # <-- critical for your LSP (clangd)

file(GLOB SOURCES "src/*.cpp")
add_executable(pacmem
	${SOURCES}
)

target_include_directories(pacmem PRIVATE src)

# Link capstone if you add disassembly later
# target_link_libraries(pacmem capstone)
