cmake_minimum_required(VERSION 3.20)
project(AP_Proj)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:\\MyWorld\\Coder\\.App\\Qt\\6.4.1\\msvc2019_64\\lib\\cmake\\")


find_package(Qt6Widgets REQUIRED)
find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/area)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/entity)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/entity/element)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/entity/buff)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/entity/action)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/entity/monster)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/entity/character)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/particle)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/game_view)

# Need to add this line to handle Q_OBJECT macro
file(GLOB PARTICLE_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/particle/*.h")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} MAIN_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source COMPONENTS_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/area AREA_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/entity ENTITY_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/entity/buff BUFF_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/entity/element ELEMENT_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/entity/action ACTION_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/entity/monster MONSTER_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/entity/character CHARACTER_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/particle PARTICLE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/game_view VIEW_SRC)

file(GLOB QRC_FILE "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.qrc")

add_executable(${PROJECT_NAME}
        ${MAIN_SRC} ${COMPONENTS_SRC}
        ${AREA_SRC} ${ENTITY_SRC} ${BUFF_SRC} ${ELEMENT_SRC}
        ${ACTION_SRC} ${MONSTER_SRC} ${CHARACTER_SRC}
        ${PARTICLE_SRC} ${VIEW_SRC}
        ${PARTICLE_HEADER}
        ${QRC_FILE}
        )

target_link_libraries(
        ${PROJECT_NAME}
        Qt6::Widgets
        Qt6::Core
        Qt6::Gui
)
