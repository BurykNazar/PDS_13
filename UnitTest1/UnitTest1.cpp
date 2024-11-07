#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab13\Source.cpp"
#include <fstream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestColorGraph)
		{
			N = 4;
			adjList.resize(N);
			addEdge(0, 1);
			addEdge(1, 2);
			addEdge(2, 3);
			addEdge(3, 0);

			vector<int> colors = colorGraph();

			Assert::AreEqual(colors[0], 0);
			Assert::AreEqual(colors[1], 1);
			Assert::AreEqual(colors[2], 0);
			Assert::AreEqual(colors[3], 1);
		}
	};
}
