#cmake ./CMakeLists.txt _B ./build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake_minimum_required (VERSION 3.14.4)
 
# --- Build --------------------------------------------------------------------

project(mailWriter
  LANGUAGES CXX
  VERSION 1.0.0
)
add_executable(mailWriter 
	src/main.cc
	src/mail.h
	src/mail.cc
)

find_package( CURL REQUIRED )
target_include_directories(mailWriter
	PRIVATE src
)
target_link_libraries(mailWriter
	curl
)
set_target_properties(mailWriter PROPERTIES CXX_STANDARD 20)
