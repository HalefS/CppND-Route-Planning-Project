cmake_minimum_required(VERSION 3.11.3)

# Set the C++ standard we will use
set(CMAKE_CXX_STANDARD 17)

# Add the path of the cmake files to the CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

<<<<<<< HEAD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

#
# Project Output Paths
#
set(MAINFOLDER ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${MAINFOLDER}/build")
set(LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

#
# Locate Project Prerequisites
#
=======
project(OSM_A_star_search)

# Set library output path to /lib
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

# Locate project prerequisites
>>>>>>> b42701f6a2beb50b978d1e2cb73ed22fb9e90a68
find_package(io2d REQUIRED)
find_package(Cairo)
find_package(GraphicsMagick)

<<<<<<< HEAD
# Add project executable
add_executable(OSM_A_star_search src/main.cpp src/model.cpp src/render.cpp src/route_model.cpp src/route_planner.cpp)

target_link_libraries(OSM_A_star_search
    PRIVATE io2d::io2d
    PUBLIC pugixml
)

#
# Add Build Targets
#
=======
# Set IO2D flags
>>>>>>> b42701f6a2beb50b978d1e2cb73ed22fb9e90a68
set(IO2D_WITHOUT_SAMPLES 1)
set(IO2D_WITHOUT_TESTS 1)

# Add the pugixml and GoogleTest library subdirectories
add_subdirectory(thirdparty/pugixml)
add_subdirectory(thirdparty/googletest)

# Add project executable
add_executable(OSM_A_star_search src/main.cpp src/model.cpp src/render.cpp src/route_model.cpp src/route_planner.cpp)

target_link_libraries(OSM_A_star_search
    PRIVATE io2d::io2d
    PUBLIC pugixml
)

# Add the testing executable
add_executable(test test/utest_rp_a_star_search.cpp src/route_planner.cpp src/model.cpp src/route_model.cpp)

target_link_libraries(test 
    gtest_main 
    pugixml
)

# Set options for Linux or Microsoft Visual C++
if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    target_link_libraries(OSM_A_star_search PUBLIC pthread)
endif()

if(MSVC)
	target_compile_options(OSM_A_star_search PUBLIC /D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING /wd4459)
endif()
