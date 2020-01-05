#include "pch.h"
#include "../PEA_Projekt/AdjacencyMatrix.h"
#include "../PEA_Projekt/Path.h"

#include <string>
#include <windows.h>
#include "../PEA_Projekt/TS_Genetic.h"

using namespace std;

TEST(TestAdjacencyMatrix, MatrixCanBeLoaded) {
	AdjacencyMatrix* am = new AdjacencyMatrix(".\\Data\\SMALL\\data11.txt");

	EXPECT_TRUE(am->GetSize() > 0);
}

Path generateCorrectPath(AdjacencyMatrix* am) {
	Path path = Path(am);
	path.InsertEdge(PathEdge(0, 1));
	path.InsertEdge(PathEdge(1, 3));
	path.InsertEdge(PathEdge(3, 5));
	path.InsertEdge(PathEdge(5, 0));
	return path;
}

TEST(TestPath, ValidateValidates) {
	AdjacencyMatrix* am = new AdjacencyMatrix(".\\Data\\SMALL\\data11.txt");

	{
		Path p = generateCorrectPath(am);
		EXPECT_TRUE(p.Validate());
	}

	// Sprawdü czy wÍz≥y nie powtarzajπ siÍ
	{
		Path p = generateCorrectPath(am);
		p.InsertEdge(PathEdge(5, 0));
		EXPECT_FALSE(p.Validate());
	}

	// Sprawdü poprawnoúÊ startingPoint
	{
		//Path p = generateCorrectPath(am);
		//p.SetStartingPoint(4);
		//EXPECT_ANY_THROW(p.Validate());
	}

	// Sprawdü czy wartoúci from odpowiadajπ wartoúciom to
	{
		Path p = Path(am);
		p.InsertEdge(PathEdge(0, 1));
		p.InsertEdge(PathEdge(1, 3));
		p.InsertEdge(PathEdge(5, 4));
		p.InsertEdge(PathEdge(4, 0));
		EXPECT_FALSE(p.Validate());
	}

	// Sprawdü czy ostatni element to startingPoint
	{
		Path path = Path(am);
		path.InsertEdge(PathEdge(0, 1));
		path.InsertEdge(PathEdge(1, 3));
		path.InsertEdge(PathEdge(3, 5));
		EXPECT_FALSE(path.Validate());
	}
}

TEST(TestGenetic, OX_Crossing) {
	AdjacencyMatrix* am = new AdjacencyMatrix(".\\Data\\SMALL\\data11.txt");

	Path path1 = Path(am);
	path1.InsertEdge(PathEdge(1, 2));
	path1.InsertEdge(PathEdge(2, 3));
	path1.InsertEdge(PathEdge(3, 4));
	path1.InsertEdge(PathEdge(4, 5));
	path1.InsertEdge(PathEdge(5, 6));
	path1.InsertEdge(PathEdge(6, 7));
	path1.InsertEdge(PathEdge(7, 8));
	path1.InsertEdge(PathEdge(8, 9));
	path1.InsertEdge(PathEdge(9, 1));

	Path path2 = Path(am);
	path2.InsertEdge(PathEdge(5, 3));
	path2.InsertEdge(PathEdge(3, 6));
	path2.InsertEdge(PathEdge(6, 7));
	path2.InsertEdge(PathEdge(7, 8));
	path2.InsertEdge(PathEdge(8, 1));
	path2.InsertEdge(PathEdge(1, 2));
	path2.InsertEdge(PathEdge(2, 9));
	path2.InsertEdge(PathEdge(9, 4));
	path2.InsertEdge(PathEdge(4, 5));

	//TS_Genetic gentic = TS_Genetic(am, 2);

	EXPECT_NO_THROW(TS_Genetic::crossPaths_OX(&path1, &path2));
}