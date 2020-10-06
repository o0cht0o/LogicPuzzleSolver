project(lpsui)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

file(GLOB SRC
	"*.h"
	"*.cpp"
)

add_subdirectory(${CMAKE_SOURCE_DIR}/lpslib lpslib)


add_library(lpsui SHARED
	${SRC}
)

target_link_libraries(lpsui lpslib)

target_link_libraries(lpsui Qt5::Widgets)
