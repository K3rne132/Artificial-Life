// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "Plant.h"
#include "Herbivore.h"
#include "Carnivore.h"
#include "pch.h"
#include "FixtureMapTests.h"

TEST(MapTests, GetObjTest) {
	auto new_obj = std::unique_ptr<Drawable>(new MapObjectDummy(1, 100));
	auto ptr = new_obj.get();
	Map map;
	map.addObject(new_obj);
	EXPECT_EQ(ptr, &map[0]);
	ASSERT_THROW(map[1000], std::out_of_range);
	ASSERT_NO_THROW(map[0]);
}


TEST_F(FixtureMapTests, AddSizeMapTest) {
	size_t current_map_size = SampleMap.getSize();
	EXPECT_EQ(FixtureMapSize, current_map_size);

	auto new_obj = std::unique_ptr<Drawable>(new MapObjectDummy(1, 100));
	SampleMap.addObject(new_obj);
	current_map_size = SampleMap.getSize();
	EXPECT_EQ(++FixtureMapSize, current_map_size);
}


TEST_F(FixtureMapTests, RemoveObjTest) {
	auto &obj_to_delete1 = SampleMap[0];
	auto &obj_to_delete2 = SampleMap[15];
	int expected_map_size = FixtureMapSize - 2;

	EXPECT_EQ(&obj_to_delete1, &SampleMap[0]);
	EXPECT_TRUE(SampleMap.removeObject(obj_to_delete1));
	EXPECT_TRUE(SampleMap.removeObject(obj_to_delete2));
	int current_map_size = SampleMap.getSize();

	EXPECT_EQ(expected_map_size, current_map_size);
}

TEST(MapTests, ReadFromFileJsonTest) {
	std::string existing_file = "testowy.json";
	std::string not_existing_file = "imnothere.json";
	Map map;
	ASSERT_TRUE(map.readFromFile(existing_file));
	ASSERT_FALSE(map.readFromFile(not_existing_file));
	ASSERT_TRUE(map.writeToFile("generated3.json"));
}

TEST(MapTests, WriteToFileJsonTest) {
	std::string output_file = "json_output.json";
	auto new_animal = std::unique_ptr<Drawable>(new Carnivore(FPoint(1, 1)));
	auto new_animal2 = std::unique_ptr<Drawable>(new Herbivore(FPoint(3 ,200)));
	auto new_animal3 = std::unique_ptr<Drawable>(new Herbivore(FPoint(3, 200)));
	auto new_plant = std::unique_ptr<Drawable>(new Plant());
	Map map;
	map.addObject(new_animal);
	map.addObject(new_animal2);
	map.addObject(new_animal3);
	map.addObject(new_plant);
	ASSERT_TRUE(map.writeToFile(output_file));
}

TEST(MapTests, GeneratedMapTest) {
	std::string filename = "generated2.json";
	Map map;
	map.generate(20, 20, 20, 1920, 1080);
	map.writeToFile(filename);
	ASSERT_TRUE(map.generate(20, 20, 20, 1920, 1080));
}
