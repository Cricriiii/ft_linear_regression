/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:59:08 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/25 13:07:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>

#include "linear_regression.hpp"
#include "numcpp_tools.hpp"

constexpr std::size_t n_iterations = 1000;

void dumpCSV(const LinearRegression& lr, const char* ref_file) {
    std::string path_out{std::string{ref_file} + "_result.csv"};
    auto path{std::filesystem::path(path_out)};

    if (!std::filesystem::exists(path) || std::filesystem::is_empty(path)) {
        nc_tools::dumpToTxt(
            std::string{"time,theta1,theta0,x_mean,x_stdev,y_mean,y_stdev\n"},
            path_out.c_str());
    }

    std::stringstream ss{};
    ss << std::chrono::system_clock::now() << ",";
    ss << lr;

    nc_tools::dumpToTxt(ss.str(), path_out.c_str());
}

std::optional<Candidate> computeLinearRegression(const nc::NdArray<double>& X, const nc::NdArray<double>& Y) {
    std::optional<Candidate> best_fit{};
    std::vector<double> steps{0.001, 0.01, 0.0001, 0.1, 1.0};

    /* Find optimum */
    for (double step : steps) {
        /* Each step is evaluated from the same initial model. */
        auto theta{nc::zeros<double>({2, 1})};
        gradientDescent(X, Y, theta, step, n_iterations);

        const double current_cost = cost(X, Y, theta).item();
        Candidate candidate{current_cost, theta[0], theta[1], step};

        if (!best_fit.has_value() || candidate.cost < best_fit->cost) {
            best_fit = candidate;
        }
    }
    return best_fit;
}

int main([[maybe_unused]]int argc, char** argv) {
    try {
        /* Read file */
        nc::NdArray<double> raw_data{nc_tools::genFromTxt(argv[1])};

        /* Create X matrix */
        auto x = raw_data(raw_data.rSlice(), 0);
        double x_mean = nc::mean(x).item();
        double x_stdev = nc::stdev(x).item();
        x = (x - x_mean) / x_stdev;

        auto ones = nc::ones<double>(x.shape());
        auto X = nc::hstack({x, ones});

        /* Create Y matrix */
        auto Y = raw_data(raw_data.rSlice(), 1);
        double y_mean = nc::mean(Y).item();
        double y_stdev = nc::stdev(Y).item();
        Y = (Y - y_mean) / y_stdev;

        /* Compute the linear regression */
        std::optional<Candidate> best_fit = computeLinearRegression(X, Y);
        if (!best_fit.has_value()) {
            throw std::runtime_error{"couldn't find a valid model\n"};
        }

        /* Convert normalized parameters to the original units before saving
         * values */
        double theta_1 = best_fit->theta_1 * (y_stdev / x_stdev);
        double theta_0 =
            y_mean + y_stdev * best_fit->theta_0 - theta_1 * x_mean;

        /* Dump result in text file */
        dumpCSV(LinearRegression{theta_1, theta_0, x_mean, x_stdev, y_mean,
                                 y_stdev},
                argv[1]);

    } catch (std::runtime_error& e) {
        std::cerr << "\ntrain: error: " << e.what();
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "\ntrain: error: unexpected error";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}