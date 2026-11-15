.PHONY: setup build test run format
setup:
	cmake --preset debug
	cmake --build --preset debug
build:
	cmake --build --preset debug
test:
	ctest --preset debug
