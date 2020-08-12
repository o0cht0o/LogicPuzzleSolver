project(lpslib)

file(GLOB SRC
	"base/*.h"
	"base/*.cpp"
	"solver/*.h"
	"solver/*.cpp"
)

add_library(lpslib SHARED
	${SRC}
)
