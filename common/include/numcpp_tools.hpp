/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numcpp_tools.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:52:59 by root              #+#    #+#             */
/*   Updated: 2026/09/25 13:05:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "NumCpp.hpp"

namespace nc_tools {

nc::NdArray<double> genFromTxt(const char* filepath);
void dumpToTxt(std::string_view str, const char* filepath);
}  // namespace nc_tools
