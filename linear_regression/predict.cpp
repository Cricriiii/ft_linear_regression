/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 16:19:00 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/26 18:18:04 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <iostream>
#include <optional>

#include "NumCpp.hpp"
#include "linear_regression_types.hpp"
#include "numcpp_tools.hpp"

/**
 * Run before main: clear the terminal, install the SIGINT handler and print
 * the program banner
 */
__attribute__((constructor)) void printBanner() {
#ifdef __unix__
    std::system("clear");
#endif

    std::cout << "ｆｔ＿ｌｉｎｅａｒ＿ｒｅｇｒｅｓｓｉｏｎ\n" << std::endl;
}

/**
 * Read one word from stdin and convert it to a double.
 * Return nullopt if the whole word isn't a valid number.
 */
std::optional<double> readDouble() {
    std::string input{};

    /* Get input and flush leftovers */
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    size_t pos{};
    try {
        double value{std::stod(input.c_str(), &pos)};

        if (pos == input.length()) {
            return value;
        } else {
            return std::nullopt;
        }

    } catch (std::invalid_argument& e) {
        return std::nullopt;
    } catch (std::out_of_range& e) {
        return std::nullopt;
    }
}

/**
 * Prompt the user for a mileage until a valid number is entered.
 * Return nullopt when stdin reaches EOF (Ctrl+D).
 */
std::optional<double> readMileage() {
    std::optional<double> value{};
    while (true) {
        std::cout << "Enter a mileage: ";
        if ((value = readDouble()).has_value() && value >= 0) {
            return value;
        } else if (std::cin.eof()) {
            std::cout << std::endl;
            return std::nullopt;
        } else {
            std::cout << "incorrect input\n";
        }
    }
}

/**
 * Load the latest trained thetas as {theta_1, theta_0}.
 * Return {0, 0} if the model hasn't been trained yet (missing, empty or
 * undated result file).
 */
std::vector<double> loadThetas(const char* filepath) {
    try {
        return nc_tools::genLatestFromTxt(filepath);
    } catch (std::runtime_error&) {
        return {0.0, 0.0};
    }
}

int main([[maybe_unused]] int argc, char** argv) {
    try {
        std::vector<double> data{loadThetas(argv[1])};

        while (true) {
            std::optional<double> mileage = readMileage();
            if (!mileage.has_value()) {
                break;
            }
            double estimated_price =
                round(std::max(*mileage * data[0] + data[1], 0.0));

            std::cout << "Estimated price: " << estimated_price << std::endl;
        }
    } catch (...) {
        std::cerr << "predict: error: unexpected error\n";
        return EXIT_FAILURE;
    }
    return 0;
}
