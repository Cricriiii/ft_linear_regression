/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numcpp_tools.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 10:04:25 by root              #+#    #+#             */
/*   Updated: 2026/09/25 13:05:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numcpp_tools.hpp"

#include <filesystem>
#include <fstream>
#include <optional>

namespace {
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

std::ofstream openOfstream(std::string&& filepath,
                           std::ios_base::openmode mode = std::ios::binary |
                                                          std::ofstream::app) {
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
 * Open file istream and throw if it fails.
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
}  // namespace

nc::NdArray<double> nc_tools::genFromTxt(const char* filepath) {
    nc::NdArray<double> matrix{};
    std::optional<std::vector<double>> values{};

    /* Open file */
    std::ifstream file{openIfstream(filepath)};

    /* Skip headers */
    for (std::string line{}; std::getline(file, line);) {
        values = parseNumericString(line, ',');
        if (values.has_value()) {
            break;
        }
    }

    /* Assess if numeric data was found */
    if (!values.has_value()) {
        throw std::runtime_error{"file doesn't contain any data\n"};
    }

    try {
        /* Register the first line of the matrix */
        auto new_row = nc::fromiter<double>(values->begin(), values->end());
        matrix = nc::append(matrix, std::move(new_row), nc::Axis::ROW);

        for (std::string line{}; std::getline(file, line);) {
            /* Register the rest of the file */
            values = parseNumericString(line, ',');
            if (values.has_value()) {
                auto new_row =
                    nc::fromiter<double>(values->begin(), values->end());
                matrix = nc::append(matrix, std::move(new_row), nc::Axis::ROW);
            }
        }
    } catch (std::invalid_argument& e) {
        throw std::runtime_error{"data is not properly formatted\n"};
    }

    return matrix;
}

void nc_tools::dumpToTxt(std::string_view str, const char* filepath) {
    /* Open file */
    std::ofstream file{openOfstream(filepath)};

    file << str;
}

// void nc_tools::dumpToTxt(const std::string& str, const char* filepath) {
//     /* Open file */
//     std::ofstream file{openOfstream(filepath)};

//     file << str;
// }
