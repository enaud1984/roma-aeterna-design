add_library(RomaAeternaCore INTERFACE)
target_include_directories(RomaAeternaCore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(RomaAeternaCore INTERFACE cxx_std_17)

add_executable(RomaAeternaCoreTests tests/RARomanModularCoreTests.cpp)
target_link_libraries(RomaAeternaCoreTests PRIVATE RomaAeternaCore)

if(MSVC)
    target_compile_options(RomaAeternaCoreTests PRIVATE /W4 /permissive-)
else()
    target_compile_options(RomaAeternaCoreTests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(ROMA_AETERNA_ENABLE_SANITIZERS AND NOT MSVC)
    target_compile_options(RomaAeternaCoreTests PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(RomaAeternaCoreTests PRIVATE -fsanitize=address,undefined)
endif()

enable_testing()
add_test(NAME RomaAeternaCoreTests COMMAND RomaAeternaCoreTests)
