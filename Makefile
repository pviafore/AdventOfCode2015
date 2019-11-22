
CURDIR = $(shell pwd)
DOCKER=docker run -it -v $(CURDIR):/root/modern:rw advent-of-code-2015 
CHALLENGE?=1
CPPFILES = challenges/*.cpp common/*.cpp
run: static-analysis
		./test

static-analysis: build
		$(DOCKER) cppcheck --std=c++11 $(CPPFILES) --enable=all -q -Icommon --error-exitcode=1 --suppress="unusedFunction" && \
		$(DOCKER) clang-tidy $(CPPFILES) --checks="*,-fuchsia-default-arguments, -fuchsia-overloaded-operator" --warnings-as-errors="*" -- -Icommon -std=c++1z

build:
		$(DOCKER) g++ -g challenges/challenge$(CHALLENGE).cpp common/*.cpp -Icommon -std=c++2a -o test -Werror -Wall -Wextra -pedantic

docker:
		docker build -t advent-of-code-2015 . 

debug:
		$(DOCKER) gdb ./test

shell:
		$(DOCKER) /bin/bash
