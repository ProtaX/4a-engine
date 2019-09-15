cmake_minimum_required(VERSION 3.0)

#GLFW - to make a window
add_subdirectory(${EXTERNALS_DIR}/glfw-3.3)

#compile GLEW
set (GLEW_COMPILE_CMD "compile.64.bat")
execute_process(COMMAND ${GLEW_COMPILE_CMD}
                WORKING_DIRECTORY ${EXTERNALS_DIR}/glew-2.0.0)