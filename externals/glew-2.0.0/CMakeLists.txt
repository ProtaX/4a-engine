cmake_minimum_required(VERSION 3.0)

set (GLEW_COMPILE_CMD "compile.64.bat")
execute_process(COMMAND ${GLEW_COMPILE_CMD}
                WORKING_DIRECTORY ${EXTERNALS_DIR}/glew-2.0.0)
set (GLEW_MOVE_DLL_CMD "cp")
set (GLEW_MOVE_DLL_1_ARG "glew32.dll")
set (GLEW_MOVE_DLL_2_ARG "../../../build/")
execute_process(COMMAND ${GLEW_MOVE_DLL_CMD} ${GLEW_MOVE_DLL_1_ARG} ${GLEW_MOVE_DLL_2_ARG}
                WORKING_DIRECTORY ${EXTERNALS_DIR}/glew-2.0.0/lib)