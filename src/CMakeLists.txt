
ADD_SUBDIRECTORY(backend)
ADD_SUBDIRECTORY(frontend)
ADD_SUBDIRECTORY(ui)
ADD_SUBDIRECTORY(util)

add_library(playtolearnlibrary)
target_link_libraries(playtolearnlibrary
                      playtolearnlibrary_backend
                      playtolearnlibrary_frontend
                      playtolearnlibrary_ui
                      playtolearnlibrary_util)
ADD_DEPENDENCIES(playtolearnlibrary
                      playtolearnlibrary_backend
                      playtolearnlibrary_frontend
                      playtolearnlibrary_ui
                      playtolearnlibrary_util)