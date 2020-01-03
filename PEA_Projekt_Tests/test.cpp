#include "pch.h"
#include "../PEA_Projekt/AdjacencyMatrix.h"
#include "../PEA_Projekt/Path.h"

#include <string>
#include <windows.h>

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
		EXPECT_ANY_THROW(p.Validate());
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
		EXPECT_ANY_THROW(p.Validate());
	}

	// Sprawdü czy ostatni element to startingPoint
	{
		Path path = Path(am);
		path.InsertEdge(PathEdge(0, 1));
		path.InsertEdge(PathEdge(1, 3));
		path.InsertEdge(PathEdge(3, 5));
		EXPECT_ANY_THROW(path.Validate());
	}
}
