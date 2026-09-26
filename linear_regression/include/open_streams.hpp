/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_streams.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 16:29:27 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/26 16:47:47 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>

/**
 * Open file and return an ofstream object, or throw
 */
std::ofstream openOfstream(std::string&& filepath,
                           std::ios_base::openmode mode = std::ios::binary |
                                                          std::ofstream::app);

/**
 * Open file and return an ifstream object, or throw
 */
std::ifstream openIfstream(const char* filepath);