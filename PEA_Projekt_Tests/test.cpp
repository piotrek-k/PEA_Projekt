#include "pch.h"
#include "../PEA_Projekt/Path.h"
#include "../PEA_Projekt/PathEdge.h"
#include "../PEA_Projekt/AdjacencyMatrix.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(test_Path, PathCanBeLoaded) {
	AdjacencyMatrix* am = new AdjacencyMatrix("./dane.txt");
	Path* path = new Path(am);

	EXPECT_TRUE(am->GetSize() > 0);
}

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
