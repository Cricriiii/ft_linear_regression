/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:59:08 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/24 13:51:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>

#include "LibCpp.hpp"
#include "NumCpp.hpp"

int main([[maybe_unused]] int argc, char** argv) {
    try {
        /* Open file */
        std::ifstream file{LibCpp::Cpp_IO::openFile(argv[1])};

        /* Read file */
        auto arr = LibCpp::Cpp_IO::readCSV<double>(file);

    } catch (std::runtime_error& e) {
        std::cerr << "\ntrain: error: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}