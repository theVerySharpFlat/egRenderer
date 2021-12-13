add_executable(egrTest)

target_sources(egrTest PUBLIC src/main.cpp)

target_link_libraries(egrTest PUBLIC egr)