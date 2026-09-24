/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 23:12:29 by fox               #+#    #+#             */
/*   Updated: 2026/09/25 00:20:59 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <limits>
#include <sstream>

#include "NumCpp.hpp"

struct LinearRegression {
    double theta_x;
    double theta_bias;
    double x_mean;
    double x_stdev;

    LinearRegression() : theta_x{0}, theta_bias{0}, x_mean{0}, x_stdev{0} {
    }
    LinearRegression(double theta_x, double theta_bias, double x_mean,
                     double x_stdev)
        : theta_x{theta_x},
          theta_bias{theta_bias},
          x_mean{x_mean},
          x_stdev{x_stdev} {
    }
};

inline std::ofstream& operator<<(std::ofstream& ofs, const LinearRegression& lr) {
    ofs << lr.theta_x << ',' << lr.theta_bias << ',' << lr.x_mean << ','
        << lr.x_stdev << std::endl;
    return ofs;
}

nc::NdArray<double> model(const auto& X, const auto& theta);

nc::NdArray<double> cost(const nc::NdArray<double>& X,
                         const nc::NdArray<double>& Y,
                         const nc::NdArray<double>& theta);

nc::NdArray<double> gradient(const nc::NdArray<double>& X,
                             const nc::NdArray<double>& Y,
                             const nc::NdArray<double>& theta);

void gradient_descent(const nc::NdArray<double>& X,
                      const nc::NdArray<double>& Y, nc::NdArray<double>& theta,
                      double learning_rate, size_t n_iteration);