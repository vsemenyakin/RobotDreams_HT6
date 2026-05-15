#include <gtest/gtest.h>
#include "ballistics.hpp"

constexpr float precision{ 0.001f };

TEST(Ballistics, Test1) {

    const float attackSpeed = 10.f;
    const float zd = 100.f;
    const float ammo_m = 0.35f;
    const float ammo_d = 0.07f;
    const float ammo_l = 0.f;

    float ammo_fligthTime;
    float h;
	computeAmmoDrop(ammo_fligthTime, h, attackSpeed, zd, ammo_m, ammo_d, ammo_l);

    EXPECT_NEAR(ammo_fligthTime, 5.74976f, precision);
    EXPECT_NEAR(h, 37.1102f, precision);
}

TEST(Ballistics, Test2) {

    const float attackSpeed = 10.f;
    const float zd = 100.f;
    const float ammo_m = 0.45f;
    const float ammo_d = 0.1f;
    const float ammo_l = 1.f;

    float ammo_fligthTime;
    float h;
	computeAmmoDrop(ammo_fligthTime, h, attackSpeed, zd, ammo_m, ammo_d, ammo_l);

    EXPECT_NEAR(ammo_fligthTime, 6.26317, precision);
    EXPECT_NEAR(h, -806.475, precision);
}

