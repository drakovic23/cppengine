cmake_minimum_required(VERSION 3.14)  # or higher
project(BacktestEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(BacktestEngine
	src/main.cpp
	src/BarData.cpp
	src/SqliteHelper.cpp
	src/OhlcMapper.cpp
	src/ReturnsCalculator.cpp
	src/StatAccumulator.cpp
)

target_include_directories(BacktestEngine
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(BacktestEngine PRIVATE sqlite3)
