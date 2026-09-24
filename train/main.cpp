/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:59:08 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/25 00:07:31 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io_files.hpp"
#include "linear_regression.hpp"

void dumpCSV(const LinearRegression& lr, const char* ref_file) {
    std::string path_out{std::string{ref_file} + "_result.csv"};
    auto path{std::filesystem::path(path_out)};

    auto file_out = Cpp_IO::openOfstream(std::move(path_out));
    if (std::filesystem::is_empty(path)) {
        file_out << "theta,theta_bias,x_mean,x_stdev\n";
    }

    file_out << lr;
}

int main([[maybe_unused]] int argc, char** argv) {
    try {
        /* Open file */
        auto file_in{Cpp_IO::openIfstream(argv[1])};

        /* Read file */
        nc::NdArray<double> raw_data{Cpp_IO::readCSV<double>(file_in)};

        /* Create X matrix */
        auto x = raw_data(raw_data.rSlice(), 0);
        double x_mean = nc::mean(x).item();
        double x_stdev = nc::stdev(x).item();
        x = (x - x_mean) / x_stdev;

        auto ones = nc::ones<double>(x.shape());
        auto X = nc::hstack({x, ones});

        /* Create Y matrix */
        auto Y = raw_data(raw_data.rSlice(), 1);

        /* Initialize theta with random values */
        auto theta = nc::zeros<double>({2, 1});

        /* Cost */
        auto cst = cost(X, Y, theta);

        gradient_descent(X, Y, theta, 0.01, 1000);

        /* Write result */
        dumpCSV(LinearRegression{theta[0], theta[1], x_mean, x_stdev}, argv[1]);

    } catch (std::runtime_error& e) {
        std::cerr << "\ntrain: error: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}