# CMakeList.txt : CMake project for graphics_test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("graphics_test")

# Add source to this project's executable.
add_executable (graphics_test "graphics_test.cpp" "graphics_test.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET graphics_test PROPERTY CXX_STANDARD 11)
endif()

# Load OpenGL
#find_package(OpenGL REQUIRED)
#target_link_libraries(graphics_test OpenGL::GL)

# GLFW3
include_directories("${CMAKE_SOURCE_DIR}/lib/glfw-3.4.bin.WIN64/include")
find_library(GLFW3_LIBRARY glfw3 "${CMAKE_SOURCE_DIR}/lib/glfw-3.4.bin.WIN64/lib-vc2022")
target_link_libraries(graphics_test ${GLFW3_LIBRARY})

# GLAD
include_directories("${CMAKE_SOURCE_DIR}/lib/glad/include")
find_library(GLAD_LIBRARY glad "${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c")
target_link_libraries(graphics_test ${GLAD_LIBRARY}:glad)



# TODO: Add tests and install targets if needed.
