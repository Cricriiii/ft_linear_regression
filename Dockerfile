# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/22 18:45:44 by cgajean           #+#    #+#              #
#    Updated: 2026/09/26 18:02:41 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM fedora:44

# Copy the project files
WORKDIR /projects

COPY data data
COPY linear_regression linear_regression
COPY Makefile Makefile

# # Install dependencies
RUN dnf install -y \
        make \
        g++ \
        boost-devel \
        python3-devel \
        python3-numpy \
        python3-matplotlib \
        python3-scikit-learn \
        git \
        zsh \
        curl \
    && sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" \
    && dnf clean all \
    && rm -rf /var/cache/dnf

# Compile the project
RUN make

ENTRYPOINT [ "zsh" ]