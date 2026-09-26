/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 16:19:00 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/26 16:19:02 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include <atomic>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <numcpp_tools.hpp>
#include <optional>
#include <sstream>

#include "NumCpp.hpp"
#include "linear_regression_types.hpp"

namespace {
volatile bool running = 1;

/**
 * SIGINT handler: request the end of the prediction loop
 */
void handleInterrupt(int signal) {
    if (signal == SIGINT) {
        running = 0;
    }
}
}  // namespace

/**
 * Run before main: clear the terminal, install the SIGINT handler and print
 * the program banner
 */
__attribute__((constructor)) void printBanner() {
#ifdef __unix__
    std::system("clear");
#endif

    signal(SIGINT, handleInterrupt);

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
    }
}

/**
 * Prompt the user for a mileage until a valid number is entered
 */
double readMileage() {
    std::optional<double> value{};
    while (true) {
        std::cout << "Enter a mileage: ";
        if ((value = readDouble()).has_value()) {
            return *value;
        } else {
            std::cout << "incorrect input\n";
        }
    }
}

int main([[maybe_unused]] int argc, char** argv) {
    try {
        std::vector<double> data{nc_tools::genLatestFromTxt(argv[1])};

        while (running) {
            double mileage = readMileage();
            double estimated_price =
                round(std::max(mileage * data[0] + data[1], 0.0));

            std::cout << "Estimated price: " << estimated_price << std::endl;
        }
    } catch (...) {
        std::cerr << "predict: error: unexpected error\n";
        return EXIT_FAILURE;
    }
    return 0;
}
