cmake_minimum_required(VERSION 3.4)
project(knowledge_engineering)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag(--std=c++11 SUPPORTS_STD_CXX11)
    if(SUPPORTS_STD_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c++11")
    else()
        message(ERROR "Compiler does not support --std=c++11")
    endif()
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    SET (CMAKE_AR      "/usr/bin/llvm-ar")
    SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
    SET (CMAKE_NM      "/usr/bin/llvm-nm")
    SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
    SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
endif()

# Find includes in corrisponing build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Sql)
find_package(Qt5Gui)
find_package(Qt5Qml)
find_package(Qt5Quick)
find_package(Qt5Widgets)
# Add the include directories for the Qt5 modules to
# the compile lines
INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS} ${Qt5Sql_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Concurrent_INCLUDE_DIRS} ${QUAZIP_INCLUDE_DIRS} src/data src/utils src/workers src/gui)

# Use the compile definitions defined in the Qt5 modules
add_definitions(${Qt5Core_DEFINITIONS} ${Qt5Sql_DEFINITIONS} ${Qt5Gui_DEFINITIONS} ${Qt5Qml_DEFINITIONS} ${Qt5Quick_DEFINITIONS} ${Qt5Widgets_DEFINITIONS} ${Qt5Concurrent_DEFINITIONS})

# Add compiler flags for bulding executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS} ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS} ${Qt5Qml_EXECUTABLE_COMPILE_FLAGS} ${Qt5Quick_EXECUTABLE_COMPILE_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${Qt5Concurrent_EXECUTABLE_COMPILE_FLAGS} ")

set(knowledge_engineering_SRCS src/main.cpp)
set(knowledge_engineering_QRC src/files.qrc)
add_subdirectory(src/data)
add_subdirectory(src/controller)

QT5_ADD_RESOURCES(knowledge_engineering_RCC_SRCS ${knowledge_engineering_QRC})

#foreach(knowledge_engineering_QT_HEADER ${knowledge_engineering_QT_HEADERS})
#    GET_FILENAME_COMPONENT(knowledge_engineering_MOC ${knowledge_engineering_QT_HEADER} NAME_WE)
#    GET_FILENAME_COMPONENT(knowledge_engineering_DIR ${knowledge_engineering_QT_HEADER} DIRECTORY)
#    set(knowledge_engineering_MOC "${knowledge_engineering_DIR}/${knowledge_engineering_MOC}.moc")
#    #message(${knowledge_engineering_SRC} " - " ${knowledge_engineering_MOC} " ;")
#    qt5_generate_moc(${knowledge_engineering_QT_HEADER} ${knowledge_engineering_MOC})
#    set(knowledge_engineering_MOCS ${knowledge_engineering_MOCS} ${knowledge_engineering_MOC})
#endforeach()

add_executable(knowledge_engineering ${knowledge_engineering_SRCS} ${knowledge_engineering_MOCS} ${knowledge_engineering_RCC_SRCS})
target_link_libraries(knowledge_engineering ${Qt5Sql_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Qml_LIBRARIES} ${Qt5Quick_LIBRARIES} ${Qt5Widgets_LIBRARIES})

install(TARGETS knowledge_engineering RUNTIME DESTINATION bin)
