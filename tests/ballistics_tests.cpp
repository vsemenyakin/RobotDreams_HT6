#include <gtest/gtest.h>
#include "ballistics.hpp"

TEST(Ballistics, Test1) {

    const float attackSpeed = 10.f;
    const float zd = 100.f;
    const float ammo_m = 0.35f;
    const float ammo_d = 0.07f;
    const float ammo_l = 0.f;

    float ammo_fligthTime;
    float h;
	computeAmmoDrop(ammo_fligthTime, h, attackSpeed, zd, ammo_m, ammo_d, ammo_l);

    EXPECT_NEAR(ammo_fligthTime, 5.74976f, 0.0001f);
    EXPECT_NEAR(h, 37.1102f, 0.0001f);
}

TEST(Ballistics, Test2) {

    // const float attackSpeed = 10.f;
    // const float zd = 100.f;
    // const float ammo_m = 0.35f;
    // const float ammo_d = 0.07f;
    // const float ammo_l = 0.f;

    // float ammo_fligthTime;
    // float h;
	// computeAmmoDrop(ammo_fligthTime, h, attackSpeed, zd, ammo_m, ammo_d, ammo_l);

    // EXPECT_NEAR(ammo_fligthTime, 5.74976f, 0.0001f);
    // EXPECT_NEAR(h, 37.1102f, 0.0001f);
}


