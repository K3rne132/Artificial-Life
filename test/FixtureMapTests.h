#pragma once
#include "pch.h"
#include <Map.h>

class FixtureMapTests : public testing::Test {
protected:
	int FixtureMapSize = 30;
	Map SampleMap;
	void SetUp() override {
		for (int i = 0; i < FixtureMapSize; i++) {
			auto obj = std::unique_ptr<MapObject>(new MapObject(i, i));
			SampleMap.addObject(obj);
		}
	}

	void TearDown() override {}
};