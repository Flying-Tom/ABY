
# add_executable(secureFL float_utils.h  loss.cpp)
add_library(secureLR SHARED  loss.cpp)
target_link_libraries(secureLR ABY::aby ENCRYPTO_utils::encrypto_utils)
