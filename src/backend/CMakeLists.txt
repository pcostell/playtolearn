
FILE(GLOB_RECURSE SRCS "**.cpp")

add_library(playtolearnlibrary_backend ${SRCS})
target_link_libraries(playtolearnlibrary_backend
                      boost_python ${PYTHON_LIBRARIES} boost_serialization)
