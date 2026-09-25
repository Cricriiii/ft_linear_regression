/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression_types.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 14:09:04 by root              #+#    #+#             */
/*   Updated: 2026/09/25 14:09:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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