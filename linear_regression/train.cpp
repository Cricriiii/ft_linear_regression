/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 16:19:05 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/26 18:09:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matplotlibcpp.h"

#include <chrono>

#include "linear_regression.hpp"
#include "numcpp_tools.hpp"

namespace plt = matplotlibcpp;

constexpr size_t pltWidth = 1200;
constexpr size_t pltHeight = 700;
constexpr size_t pltThick = 10;
constexpr std::size_t n_iterations = 1000;

/**
 * Append the trained model, timestamped, to "<ref_file>_result.csv".
 * The CSV header is written first if the file doesn't exist or is empty.
 */
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

/**
 * Run gradient descent with several learning rates on normalized data and
 * return the candidate with the lowest final cost.
 */
std::optional<Candidate> computeLinearRegression(const nc::NdArray<double>& X,
                                                 const nc::NdArray<double>& Y) {
    std::optional<Candidate> best_fit{};
    std::vector<double> steps{0.001, 0.01, 0.0001, 0.1};

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

/**
 * Plot the dataset and the regression line, then save the figure as a
 * timestamped PNG in the "output" directory.
 */
void plot(const nc::NdArray<double>& X, const nc::NdArray<double>& Y,
          double theta_1, double theta_0) {
    std::vector<double> vx{}, vy{};

    plt::backend("Agg");
    /* Extract raw data values */
    uint32_t size = X.size();
    for (uint32_t i = 0; i < size; ++i) {
        vx.push_back(X[i]);
        vy.push_back(Y[i]);
    }

    plt::figure_size(pltWidth, pltHeight);
    plt::scatter(vx, vy, pltThick);

    double min_x = *std::min_element(vx.begin(), vx.end());
    double max_x = *std::max_element(vx.begin(), vx.end());

    std::vector<double> trend_x{min_x, max_x};
    std::vector<double> trend_y{trend_x[0] * theta_1 + theta_0,
                                trend_x[1] * theta_1 + theta_0};
    plt::plot(trend_x, trend_y, "r--");

    /* Save output as png */
    const auto output_dir = std::filesystem::path{"output"};
    std::filesystem::create_directories(output_dir);
    const auto now = std::chrono::system_clock::now();
    const auto timestamp =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch())
            .count();
    const auto output_file =
        output_dir / ("plot_" + std::to_string(timestamp) + ".png");
    plt::save(output_file.string());
}

int main([[maybe_unused]] int argc, char** argv) {
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

        plot(raw_data(raw_data.rSlice(), 0), raw_data(raw_data.rSlice(), 1),
             theta_1, theta_0);

        std::cout << "theta_1 = " << theta_1 << "\ntheta_0 = " << theta_0
                  << std::endl;

    } catch (std::runtime_error& e) {
        std::cerr << "\ntrain: error: " << e.what();
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "\ntrain: error: unexpected error";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}