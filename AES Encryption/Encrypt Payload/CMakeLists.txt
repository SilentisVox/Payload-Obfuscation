project(Encrypt_Payload)

file(GLOB_RECURSE SRC "*.c")
file(GLOB_RECURSE HDR "*.h")
add_executable(Encrypt_Payload ${SRC} ${HDR})

target_include_directories(Encrypt_Payload PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})