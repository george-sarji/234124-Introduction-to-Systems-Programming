#ifndef CHARACTER_H
#define CHARACTER_H

namespace mtm
{
    class Character
    {
    private:
        int health, ammo, range, power, move_range, attack_cost, reload_amount;

    protected:
        explicit Character(int health, int ammo, int range, int power, int move_range,
                           int attack_cost, int reload_amount) : health(health), ammo(ammo),
                                                                 range(range), power(power), move_range(move_range),
                                                                 attack_cost(attack_cost), reload_amount(reload_amount) {}
    };
} // namespace mtm

#endif