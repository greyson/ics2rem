add_library( ics2rem_lib STATIC
  Ics.cpp
)
target_link_libraries( ics2rem_lib ${Boost_LIBRARIES} ical )