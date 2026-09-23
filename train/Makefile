# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/22 16:59:04 by cgajean           #+#    #+#              #
#    Updated: 2026/09/23 15:29:22 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
# compiler                                                                     #
# ---------------------------------------------------------------------------- #

CXX				:= g++
CXX_STD			:= -std=c++23
CXX_EFLAGS		:= -Werror -Wall -Wextra 
CXX_DEBUG		:= -g3
CXX_FLAGS		:= $(CXX_STD) $(CXX_EFLAGS) $(CXX_DEBUG)


# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

PROGRAM			:= $(notdir $(abspath $(dir $(lastword $(MAKEFILE_LIST)))))

ROOT_INC		:= ../include
NUMCPP_INC		:= ../numcpp/include

SRC_DIR			:= source
OBJ_DIR			:= .object
INC_DIR			:= include

FILES_CPP		:= $(shell find . -type f -wholename "*.cpp")
FILES_O			:= $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(FILES_CPP))


# ---------------------------------------------------------------------------- #
# build                                                                        #
# ---------------------------------------------------------------------------- #

## Build the whole project
all: $(PROGRAM)

$(PROGRAM): $(FILES_O)
	$(CXX) $(CXX_FLAGS) -I $(ROOT_INC) -I $(NUMCPP_INC) -I $(INC_DIR) $^ -o $(PROGRAM)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -I $(ROOT_INC) -I $(NUMCPP_INC) -I $(INC_DIR) -c $< -o $@

## Call 'fclean' then 'all' targets
re:
	+$(MAKE) fclean
	+$(MAKE) all


# ---------------------------------------------------------------------------- #
# clean                                                                        #
# ---------------------------------------------------------------------------- #

## Clean the .object folder
clean:
	rm -rf $(shell find . -type d -wholename *.object)

## Call the 'clean' target and the delete executable file
fclean:
	+$(MAKE) clean
	rm -f $(PROGRAM)


# ---------------------------------------------------------------------------- #
# misc                                                                         #
# ---------------------------------------------------------------------------- #

## Format files
format:
	@find . -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i

# Provided by https://gitlab.com/depressiveRobot/make-help/blob/master/help.mk
## Show this help
help:
	@printf "\nAvailable targets:\n"
	@awk '/^[a-zA-Z\-_0-9]+:/ { \
		helpMessage = match(lastLine, /^## (.*)/); \
		if (helpMessage) { \
			helpCommand = substr($$1, 0, index($$1, ":")-1); \
			helpMessage = substr(lastLine, RSTART + 3, RLENGTH); \
			printf "  %-20s %s\n", helpCommand, helpMessage; \
		} \
	} \
	{ lastLine = $$0 }' $(MAKEFILE_LIST)
	@echo


.PHONY: all re test test_docker clean fclean format help