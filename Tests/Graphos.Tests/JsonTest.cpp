#include "JsonController.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

using namespace std;
using namespace Graphos::Utility;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphosTests
{		
	TEST_CLASS(JsonTest)
	{
	public:
		TEST_METHOD(GetSet)
		{
			JsonObject test;

			test.Set( "Test1", "Result" );
			Assert::AreEqual( "Result", test.Get<string>( "Test1" ).c_str() );

			test.Set( "Test2.Test3", "Set1" );
			Assert::AreEqual( "Set1", test.Get<string>( "Test2.Test3" ).c_str() );

			test.Set( "Test2.Test3", "Set2" );
			Assert::AreEqual( "Set2", test.Get<string>( "Test2.Test3" ).c_str() );

			test.Set( "Test2.Test4", 3 );
			Assert::AreEqual( 3, test.Get<int>( "Test2.Test4" ) );

			test.Set( "Test2.Test5.Test6", "Set4" );
			Assert::AreEqual( "Set4", test.Get<string>( "Test2.Test5.Test6" ).c_str() );
		}

		TEST_METHOD(TryGet)
		{
			JsonObject test;
			JsonObject testRef;

			test.Set( "Test1", "Set1" );
			Assert::IsTrue( test.TryGet( "Test1", testRef ), L"Test1 not found." );

			Assert::IsFalse( test.TryGet( "Test2", testRef ), L"Test2 reported found." );
		}
	};
}