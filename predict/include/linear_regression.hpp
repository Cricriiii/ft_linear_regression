/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 23:12:29 by fox               #+#    #+#             */
/*   Updated: 2026/09/25 14:11:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <limits>
#include <sstream>

#include "NumCpp.hpp"
#include "linear_regression_types.hpp"

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