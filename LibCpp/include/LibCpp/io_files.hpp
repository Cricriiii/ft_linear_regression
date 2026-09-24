/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_files.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:35:49 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/24 13:47:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <optional>
#include "NumCpp.hpp"



namespace LibCpp::C_IO {

    /**
     * Return a file descriptor after closing it and clearing errno.
     */
    inline int unopened_fd(int fd) {
        /* Close errno anyway, which sets errno to EBADF */
        close(fd);
        /* Reset errno */
        *__errno_location() = 0;
        return fd;
    }
}



/* ************************************************************************** */
    
std::optional<std::vector<double>> parseNumericString(const std::string& line,
                                                    char sep) {
    std::istringstream stream{line};
    std::vector<double> values{};
    std::string field{};

    while (std::getline(stream, field, sep)) {
        try {
            size_t position{};
            double value = std::stod(field, &position);

            if (position != field.size()) {
                return std::nullopt;
            }

            values.push_back(value);
        } catch (const std::invalid_argument& e) {
            return std::nullopt;
        } catch (const std::out_of_range& e) {
            return std::nullopt;
        }
    }
    return values;
}

namespace LibCpp::Cpp_IO {

    /**
     * Open ifstream and throw if it fails.
     */
    std::ifstream openFile(const char* filepath) {
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

    template<typename T>
    nc::NdArray<T> readCSV(std::ifstream& file) {
        nc::NdArray<T> matrix{};
        std::optional<std::vector<T>> values{};

        /* Skip headers */
        for (std::string line{}; std::getline(file, line);) {
            values = parseNumericString(line, ',');
            if (values.has_value()) {
                break;
            }
        }

        /* Assess if numeric data was found */
        if (!values.has_value()) {
            throw std::runtime_error{"wrong data format\n"};
        }
        
        try {
            /* Register the first line of the matrix */
            auto new_row = nc::fromiter<T>(values->begin(), values->end());
            matrix = nc::append(matrix, std::move(new_row), nc::Axis::ROW);
        
            for (std::string line{}; std::getline(file, line);) {
            /* Register the rest of the file */
                values = parseNumericString(line, ',');
                if (values.has_value()) {
                    auto new_row = nc::fromiter<T>(values->begin(), values->end());
                    matrix = nc::append(matrix, std::move(new_row), nc::Axis::ROW);
                }
            }
        } catch (std::invalid_argument& e) {
            throw std::runtime_error{"wrong data format\n"};
        }

        std::cout << matrix;

        return matrix;
    }    
}
