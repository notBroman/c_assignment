
cmake_minimum_required(VERSION 3.4)

project(c_assignment LANGUAGES C)


add_executable(a.out
    src/main.c
)

target_compile_features(a.out PUBLIC c_std_99)

function(print)
    foreach(var ${ARGN})
        message("${var} = ${${var}}")
    endforeach()
endfunction()

print(PROJECT_NAME)
