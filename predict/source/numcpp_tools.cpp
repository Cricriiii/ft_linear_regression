/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numcpp_tools.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 10:04:25 by root              #+#    #+#             */
/*   Updated: 2026/09/25 15:28:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numcpp_tools.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <optional>

namespace {
std::optional<std::vector<double>> parseNumericString(const std::string& line,
                                                      char sep) {
    std::vector<double> values{};
    std::string field{};

    std::chrono::system_clock::time_point tp;
    std::stringstream ss{line};

    /* Parse first field: date */
    if (!std::getline(ss, field, sep)) {
        return std::nullopt;
    }

    std::chrono::system_clock::time_point date{};
    std::stringstream dateStream{field};
    dateStream >> std::chrono::parse("%F %T", date);

    if (dateStream.fail()) {
        return std::nullopt;
    }

    /* Next fields: numerics */
    while (std::getline(ss, field, sep)) {
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

std::vector<double> nc_tools::genFromTxt(const char* filepath) {
    std::optional<std::vector<double>> values{};

    /* Open file */
    std::ifstream file{openIfstream(filepath)};

    /* Retrieve most recent record */
    std::string record{};
    {
        std::chrono::system_clock::time_point tp;
        for (std::string next_record{}; std::getline(file, next_record);) {
            std::chrono::system_clock::time_point tp_next;

            std::stringstream ss{next_record};
            ss >> std::chrono::parse("%F %T", tp_next);

            if (tp_next > tp) {
                record = std::move(next_record);
            }
            tp = tp_next;
        }
    }

    values = parseNumericString(record, ',');

    /* Assess if numeric data was found */
    if (!values.has_value()) {
        throw std::runtime_error{"file doesn't contain any data\n"};
    }

    return *values;
}
