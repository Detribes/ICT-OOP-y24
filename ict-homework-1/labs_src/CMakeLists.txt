add_library(labs)

target_sources(labs
  PRIVATE
        lab1/Point.cpp
        lab1/Poly.cpp
        lab1/ClosedPoly.cpp
        lab1/Polygon.cpp
        lab1/RegularPolygon.cpp
        lab1/Trapezoid.cpp
        lab1/Triangle.cpp
  PUBLIC
        lab1/Point.h
        lab1/Poly.h
        lab1/ClosedPoly.h
        lab1/Polygon.h
        lab1/RegularPolygon.h
        lab1/Trapezoid.h
        lab1/Triangle.h
  )

target_include_directories(labs
  PUBLIC
        .
  )

# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(labs
    PUBLIC
      "--coverage"
    )
  target_link_options(labs
    INTERFACE
      "--coverage"
    )
endif()
