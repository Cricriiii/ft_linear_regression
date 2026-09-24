# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/22 18:34:12 by cgajean           #+#    #+#              #
#    Updated: 2026/09/24 14:02:54 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

PREDICT		:= predict
TRAIN		:= train
PRECIS		:= precision
NUMCPP		:= NumCpp
LIBCPP		:= LibCpp


# ---------------------------------------------------------------------------- #
# build                                                                        #
# ---------------------------------------------------------------------------- #

## Build whole project
all:
	+$(MAKE) $(NUMCPP)
	+$(MAKE) -C $(PREDICT) -j $(nproc) all
	+$(MAKE) -C $(TRAIN) -j $(nproc) all
	+$(MAKE) -C $(PRECIS) -j $(nproc) all

## Build whole project in a Docker environment
docker:
	+$(MAKE) fclean
	docker build -t linear:1.0 .

## Call 'fclean' then 'all' targets
re:
	+$(MAKE) fclean
	+$(MAKE) all

## Call 'reset' then 'all' targets
rere:
	+$(MAKE) reset
	+$(MAKE) all	

## Import numcpp
$(NUMCPP):
ifeq ($(wildcard $(NUMCPP)),)
	git clone https://github.com/dpilger26/NumCpp.git $(NUMCPP);
else
	@echo "$(NUMCPP) is already installed"
endif


# ---------------------------------------------------------------------------- #
# clean                                                                        #
# ---------------------------------------------------------------------------- #

## Clean .object folders
clean:
	+$(MAKE) -C $(PREDICT) clean
	+$(MAKE) -C $(TRAIN) clean
	+$(MAKE) -C $(PRECIS) clean

## Call 'clean' target and delete executable files
fclean:
	+$(MAKE) -C $(PREDICT) fclean
	+$(MAKE) -C $(TRAIN) fclean
	+$(MAKE) -C $(PRECIS) fclean

## Call 'fclean' target and wipe imported librairies
reset:
	+$(MAKE) fclean
	rm -rf $(NUMCPP)


# ---------------------------------------------------------------------------- #
# test                                                                         #
# ---------------------------------------------------------------------------- #

docker_run:
	docker run -it localhost/linear:1.0


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


.PHONY: all re rere docker test docker_run clean fclean reset format help