project(MultiProcessDemo)
#message("CMAKE_MODULE_PATH:"${CMAKE_MODULE_PATH})
message("CMAKE_MODULE_PATH=${CMAKE_CURRENT_SOURCE_DIR}")
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    message(STATUS "C++17 supported!")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()

add_subdirectory("CppXBase")


include_directories(${BASE_INCLUDE_DIRS})

macro(DEMO_ADD_EXE exe_name src)
    LINK_DIRECTORIES(${BASE_LIB_DIRS})
    add_executable(${exe_name} ${src})
    target_link_libraries(${exe_name} ${BASE_LIBS})
endmacro(DEMO_ADD_EXE)


DEMO_ADD_EXE(main main.cpp)
DEMO_ADD_EXE(daemon daemon.cpp)
#add_executable(MultiProcessDemo MultiProcessDemo.cpp)
#LINK_DIRECTORIES(${BASE_LIB_DIRS})
#target_link_libraries(MultiProcessDemo ${BASE_LIBS})
