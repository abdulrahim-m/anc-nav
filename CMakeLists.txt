cmake_minimum_required(VERSION 3.28.0)
project(A.N.C.S. VERSION 0.1.0 LANGUAGES C CXX)

# add_subdirectory(thirdParty/test)

include(CTest)
enable_testing()

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if(PRODUCTION_BUILD)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization
else()
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
endif()

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
# target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCES_PATH="./resources/")

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_link_libraries(A.N.S.C. PRIVATE test) 