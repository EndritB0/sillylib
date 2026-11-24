add_library(sillylib STATIC)

set(sillylib_SOURCES
    "src/sillylib/pch.h"
    "include/sillylib/sillylib.h"
    "include/sillylib/assert.h"
    "src/sillylib/assert.cpp"
)

set(BASE_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set_target_properties(sillylib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${BASE_OUTPUT_DIR}
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${sillylib_SOURCES})
source_group("Precompiled Headers" REGULAR_EXPRESSION ".*pch.*")

target_sources(sillylib PRIVATE ${sillylib_SOURCES})

target_compile_features(sillylib PUBLIC cxx_std_20)
target_include_directories(sillylib PUBLIC include PRIVATE src)
target_precompile_headers(sillylib PRIVATE src/sillylib/pch.h)

target_link_libraries(sillylib PRIVATE SillylibProjectWarnings)
