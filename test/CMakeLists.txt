set(target polinoms_test)

#file(GLOB hdrs "*.h*" "../include/*.h" "../gtest/*.h")
file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../src/*.cpp")

add_executable(${target} ${srcs} ${hdrs}  "test_table.cpp" "test_ordered_table.cpp" "test_hash_table.cpp" "test_monomial.cpp")
target_link_libraries(${target} gtest)
