#include "Event.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

using namespace std;
using namespace Graphos::Utility;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphosTests
{		
	TEST_CLASS(EventTest)
	{
	public:
		TEST_METHOD(Void)
		{
			Event<void, void> test;

			bool test1 = false;
			bool test2 = false;

			test += [&](){ test1 = true; };
			test();
			Assert::IsTrue( test1, L"Function did not execute." );

			test += [&]()
			{
				test2 = true;
				test1 = false;
			};

			test();
			Assert::IsFalse( test1, L"Function2 did not execute." );
			Assert::IsTrue( test2, L"Function2 did not execute." );
		}

		TEST_METHOD(Param)
		{
			Event<void, bool> testEvent;

			bool testBool = false;

			testEvent += [&]( bool newVal )
			{
				testBool = newVal;
			};

			testEvent( true );

			Assert::IsTrue( testBool, L"Function did not execute." );
		}
	};
}