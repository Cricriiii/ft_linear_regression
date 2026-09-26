# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fox <fox@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/22 16:59:04 by cgajean           #+#    #+#              #
#    Updated: 2026/09/26 15:21:18 by fox              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
# compiler                                                                     #
# ---------------------------------------------------------------------------- #

# General rules
CXX				:= g++
CXX_STD			:= -std=c++23
CXX_EFLAGS		:= -Werror -Wall -Wextra
CXX_DEBUG		:= -g3
CXX_FLAGS		:= $(CXX_STD) $(CXX_EFLAGS) $(CXX_DEBUG)

# Train program
TRAIN_STD		:= -std=c++23 -O3
PYTHON_CFLAGS	= $(shell python3-config --includes)
PYTHON_LDFLAGS	= $(shell python3-config --embed --ldflags)
NUMPY_CFLAGS	= -I $(shell python3 -c 'import numpy; print(numpy.get_include())')
TRAIN_FLAGS		= $(TRAIN_STD) $(CXX_EFLAGS) $(CXX_DEBUG) \
				   $(PYTHON_CFLAGS) $(NUMPY_CFLAGS) \
				   -Wno-deprecated-declarations
 

# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

# Names of the programs
TRAIN			?= train
PREDICT			?= predict
PRECIS			?= precision

# Used librairies
NUMCPP			:= NumCpp
MATPLOT			:= matplotlib-cpp
NUMCPP_INC		:= ../$(NUMCPP)/include
MATPLOT_INC		:= ../$(MATPLOT)

# Image output directory of the training program
OUTPUT_IMG		:= output

# Program directories
SRC_DIR			:= source
OBJ_DIR			:= .object
INC_DIR			:= include

# Source code of each program
TRAIN_SRC		:= train.cpp \
				   		$(SRC_DIR)/linear_regression.cpp \
				   		$(SRC_DIR)/numcpp_tools.cpp
PREDICT_SRC		:= predict.cpp \
				   		$(SRC_DIR)/numcpp_tools.cpp
PRECIS_SRC		:= precision.cpp \
				   		$(SRC_DIR)/numcpp_tools.cpp

# Object files of each
TRAIN_OBJ		:= $(patsubst %.cpp,$(OBJ_DIR)/$(TRAIN)/%.o,$(TRAIN_SRC))
PREDICT_OBJ		:= $(patsubst %.cpp,$(OBJ_DIR)/$(PREDICT)/%.o,$(PREDICT_SRC))
PRECIS_OBJ		:= $(patsubst %.cpp,$(OBJ_DIR)/$(PRECIS)/%.o,$(PRECIS_SRC))


# ---------------------------------------------------------------------------- #
# build                                                                        #
# ---------------------------------------------------------------------------- #

## Build the whole project
all: $(TRAIN) $(PREDICT) $(PRECIS)
 
$(TRAIN): $(TRAIN_OBJ)
	$(CXX) $(TRAIN_FLAGS) -I $(NUMCPP_INC) -I $(MATPLOT_INC) -I $(INC_DIR) $^ -o $@ $(PYTHON_LDFLAGS)
 
$(PREDICT): $(PREDICT_OBJ)
	$(CXX) $(CXX_FLAGS) -I $(NUMCPP_INC) -I $(INC_DIR) $^ -o $@
 
$(PRECIS): $(PRECIS_OBJ)
	$(CXX) $(CXX_FLAGS) -I $(NUMCPP_INC) -I $(INC_DIR) $^ -o $@

$(OBJ_DIR)/$(TRAIN)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(TRAIN_FLAGS) -I $(NUMCPP_INC) -I $(MATPLOT_INC) -I $(INC_DIR) -c $< -o $@
 
$(OBJ_DIR)/$(PREDICT)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -I $(NUMCPP_INC) -I $(INC_DIR) -c $< -o $@
 
$(OBJ_DIR)/$(PRECIS)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -I $(NUMCPP_INC) -I $(INC_DIR) -c $< -o $@
 
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
	rm -rf $(OUTPUT_IMG)

## Call the 'clean' target and the delete executable file
fclean:
	+$(MAKE) clean
	rm -f $(TRAIN) $(PREDICT) $(PRECIS)


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

.SECONDARY: $(TRAIN_OBJ) $(PREDICT_OBJ) $(PRECIS_OBJ)