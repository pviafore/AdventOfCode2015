
CURDIR = $(shell pwd)
DOCKER=docker run -it -v $(CURDIR):/root/modern:rw advent-of-code-2017 
CHALLENGE?=1
CPPFILES = challenges/challenge$(CHALLENGE).cpp
run: static-analysis
		./test

static-analysis: build
		$(DOCKER) cppcheck --std=c++11 $(CPPFILES) --enable=all -q -Icommon --error-exitcode=1 && \
		$(DOCKER) clang-tidy $(CPPFILES) --checks="*" --warnings-as-errors="*" -- -Icommon -std=c++1z

build:
		$(DOCKER) g++ -g $(CPPFILES) -Icommon -std=c++17 -o test -Werror -Wall -Wextra -pedantic

docker:
		docker build -t advent-of-code-2017 . 

shell:
		$(DOCKER) /bin/bash
