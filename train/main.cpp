/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:59:08 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/24 16:30:45 by root             ###   ########.fr       */
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

auto model(const auto& X, const auto& theta) {
    return nc::dot(X, theta);
}

auto cost(const nc::NdArray<double>& X, const nc::NdArray<double>& Y, const nc::NdArray<double>& theta) {

    double factor = 1.0 / (2 * Y.size());
    auto mdl = model(X, theta);
    auto sq_sub_expr = nc::square(nc::subtract<double>(mdl, Y));
    auto sigma_sum = nc::sum(sq_sub_expr);
    
    return nc::multiply<double>(sigma_sum, factor);
}

auto gradient(const nc::NdArray<double>& X, const nc::NdArray<double>& Y, const nc::NdArray<double>& theta) {
    double factor = 1.0 / Y.size();
    auto mdl = model(X, theta);
    auto sub_expr = nc::subtract<double>(mdl, Y);
    auto expr = nc::dot(X.transpose(), sub_expr);

    return nc::multiply(expr, factor);
}

void gradient_descent(const nc::NdArray<double>& X, const nc::NdArray<double>& Y, nc::NdArray<double>& theta, double learning_rate, size_t n_iteration) {
    
    for (size_t i = 0; i < n_iteration; ++i) {
        auto theta_grad = nc::multiply(gradient(X, Y, theta), learning_rate);

        theta = nc::subtract(theta, theta_grad);
        std::cout << theta << '\n';
    }
}

int main([[maybe_unused]] int argc, char** argv) {

    try {
        /* Open file */
        std::ifstream file{LibCpp::Cpp_IO::openFile(argv[1])};

        /* Read file */
        nc::NdArray<double> raw_data{LibCpp::Cpp_IO::readCSV<double>(file)};

        /* Create X matrix */
        auto x = raw_data(raw_data.rSlice(), 0);
        x = nc::multiply(x, 1.0 / 100000.0);
        auto ones = nc::ones<double>(x.shape());
        auto X = nc::hstack({x, ones});

        LibCpp::nc::clearMatrix(x);
        LibCpp::nc::clearMatrix(ones);

        /* Create Y matrix */
        auto Y = raw_data(raw_data.rSlice(), 1);
        // Y = nc::multiply(Y, 1.0 / 100000.0);

        LibCpp::nc::clearMatrix(raw_data);

        /* Initialize theta with random values */
        auto theta = nc::random::randN<double>({2, 1});

        /* Cost */
        auto cst = cost(X, Y, theta);    
        
        gradient_descent(X, Y, theta, 0.01, 1000);

        cst = cost(X, Y, theta);

    } catch (std::runtime_error& e) {
        std::cerr << "\ntrain: error: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}