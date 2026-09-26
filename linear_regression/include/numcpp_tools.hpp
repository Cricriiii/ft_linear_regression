/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numcpp_tools.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 16:18:25 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/26 16:18:27 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "NumCpp.hpp"

namespace nc_tools {

/**
 * Load a numerical CSV file into a matrix, one row per line.
 * Lines that are not purely numerical (such as headers) are skipped.
 */
nc::NdArray<double> genFromTxt(const char* filepath);

/**
 * Return the numerical values of the most recent record of a dated CSV file.
 * Each record must start with a "YYYY-MM-DD HH:MM:SS" date field.
 */
std::vector<double> genLatestFromTxt(const char* filepath);

/**
 * Append a string at the end of a file, creating it if needed
 */
void dumpToTxt(std::string_view str, const char* filepath);
}  // namespace nc_tools
