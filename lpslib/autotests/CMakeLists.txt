project(testAll)

if(NOT LPSLIB_DIR)
	set( LPSLIB_DIR ${CMAKE_SOURCE_DIR}/..)
endif()
if(IS_DIRECTORY ${LPSLIB_DIR})
	add_subdirectory( ${LPSLIB_DIR} lpslib)
else()
	message(FATAL_ERROR   "INVALID FOLDER 'LPSLIB_DIR'=${LPSLIB_DIR}")
endif()

file(GLOB tests
	RELATIVE "${CMAKE_SOURCE_DIR}/"
	"${CMAKE_SOURCE_DIR}/test*.cpp"
)

foreach(testfile IN LISTS tests)
	get_filename_component(testname ${testfile} NAME_WE)
	add_executable(${testname} ${testfile})
	target_link_libraries(${testname}
		PRIVATE
		lpslib
	)
endforeach(testfile)
