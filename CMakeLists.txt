cmake_minimum_required(VERSION 3.5)

# Set the project name
project (SearchMaster)

set(CMAKE_DEBUG_POSTFIX d)

set (CTRL_SOURCES
    src/ui/controls/sl_labeled_value.cpp
    src/ui/controls/sl_simple_value.cpp
    src/ui/controls/sl_value.cpp
    src/ui/controls/sl_angle_value.cpp
    src/ui/controls/sl_lamp_dir_indicator.cpp
    src/ui/controls/sl_lamp_dir_indicators.cpp
    src/ui/controls/sl_lamp_id_indicators.cpp
    src/ui/controls/sl_lamp_status_indicators.cpp
    src/ui/controls/sl_lamp_dist_indicators.cpp
    src/ui/controls/sl_lamp_focus_indicators.cpp
    src/ui/controls/sl_lamp_system_indicators.cpp
    src/ui/controls/sl_lamp_generic_indicators.cpp
    src/ui/controls/sl_display.cpp
)

set (CTRL_HEADERS
    src/ui/controls/sl_labeled_value.h
    src/ui/controls/sl_simlpe_value.h
    src/ui/controls/sl_value.h
    src/ui/controls/sl_angle_value.h
    src/ui/controls/sl_lamp_dir_indicator.h
    src/ui/controls/sl_lamp_dir_indicators.h
    src/ui/controls/sl_lamp_status_indicators.h
    src/ui/controls/sl_lamp_dist_indicators.h
    src/ui/controls/sl_lamp_focus_indicators.h
    src/ui/controls/sl_lamp_system_indicators.h
    src/ui/controls/sl_lamp_generic_indicators.h
    src/ui/controls/sl_display.h
)

set (LBL_SOURCES
    src/ui/labels/sl_red_label.cpp
    src/ui/labels/sl_value_field.cpp
)

set (LBL_HEADERS
    src/ui/labels/sl_red_label.h
    src/ui/labels/sl_value_field.h
)

set(BUT_SOURCES
    src/ui/buttons/sl_ui_button.cpp
    src/ui/buttons/sl_name_edit_button.cpp
    src/ui/buttons/sl_harbour_mode_button.cpp
    src/ui/buttons/sl_settings_button.cpp
    src/ui/buttons/sl_range_ext_button.cpp
    src/ui/buttons/sl_range_red_button.cpp
    src/ui/buttons/sl_scan_ext_button.cpp
    src/ui/buttons/sl_scan_red_button.cpp
    src/ui/buttons/sl_light_on_button.cpp
    src/ui/buttons/sl_light_off_button.cpp
    src/ui/buttons/sl_dimmer_ext_button.cpp
    src/ui/buttons/sl_dimmer_red_button.cpp
)

set(BUT_HEADERS
    src/ui/buttons/sl_ui_button.h
    src/ui/buttons/sl_name_edit_button.h
    src/ui/buttons/sl_harbour_mode_button.h
    src/ui/buttons/sl_settings_button.h
    src/ui/buttons/sl_range_ext_button.h
    src/ui/buttons/sl_range_red_button.h
    src/ui/buttons/sl_scan_ext_button.h
    src/ui/buttons/sl_scan_red_button.h
    src/ui/buttons/sl_light_on_button.h
    src/ui/buttons/sl_light_off_button.h
    src/ui/buttons/sl_dimmer_ext_button.h
    src/ui/buttons/sl_dimmer_red_button.h
)

set(SDK_SOURCES
    src/sdk/sl_button.cpp
    src/sdk/sl_drawable.cpp
    src/sdk/sl_wnd.cpp
    src/sdk/sl_button.cpp
    src/sdk/sl_text.cpp
    src/sdk/sl_event.cpp
    src/sdk/sl_bitmap.cpp
    src/sdk/sl_util.cpp
    src/sdk/sl_img_button.cpp
    src/sdk/sl_img_container.cpp
)

set(SDK_HEADERS
    src/sdk/sl_button.h
    src/sdk/sl_drawable.h
    src/sdk/sl_wnd.h
    src/sdk/sl_button.h
    src/sdk/sl_text.h
    src/sdk/sl_event.h
    src/sdk/sl_bitmap.h
    src/sdk/sl_util.h
    src/sdk/sl_img_button.h
    src/sdk/sl_img_container.h
)

set(NMEA_SOURCES
    src/nmea/sl_nmea_parser.cpp
    src/nmea/sl_sentence_conwayer.cpp
    src/nmea/sl_nmea_sentence.cpp
    src/nmea/sl_gll_sentence.cpp
    src/nmea/sl_ttm_sentence.cpp
)

set(NMEA_HEADERS
    src/nmea/sl_nmea_parser.h
    src/nmea/sl_nmea_sentence.h
    src/nmea/sl_hdt_sentence.h
    src/nmea/sl_gll_sentence.h
    src/nmea/sl_ttm_sentence.h
    src/nmea/sl_sentence_conwayer.h
)

set(IO_SOURCES
    src/io/sl_generic_channel.cpp
    src/io/sl_udp_channel.cpp
    src/io/sl_channel_host.cpp
)

set(IO_HEADERS
    src/io/sl_generic_channel.h
    src/io/sl_udp_channel.cpp
    src/io/sl_channel_host.h
)

set(SOURCES
    src/sl_main.cpp
    src/sl_main_wnd.cpp
    src/sl_range_inc_but.cpp
    src/sl_range_dec_but.cpp
    src/sl_value_storage.cpp
    src/sl_settings_storage.cpp
    src/sl_tools.cpp
    src/sl_constants.cpp
    src/sl_geo.cpp
    src/sl_vessel_shape.cpp
)

set(HEADERS
    src/sl_res.h
    src/sl_main_wnd.h
    src/sl_range_inc_but.h
    src/sl_range_dec_but.h
    src/sl_value_storage.h
    src/sl_settings_storage.h
    src/sl_tools.h
    src/sl_constants.h
    src/sl_vessel_shape.h
    src/sl_geo.h
)

add_executable(SearchMaster
    ${SDK_SOURCES}
    ${SOURCES}
    ${BUT_SOURCES}
    ${LBL_SOURCES}
    ${CTRL_SOURCES}
    ${NMEA_SOURCES}
    ${IO_SOURCES}
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
    ${PROJECT_SOURCE_DIR}/src/ui/buttons
    ${PROJECT_SOURCE_DIR}/src/ui/labels
    ${PROJECT_SOURCE_DIR}/src/ui/controls
    ${PROJECT_SOURCE_DIR}/src/nmea
    ${PROJECT_SOURCE_DIR}/src/io
)

target_link_libraries(SearchMaster
    X11
    Imlib2
    pthread
)

add_compile_options(
    -g -std=c++14 -o bin/sm
)


