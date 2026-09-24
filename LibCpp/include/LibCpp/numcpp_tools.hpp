/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numcpp_tools.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:01:56 by root              #+#    #+#             */
/*   Updated: 2026/09/24 17:07:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "NumCpp.hpp"

namespace LibCpp::nc {
    template <typename T>
    void clearMatrix(::nc::NdArray<T>& matrix) {
        matrix = ::nc::NdArray<T>{};
    }
}