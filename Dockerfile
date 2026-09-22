# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/22 18:45:44 by cgajean           #+#    #+#              #
#    Updated: 2026/09/22 18:56:27 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM fedora:44

# Install dependencies
RUN dnf update && dnf install -y g++ make && \
    rm -rf /var/cache/dnf

# Copy the project files
WORKDIR /linear

COPY data data
COPY include include
COPY predict predict
COPY train train
COPY precision precision
COPY Makefile Makefile

# Compile the project
RUN make

ENTRYPOINT [ "sh" ]