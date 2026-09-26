/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 16:18:30 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/26 16:55:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_regression.hpp"

/**
 * MODEL
 */
inline nc::NdArray<double> model(const auto& X, const auto& theta) {
    return nc::dot(X, theta);
}

/**
 * COST
 */
nc::NdArray<double> cost(const nc::NdArray<double>& X,
                         const nc::NdArray<double>& Y,
                         const nc::NdArray<double>& theta) {
    return nc::sum(nc::square(model(X, theta) - Y)) * (1.0 / (2 * Y.size()));
}

/**
 * GRADIENT
 */
nc::NdArray<double> gradient(const nc::NdArray<double>& X,
                             const nc::NdArray<double>& Y,
                             const nc::NdArray<double>& theta) {
    auto mdl = model(X, theta);
    auto sub_expr = mdl - Y;

    return nc::dot(X.transpose(), sub_expr) * (1.0 / Y.size());
}

/**
 * GRADIENT DESCENT algorithm
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
