cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("pargse")

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
 set(warnings "-Wall -Wextra -Werror")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  set(warnings "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
  set(CMAKE_C_FLAGS "${warnings} -Wmissing-prototypes"
    CACHE STRING "Flags used by the compiler during all build types." FORCE)
  set(CMAKE_CXX_FLAGS "${warnings}"
    CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


include_directories(inc/)

set(SRCS_DIR srcs)
set(SRCS)
add_subdirectory(${SRCS_DIR})
foreach(file ${SRCS_FILES})
  set(SRCS ${SRCS} ${SRCS_DIR}/${file})
endforeach()

add_library(pargse SHARED ${SRCS})

set(SAMPLES_DIR samples)
add_subdirectory(${SAMPLES_DIR})

install (DIRECTORY inc/ DESTINATION include)
install (TARGETS pargse DESTINATION lib)
