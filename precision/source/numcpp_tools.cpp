/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numcpp_tools.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 10:04:25 by root              #+#    #+#             */
/*   Updated: 2026/09/25 14:37:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numcpp_tools.hpp"

#include <filesystem>
#include <fstream>
#include <optional>

namespace {
std::optional<std::stringstream> parseDateString(const std::string& line,
                                                 char sep) {
    std::chrono::system_clock::time_point date{};
    std::stringstream stream{line};
    std::string field{};

    if (!std::getline(stream, field, sep)) {
        return std::nullopt;
    }

    std::stringstream date_stream{field};
    date_stream >> std::chrono::parse("%F %T", date);
    if (date_stream.fail()) {
        return std::nullopt;
    }

    return stream;
}

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

std::optional<std::vector<double>> parseDatedNumericString(
    const std::string& line, char sep) {
    std::optional<std::stringstream> valid_stream{parseDateString(line, sep)};
    if (!valid_stream.has_value()) {
        return std::nullopt;
    }

    std::stringstream stream{std::move(*valid_stream)};
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
        } catch (const std::invalid_argument&) {
            return std::nullopt;
        } catch (const std::out_of_range&) {
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

std::vector<double> nc_tools::genLatestFromTxt(const char* filepath) {
    std::ifstream file{openIfstream(filepath)};
    std::chrono::system_clock::time_point latest_date{};
    std::string latest_record{};

    for (std::string record{}; std::getline(file, record);) {
        std::stringstream stream{record};
        std::chrono::system_clock::time_point date{};
        stream >> std::chrono::parse("%F %T", date);

        if (!stream.fail() && date > latest_date) {
            latest_date = date;
            latest_record = std::move(record);
        }
    }

    std::optional<std::vector<double>> values{
        parseDatedNumericString(latest_record, ',')};
    if (!values.has_value()) {
        throw std::runtime_error{"file doesn't contain any dated data\n"};
    }

    return *values;
}

void nc_tools::dumpToTxt(std::string_view str, const char* filepath) {
    /* Open file */
    std::ofstream file{openOfstream(filepath)};

    file << str;
}
