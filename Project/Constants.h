#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>

namespace Constants
{
	inline constexpr int min_attack_bonus{ 1 };
	inline constexpr int max_attack_bonus{ 5 };

	inline constexpr int min_crit_multiplier{ 200 };
	inline constexpr int max_crit_multiplier{ 299 };
	inline constexpr int critThreshold{ 3 };

	inline constexpr std::array statThreshold{ 6, 8, 10, 13, 16, 20 };
	inline constexpr double low_bonus{ -0.1 };
	inline constexpr double high_bonus{ 0.2 };

	inline constexpr int min_armor_reduce{ 40 };
	inline constexpr int max_armor_reduce{ 60 };
	inline constexpr int min_block_reduce{ 50 };
	inline constexpr int max_block_reduce{ 100 };

	inline constexpr int points_to_distribute{ 10 };
	inline constexpr int initial_ap{ 10 };

	inline constexpr int concentrationManaRestore{ 15 };
    inline constexpr int healAmount{ 20 };
    inline constexpr size_t maxInventorySize{ 5 };

	inline constexpr int block_cost{ 5 };
	inline constexpr int melee_cost{ 5 };
	inline constexpr int cast_cost{ 3 };
}

#endif