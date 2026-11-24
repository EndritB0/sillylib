add_executable(sillylibTests)

set(sillylibTests_SOURCES
    "src/pch.h"
    "src/SmokeTest.cpp"
)

set(BASE_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set_target_properties(sillylibTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BASE_OUTPUT_DIR}
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${sillylibTests_SOURCES})
source_group("Precompiled Headers" REGULAR_EXPRESSION ".*pch.*")

target_sources(sillylibTests PRIVATE ${sillylibTests_SOURCES})

target_compile_features(sillylibTests PRIVATE cxx_std_20)
target_include_directories(sillylibTests PRIVATE src)
target_precompile_headers(sillylibTests PRIVATE src/pch.h)

target_link_libraries(sillylibTests PRIVATE sillylib GTest::gtest_main SillylibProjectWarnings)

include(GoogleTest)
gtest_discover_tests(sillylibTests DISCOVERY_MODE PRE_TEST)
