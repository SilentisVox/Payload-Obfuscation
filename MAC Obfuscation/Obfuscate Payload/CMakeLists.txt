project(Obfuscate_Payload)

file(GLOB_RECURSE SRC "*.c")
file(GLOB_RECURSE HDR "*.h")
add_executable(Obfuscate_Payload ${SRC} ${HDR})

target_include_directories(Obfuscate_Payload PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})