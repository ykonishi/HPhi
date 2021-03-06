# include guard
cmake_minimum_required(VERSION 2.8)
if(${CMAKE_PROJECT_NAME} STREQUAL "Project")
  message(FATAL_ERROR "cmake should be executed not for 'src' subdirectory, but for the top directory of HPhi.")
endif(${CMAKE_PROJECT_NAME} STREQUAL "Project")

add_definitions(-D__NO_ZDOT)
set(SOURCES_KOMEGA komega_bicg.F90 komega_math.F90 komega_vals.F90)
if(MPI_Fortran_FOUND)
  add_definitions(${MPI_Fortran_COMPILE_FLAGS})
  link_directories(${MPI_Fortran_LIBRARY_DIRS})
  include_directories(${MPI_Fortran_INCLUDE_PATH})
endif(MPI_Fortran_FOUND)
add_library(komega ${SOURCES_KOMEGA})
target_link_libraries(komega ${LAPACK_LIBRARIES} m)
if(MPI_Fortran_FOUND)
  target_link_libraries(komega ${MPI_Fortran_LIBRARIES})
endif(MPI_Fortran_FOUND)
install(TARGETS komega ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
