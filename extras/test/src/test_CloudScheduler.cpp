/*
   Copyright (c) 2021 Arduino.  All rights reserved.
*/

/**************************************************************************************
   INCLUDE
 **************************************************************************************/

#include <catch.hpp>
#include <fakeit.hpp>

#include <property/types/CloudScheduler.h>

/**************************************************************************************
  TEST CODE
 **************************************************************************************/

SCENARIO("Tesing cloud type 'Scheduler' Ctor", "[Scheduler::Scheduler]")
{
  WHEN("A Scheduler(0,0,0,0,0) is being instantiated")
  {
    Scheduler schedule(0,0,0,0,0);
    THEN("The member variable 'start' should be 0") {
      REQUIRE(schedule.start == 0);
    }
    THEN("The member variable 'end' should be 0") {
      REQUIRE(schedule.end == 0);
    }
    THEN("The member variable 'duration' should be 0") {
      REQUIRE(schedule.duration == 0);
    }
    THEN("The member variable 'type' should be 0") {
      REQUIRE(schedule.type == 0);
    }
    THEN("The member variable 'mask' should be 0") {
      REQUIRE(schedule.mask == 0);
    }
  }
}

