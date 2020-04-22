cmake_minimum_required(VERSION "3.7.1")

project("MyDB")

include_directories("include")
add_executable("${PROJECT_NAME}" "main.cpp")

install(TARGETS "${PROJECT_NAME}" DESTINATION "bin")
#install(FILES "main.cpp" DESTINATION src)