/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_generators.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:35:52 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/24 13:45:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <limits>
#include <random>
#include <string>

namespace LibCpp::random {
    
    /**
     * Create a Mersenne Twister engine seeded from a random device.
     */
    inline std::mt19937 getSeed() {
        std::random_device rd;
        return std::mt19937{rd()};
    }    
}

namespace LibCpp::random::generators {
    /**
     * Generate a random string with a length between zero and max_len.
     */
    std::string string(std::mt19937& rng, size_t max_len) {
        std::uniform_int_distribution<size_t> len_dist(0, max_len);
        std::uniform_int_distribution<int> char_dist(1, 255);
    
        size_t len = len_dist(rng);
        std::string s;
        s.reserve(len);
    
        for (size_t i = 0; i < len; ++i)
            s.push_back(static_cast<char>(char_dist(rng)));
    
        return s;
    }
}