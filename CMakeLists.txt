cmake_minimum_required(VERSION 3.17)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}:/home/dphan/learning/muonTomo/TinyTIFF/install/lib/cmake/TinyTIFF")

project(name)

find_package(ROOT REQUIRED Core)
find_package(TinyTIFF REQUIRED)
# find_package(BLAS)
# find_package(Armadillo REQUIRED)
# find_package(Geant4 REQUIRED ui_all vis_all)

include(${ROOT_USE_FILE})
# include(${Geant4_USE_FILE})
# include_directories(${ARMADILLO_INCLUDE_DIRS})
# include_directories(${BLAS_INCLUDE_DIRS})

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB INC ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(target main.cpp ${SRC} ${INC})
target_link_libraries(target ${ROOT_LIBRARIES})
target_link_libraries(target TinyTIFF)
# target_link_libraries(target ${Geant4_LIBRARIES})
# target_link_libraries(target ${BLAS_LIBRARIES})
# target_link_libraries(target ${AMADILLO_LIBRARIES})
