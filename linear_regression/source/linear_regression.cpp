/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 23:12:14 by fox               #+#    #+#             */
/*   Updated: 2026/09/25 12:38:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_regression.hpp"

/**
 * Computes the predictions produced by the linear model.
 * X contains the input features and theta contains their coefficients.
 */
nc::NdArray<double> model(const auto& X, const auto& theta) {
    return nc::dot(X, theta);
}

/**
 * Computes the mean squared error cost divided by two.
 * A lower cost means that the predictions are closer to the target values.
 */
nc::NdArray<double> cost(const nc::NdArray<double>& X,
                         const nc::NdArray<double>& Y,
                         const nc::NdArray<double>& theta) {
    auto mdl = model(X, theta);
    auto sigma_sum = nc::sum(nc::square(mdl - Y));

    return sigma_sum * (1.0 / (2 * Y.size()));
}

/**
 * Computes the gradient of the cost function for every parameter in theta.
 * The gradient indicates how each parameter should change to reduce the cost.
 */
nc::NdArray<double> gradient(const nc::NdArray<double>& X,
                             const nc::NdArray<double>& Y,
                             const nc::NdArray<double>& theta) {
    auto mdl = model(X, theta);
    auto sub_expr = mdl - Y;

    return nc::dot(X.transpose(), sub_expr) * (1.0 / Y.size());
}

/**
 * Optimizes theta with gradient descent.
 * At each iteration, theta is moved in the opposite direction of the gradient.
 * The loop stops when the cost no longer changes significantly or when the
 * maximum number of iterations is reached.
 */
void gradientDescent(const nc::NdArray<double>& X, const nc::NdArray<double>& Y,
                     nc::NdArray<double>& theta, double learning_rate,
                     size_t n_iteration) {
    double previous_cost = std::numeric_limits<double>::max();

    for (size_t i = 0; i < n_iteration; ++i) {
        theta = theta - gradient(X, Y, theta) * learning_rate;

        double current_cost = cost(X, Y, theta).item();

        if (std::abs(previous_cost - current_cost) < 1e-8) {
            break;
        }

        previous_cost = current_cost;
    }
}
