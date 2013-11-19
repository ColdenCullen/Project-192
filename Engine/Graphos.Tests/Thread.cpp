#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "GraphosThread.h"
#include "ThreadManager.h"

using namespace std;
using namespace Graphos::Utility;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphosTests
{		
	TEST_CLASS(ThreadTest)
	{
	public:
		TEST_METHOD(Thread)
		{
			auto test = new Graphos::Utility::Thread();

			gBool didStuff = false;

			auto func = [&]() -> void
			{
				for( gUInt ii = 0; ii < 10000; ++ii ) ;
				didStuff = true;
			};

			test->Invoke( func );

			Assert::IsTrue( test->IsBusy(), L"Test finishes too quickly." );

			while( test->IsBusy() ) ;

			Assert::IsTrue( didStuff, L"didStuff not modified." );
		}
	};
}