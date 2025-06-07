project(DeObfuscate_Payload)

file(GLOB_RECURSE SRC "*.c")
file(GLOB_RECURSE HDR "*.h")
add_executable(DeObfuscate_Payload ${SRC} ${HDR})

target_include_directories(DeObfuscate_Payload PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})