add_subdirectory(sillylib)
add_subdirectory(tests)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sillylibTests)