#include "pch.h"
#include "FixtureMapTests.h"


TEST(MapTests, GetObjTest) {
	auto new_obj = std::unique_ptr<MapObject>(new MapObject(1, 100));
	auto ptr = new_obj.get();
	Map map;
	map.addObject(new_obj);
	EXPECT_EQ(ptr, &map[0]);
	ASSERT_THROW(map[1000], std::out_of_range);
	ASSERT_NO_THROW(map[0], std::out_of_range);
}


TEST_F(FixtureMapTests, AddSizeMapTest) {
	size_t current_map_size = SampleMap.getSize();
	EXPECT_EQ(FixtureMapSize, current_map_size);

	auto new_obj = std::unique_ptr<MapObject>(new MapObject(1, 100));
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
