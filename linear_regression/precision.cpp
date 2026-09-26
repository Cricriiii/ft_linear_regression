/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:59:08 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/25 23:08:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NumCpp.hpp"
#include "numcpp_tools.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "precision: error: usage: filename database result\n";
        return EXIT_FAILURE;
    }

    try {
        /* Read files */
        std::vector<double> latest{nc_tools::genLatestFromTxt(argv[2])};
        nc::NdArray<double> data{nc_tools::genFromTxt(argv[1])};

        /* Isolate X and Y matrix */
        nc::NdArray<double> x{data(data.rSlice(), 0)};
        nc::NdArray<double> y{data(data.rSlice(), 1)};

        /* Compute Y mean */
        double y_mean = nc::mean(y).item();

        /* Compute Total Sum of Squares */
        double SStot = nc::sum(nc::square(y - y_mean)).item();

        /* Compute Y = theta_1 * mileage + theta_0 */
        nc::NdArray<double> y_calculated(x * latest[0] + latest[1]);

        /* Compute Residual Sum of Squares */
        double SSres{nc::sum(nc::square(y - y_calculated)).item()};

        /* Compute precision */
        double precision{1.0 - (SSres / SStot)};
        std::cout << "Precision: " << precision << std::endl;

    } catch (std::exception& e) {
        std::cerr << "precision: error: " << e.what() << std::endl;
    }
    return 0;
}