all: run clean

.PHONY: all

build:
	@g++ src/main.cpp src/Trie.cpp -o build/spell-checker

.PHONY: build

run: build
	@./build/spell-checker

.PHONY: run

clean:
	@rm build/spell-checker

.PHONY: clean
