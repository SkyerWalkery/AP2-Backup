cmake_minimum_required(VERSION 3.20)
project(AP_Proj)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "D:\\Tools\\Qt\\6.3.1\\msvc2019_64\\lib\\cmake")

find_package(Qt6Widgets REQUIRED)
find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/area)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/monster)

aux_source_directory(. MAIN_SRC)
aux_source_directory(./source COMPONENTS_SRC)
aux_source_directory(./source/area AREA_SRC)
aux_source_directory(./source/monster MONSTER_SRC)

add_executable(${PROJECT_NAME}
        ${MAIN_SRC} ${COMPONENTS_SRC}
        ${AREA_SRC} ${MONSTER_SRC}
        img_rsc.qrc
        )

target_link_libraries(
        ${PROJECT_NAME}
        Qt6::Widgets
        Qt6::Core
        Qt6::Gui
)

