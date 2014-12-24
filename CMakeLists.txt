#  Copyright (c) 2014 Cory Perry
#  This file is part of SortPlugin.
#
#  SortPlugin is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  SortPlugin is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with SortPlugin.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.8.7)

project(sortPlugin)

include(GenerateExportHeader)
add_compiler_export_flags(COMPILE_VISIBILITY_FLAGS)
include_directories(${PROJECT_BINARY_DIR})
find_package(Boost COMPONENTS program_options filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(sortTest_SRCS main.cpp)

add_executable(sortTest ${sortTest_SRCS})
target_link_libraries(sortTest ${CMAKE_DL_LIBS} ${Boost_LIBRARIES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(plugins)
