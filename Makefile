# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/22 18:34:12 by cgajean           #+#    #+#              #
#    Updated: 2026/09/26 10:09:39 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ---------------------------------------------------------------------------- #
# compile                                                                      #
# ---------------------------------------------------------------------------- #

MAKEFLAGS	+= -j $(shell nproc)


# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

LINEAR_REG	:= linear_regression
TRAIN		:= train
PREDICT		:= predict
PRECIS		:= precision

NUMCPP		:= NumCpp
MATPLOT		:= matplotlib-cpp
OUTPUT_IMG	:= output


# ---------------------------------------------------------------------------- #
# build                                                                        #
# ---------------------------------------------------------------------------- #

## Build whole project
all: $(TRAIN) $(PREDICT) $(PRECIS)

## Build train program
$(TRAIN):
	+$(MAKE) -C $(LINEAR_REG) $@ TRAIN=$@

## Build predict program
$(PREDICT):
	+$(MAKE) -C $(LINEAR_REG) $@ PREDICT=$@

## Build precision program
$(PRECIS):
	+$(MAKE) -C $(LINEAR_REG) $@ PRECIS=$@

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

## Import NumCpp
$(NUMCPP):
ifeq ($(wildcard $(NUMCPP)),)
	git clone https://github.com/dpilger26/NumCpp.git $(NUMCPP);
else
	@echo "$(NUMCPP) is already installed"
endif

## Import matplotlib-cpp
$(MATPLOT):
ifeq ($(wildcard $(MATPLOT)),)
	git clone https://github.com/lava/matplotlib-cpp.git $(MATPLOT)
else
	@echo "$(MATPLOT) is already installed"
endif


# ---------------------------------------------------------------------------- #
# clean                                                                        #
# ---------------------------------------------------------------------------- #

## Clean .object folders
clean:
	+$(MAKE) -C $(LINEAR_REG) clean TRAIN=$(TRAIN) PREDICT=$(PREDICT) PRECIS=$(PRECIS)

## Call 'clean' target and delete executable files
fclean:
	+$(MAKE) -C $(LINEAR_REG) fclean TRAIN=$(TRAIN) PREDICT=$(PREDICT) PRECIS=$(PRECIS)
	rm -rf $(OUTPUT_IMG)

## Call 'fclean' target and wipe imported librairies
reset:
	+$(MAKE) fclean
	rm -rf $(NUMCPP)
	rm -rf $(MATPLOT)


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

## Generate a random regression dataset
regression:
	@python3 -c 'import csv; \
	import secrets; \
	import numpy as np; \
	from sklearn.datasets import make_regression; \
	seed = secrets.randbits(32); \
	rng = np.random.default_rng(seed); \
	x_scale = 10 ** rng.uniform(1, 5); \
	y_scale = 10 ** rng.uniform(1, 5); \
	noise = 10 ** rng.uniform(0, 3); \
	x, y = make_regression(n_samples=10000, n_features=1, noise=noise, random_state=seed); \
	x *= x_scale; \
	y *= y_scale; \
	file = open("data/generated.csv", "w", newline=""); \
	writer = csv.writer(file, lineterminator="\n"); \
	writer.writerow(["x", "y"]); \
	writer.writerows((features[0], target) for features, target in zip(x, y)); \
	file.close(); \
	print(f"Generated data/generated.csv with seed {seed}, x scale {x_scale:.2f}, y scale {y_scale:.2f}, noise {noise:.2f}")';

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

.PHONY: all re rere docker test docker_run clean fclean reset format regression help