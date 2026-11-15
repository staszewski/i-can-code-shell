.PHONY: setup build test run format
setup:
	cmake --preset debug
	cmake --build --preset debug
build:
	cmake --build --preset debug
test:
	ctest --preset debug
run: build
	./build/debug/shell-in-cpp
format:
	xcrun clang-format -i src/*.cpp
