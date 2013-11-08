#include "JsonController.h"
#include "v8.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

using namespace std;
using namespace v8;
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

		TEST_METHOD(JsonToV8)
		{
			HandleScope scope;
			JsonObject test;
			Handle<Value> testRes;

			test.Set( "TestStr", "Set1" );
			testRes = test.Get<Handle<Value>>( "TestStr" );
			Assert::AreEqual(
				test.Get<string>( "TestStr" ).c_str(),
				*String::AsciiValue( testRes->ToString() ) );

			test.Set( "TestInt", 20 );
			testRes = test.Get<Handle<Value>>( "TestInt" );
			Assert::AreEqual(
				test.Get<int>( "TestInt" ),
				testRes->Int32Value() );

			test.Set( "TestObj.Test2", 22 );
			testRes = test.Get<Handle<Value>>( "TestObj" );
			Assert::AreEqual(
				test.Get<int>( "TestObj.Test2" ),
				testRes->ToObject()->Get( String::New( "Test2" ) )->Int32Value() );
		}

		TEST_METHOD(GetChildren)
		{
			JsonObject test;

			test.Set( "Test1", 1 );
			test.Set( "Test2", 2 );

			auto children = test.GetChildren();

			Assert::AreEqual(
				test.Get<int>( "Test1" ),
				children[ 0 ].Get<int>( "" ) );

			Assert::AreEqual(
				test.Get<int>( "Test2" ),
				children[ 1 ].Get<int>( "" ) );
		}
	};
}