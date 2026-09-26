# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fox <fox@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/23 16:22:29 by cgajean           #+#    #+#              #
#    Updated: 2026/09/26 10:37:46 by fox              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM fedora:44

RUN dnf install -y \
        g++ \
        clang-format \
        boost-devel \
        make \
        gdb \
        git \
        sudo \
        zsh \
        curl \
        valgrind \
        python3-devel \
        python3-numpy \
        python3-matplotlib \
        python3-scikit-learn \
    && sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" \
    && dnf clean all \
    && rm -rf /var/cache/dnf

RUN useradd --create-home --shell /bin/bash vscode && \
    echo "vscode ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/vscode && \
    chmod 0440 /etc/sudoers.d/vscode

WORKDIR /workspaces/ft_linear_regression

CMD ["/bin/zsh"]