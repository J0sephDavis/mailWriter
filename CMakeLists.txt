#cmake ./CMakeLists.txt _B ./build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake_minimum_required (VERSION 3.11)
 
# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(poco
	GIT_REPOSITORY https://github.com/pocoproject/poco
	GIT_TAG 1211613642269b7d53bea58b02de7fcd25ece3b9 
	GIT_PROGRESS TRUE
	GIT_SHALLOW FALSE 
)

FetchContent_GetProperties(poco)
if(NOT poco_POPULATED)
	FetchContent_Populate(poco)
	add_subdirectory(
		${poco_SOURCE_DIR}
		${poco_BINARY_DIR}
		EXCLUDE_FROM_ALL
	)
endif()
 
# --- Build --------------------------------------------------------------------

project(mailWriter
  LANGUAGES CXX
  VERSION 1.0.0
)
add_executable(mailWriter 
	src/main.cc
	src/mail.h
)

target_include_directories(mailWriter PRIVATE src)
target_link_libraries(mailWriter
	PRIVATE Poco::Net
)
set_target_properties(mailWriter PROPERTIES CXX_STANDARD 20)
