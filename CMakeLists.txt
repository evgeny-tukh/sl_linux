cmake_minimum_required(VERSION 3.5)

# Set the project name
project (SearchMaster)

set(CMAKE_DEBUG_POSTFIX d)

set(BUT_SOURCES
    src/buttons/sl_name_edit_button.cpp
)

set(BUT_HEADERS
    src/buttons/sl_name_edit_button.h
)

set(SDK_SOURCES
    src/sdk/sl_button.cpp
    src/sdk/sl_wnd.cpp
    src/sdk/sl_button.cpp
    src/sdk/sl_event.cpp
    src/sdk/sl_bitmap.cpp
    src/sdk/sl_util.cpp
    src/sdk/sl_img_button.cpp
)

set(SDK_HEADERS
    src/sdk/sl_button.h
    src/sdk/sl_wnd.h
    src/sdk/sl_button.h
    src/sdk/sl_event.h
    src/sdk/sl_bitmap.h
    src/sdk/sl_util.h
    src/sdk/sl_img_button.h
)

set(SOURCES
    src/sl_main.cpp
    src/sl_main_wnd.cpp
    src/sl_range_inc_but.cpp
    src/sl_range_dec_but.cpp
)

set(HEADERS
    src/sl_res.h
    src/sl_main_wnd.h
    src/sl_range_inc_but.h
    src/sl_range_dec_but.h
)

add_executable(SearchMaster
    ${SDK_SOURCES}
    ${SOURCES}
    ${BUT_SOURCES}
)

set_target_properties(SearchMaster
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/sdk
    ${PROJECT_SOURCE_DIR}/src/buttons
)

target_link_libraries(SearchMaster
    X11
    Imlib2
)

add_compile_options(
    -g -std=c++14 -o bin/sm
)


