#include "pch.h"
#include "../PEA_Projekt/Path.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

//TEST(test_Path, ContainsValueReturnsTrueResult) {
//	Path* path = new Path();
//	path->InsertEdge(PathEdge(0, 5, 10));
//	path->InsertEdge(PathEdge(5, 3, 8));
//	path->InsertEdge(PathEdge(3, 4, 6));
//
//	EXPECT_TRUE(path->ContainsValue(5, 3));
//	EXPECT_TRUE(path->ContainsValue(3, 4));
//	EXPECT_FALSE(path->ContainsValue(3, 5));
//}
//
//TEST(test_Path, ValueCanBeConnectedToEndWorksPropely) {
//	Path* path = new Path();
//	path->InsertEdge(PathEdge(0, 5, 10));
//	path->InsertEdge(PathEdge(5, 3, 8));
//	path->InsertEdge(PathEdge(3, 4, 6));
//
//	EXPECT_TRUE(path->ValueCanBeConnectedToEnd(2));
//	EXPECT_TRUE(path->ValueCanBeConnectedToEnd(0));
//	EXPECT_FALSE(path->ValueCanBeConnectedToEnd(5));
//	EXPECT_FALSE(path->ValueCanBeConnectedToEnd(4));
//}
//
