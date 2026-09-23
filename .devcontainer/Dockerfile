# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/23 16:22:29 by cgajean           #+#    #+#              #
#    Updated: 2026/09/23 16:24:57 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM fedora:44

RUN dnf install -y \
        boost-devel \
        cmake \
        gcc-c++ \
        gdb \
        git \
        make \
        sudo \
        zsh \
        curl \
    && sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" \
    && dnf clean all \
    && rm -rf /var/cache/dnf

RUN useradd --create-home --shell /bin/bash vscode && \
    echo "vscode ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/vscode && \
    chmod 0440 /etc/sudoers.d/vscode

WORKDIR /workspaces/ft_linear_regression

CMD ["/bin/zsh"]