/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numcpp_tools.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 09:52:59 by root              #+#    #+#             */
/*   Updated: 2026/09/25 15:16:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "NumCpp.hpp"

namespace nc_tools {

std::vector<double> genFromTxt(const char* filepath);
}  // namespace nc_tools
