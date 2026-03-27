cmake_minimum_required(VERSION 3.10)
project(MeshViewer)

set(CMAKE_CXX_STANDARD 17)

set(OpenGL_GL_PREFERENCE LEGACY)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH /opt/homebrew /usr/local)
endif()

find_package(glm REQUIRED)

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OpenGL_LIBRARY_DIRS})
    add_definitions(${OpenGL_DEFINITIONS})
else()
    message(ERROR " OPENGL not found!")
endif()

find_package(GLUT REQUIRED)
if(GLUT_FOUND)
    include_directories(${GLUT_INCLUDE_DIRS})
else()
    message(ERROR " GLUT not found!")
endif()

FIND_PACKAGE(GLEW REQUIRED)
if(GLEW_FOUND)
    include_directories( ${GLEW_INCLUDE_PATH})
else()
    MESSAGE("GLEW not found!")
endif()

set(SOURCE_FILES
        main.cpp
        myHalfedge.cpp
        myVector3D.cpp
        myPoint3D.cpp
        myFace.cpp
        myMesh.cpp
        myVertex.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE SHADERS_DIR="${CMAKE_SOURCE_DIR}/shaders")
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} GLEW::GLEW ${GLUT_LIBRARIES} glm::glm)

# Set working directory to project root so relative paths (e.g. cube.obj) work
set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Copy shaders to build directory after each build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)

