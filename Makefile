.PHONY: format
format:
	clang-format src/* -i

.PHONY: build
build: clean
	mkdir -p build
	cd build && \
	cmake -DCOPY_YOLO=ON .. && \
	make

.PHONY: build
build-no-copy: clean
	mkdir -p build
	cd build && \
	cmake -DCOPY_YOLO=OFF .. && \
	make

.PHONY: debug
debug: clean
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug -DCOPY_YOLO=ON .. && \
	make

.PHONY: valgrind
valgrind: debug
	cd build && \
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--log-file=../valgrind-out.txt \
	./capstone

.PHONY: clean
clean:
	rm -rf build
