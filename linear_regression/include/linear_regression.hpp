/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 16:18:19 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/26 16:57:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "NumCpp.hpp"
#include "linear_regression_types.hpp"

/**
 * Dump a LinearRegression object in a StringStream object
 */
inline std::stringstream& operator<<(std::stringstream& ss,
                                     const LinearRegression& lr) {
    ss << lr.theta_1 << ',' << lr.theta_0 << ',' << lr.x_mean << ','
       << lr.x_stdev << ',' << lr.y_mean << ',' << lr.y_stdev << std::endl;
    return ss;
}

/**
 * Computes the predictions produced by the linear model.
 * X contains the input features and theta contains their coefficients.
 */
nc::NdArray<double> model(const auto& X, const auto& theta);

/**
 * Computes the mean squared error cost divided by two.
 * A lower cost means that the predictions are closer to the target values.
 */
nc::NdArray<double> cost(const nc::NdArray<double>& X,
                         const nc::NdArray<double>& Y,
                         const nc::NdArray<double>& theta);

/**
 * Computes the gradient of the cost function for every parameter in theta.
 * The gradient indicates how each parameter should change to reduce the cost.
 */
nc::NdArray<double> gradient(const nc::NdArray<double>& X,
                             const nc::NdArray<double>& Y,
                             const nc::NdArray<double>& theta);

/**
 * Optimizes theta with gradient descent.
 * At each iteration, theta is moved in the opposite direction of the gradient.
 * The loop stops when the cost no longer changes significantly or when the
 * maximum number of iterations is reached.
 */
void gradientDescent(const nc::NdArray<double>& X, const nc::NdArray<double>& Y,
                     nc::NdArray<double>& theta, double learning_rate,
                     size_t n_iteration);