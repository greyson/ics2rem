project( ics2rem CXX )
cmake_minimum_required( VERSION 2.6 )

find_package( Boost 1.47 REQUIRED
  COMPONENTS filesystem system )

include_directories(
  ${Boost_INCLUDE_DIRS}
)
link_directories(
  ${Boost_LIBRARY_DIRS}
)

add_subdirectory( src )

add_executable( ics2rem main.cpp )
target_link_libraries( ics2rem ics2rem_lib )