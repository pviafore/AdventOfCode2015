
CURDIR = $(shell pwd)
DOCKER=docker run -it -v $(CURDIR):/root/modern:rw advent-of-code-2015 
CHALLENGE?=1
CPPFILES = challenges/*.cpp common/*.cpp
run: static-analysis
		./test

static-analysis: build
		$(DOCKER) cppcheck --std=c++11 $(CPPFILES) --enable=all -q -Icommon --error-exitcode=1 --suppress="unusedFunction" && \
		$(DOCKER) clang-tidy $(CPPFILES) --checks="*,-fuchsia-*, -readability-magic-numbers, -cppcoreguidelines-avoid-magic-numbers, -misc-non-private-member-variables-in-classes,-modernize-pass-by-value, -bugprone-exception-escape" --warnings-as-errors="*" -- -Icommon -std=c++2a 

build:
		$(DOCKER) g++ -g challenges/challenge$(CHALLENGE).cpp common/*.cpp -Icommon -std=c++2a -o test -Werror -Wall -Wextra -pedantic

docker:
		docker build -t advent-of-code-2015 . 

debug:
		$(DOCKER) gdb ./test

shell:
		$(DOCKER) /bin/bash
