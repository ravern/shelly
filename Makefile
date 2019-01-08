all: run clean

.PHONY: all

build:
	@g++ main.cpp -o build/spell-checker

.PHONY: build

run: build
	@./build/spell-checker

.PHONY: run

clean:
	@rm build/spell-checker

.PHONY: clean