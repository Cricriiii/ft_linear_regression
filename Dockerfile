# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/22 18:45:44 by cgajean           #+#    #+#              #
#    Updated: 2026/09/23 15:31:26 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM fedora:44

# Copy the project files
WORKDIR /linear

COPY data data
COPY include include
COPY predict predict
COPY train train
COPY precision precision
COPY Makefile Makefile

# Install dependencies
# RUN dnf update && dnf install -y g++ make git && \
#     git clone https://github.com/dpilger26/NumCpp.git numcpp && \
#     dnf remove -y git && \
#     rm -rf /var/cache/dnf

# # Install dependencies
RUN dnf update && dnf install -y g++ make cmake boost-devel git && \
    git clone https://github.com/dpilger26/NumCpp.git numcpp && \
    cd $_ && mkdir build && cd $_ && cmake .. && \
    cmake --build . --target install && \
    dnf remove -y cmake git && \    
    rm -rf /var/cache/dnf

# Compile the project
RUN make

ENTRYPOINT [ "sh" ]