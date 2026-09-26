/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_streams.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 16:28:51 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/26 16:47:51 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_streams.hpp"

#include <filesystem>
#include <sstream>

/**
 * OPEN OFSTREAM
 */
std::ofstream openOfstream(std::string&& filepath,
                           std::ios_base::openmode mode) {
    /* Test filepath */
    if (filepath.empty()) {
        throw std::runtime_error{" path to file is required\n"};
    }

    /* Open file */
    std::ofstream file{filepath.c_str(), mode};
    if (!file.is_open()) {
        throw std::runtime_error{std::move(filepath + " couldn't be opened\n")};
    }
    return file;
}

/**
 * OPEN IFSTREAM
 */
std::ifstream openIfstream(const char* filepath) {
    /* Test filepath */
    if (filepath == nullptr) {
        throw std::runtime_error{" path to file is required\n"};
    }

    auto path{std::filesystem::path(filepath)};
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error{std::string{filepath} + " doesn't exist\n"};
    } else if (std::filesystem::is_empty(path)) {
        throw std::runtime_error{std::string{filepath} + " is empty\n"};
    }

    /* Open file */
    std::ifstream file{filepath, std::ios::binary};
    if (!file.is_open()) {
        throw std::runtime_error{std::string{filepath} +
                                 " couldn't be opened\n"};
    }
    return file;
}