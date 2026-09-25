/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 23:12:29 by fox               #+#    #+#             */
/*   Updated: 2026/09/25 12:33:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <limits>
#include <sstream>

#include "NumCpp.hpp"

struct LinearRegression {
    double theta_1;
    double theta_0;
    double x_mean;
    double x_stdev;
    double y_mean;
    double y_stdev;

    LinearRegression()
        : theta_1{0}, theta_0{0}, x_mean{0}, x_stdev{0}, y_mean{0}, y_stdev{0} {
    }
    LinearRegression(double theta_1, double theta_0, double x_mean,
                     double x_stdev, double y_mean, double y_stdev)
        : theta_1{theta_1},
          theta_0{theta_0},
          x_mean{x_mean},
          x_stdev{x_stdev},
          y_mean{y_mean},
          y_stdev{y_stdev} {
    }
};

struct Candidate {
    double cost;
    double theta_1;
    double theta_0;
    double step;

    Candidate() : cost{}, theta_1{}, theta_0{}, step{} {
    }
    Candidate(double c, double t1, double t0, double s)
        : cost{c}, theta_1{t1}, theta_0{t0}, step{s} {
    }
};

inline std::stringstream& operator<<(std::stringstream& ss,
                                     const LinearRegression& lr) {
    ss << lr.theta_1 << ',' << lr.theta_0 << ',' << lr.x_mean << ','
       << lr.x_stdev << ',' << lr.y_mean << ',' << lr.y_stdev << std::endl;
    return ss;
}

nc::NdArray<double> model(const auto& X, const auto& theta);

nc::NdArray<double> cost(const nc::NdArray<double>& X,
                         const nc::NdArray<double>& Y,
                         const nc::NdArray<double>& theta);

nc::NdArray<double> gradient(const nc::NdArray<double>& X,
                             const nc::NdArray<double>& Y,
                             const nc::NdArray<double>& theta);

void gradientDescent(const nc::NdArray<double>& X, const nc::NdArray<double>& Y,
                     nc::NdArray<double>& theta, double learning_rate,
                     size_t n_iteration);