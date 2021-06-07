#include "pch.h"
#include "CppUnitTest.h"
#include "BasicServer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestServer
{
	TEST_CLASS(UnitTestServer)
	{
	public:
		
		TEST_METHOD(TestturnOffAllLight)
		{
			BasicServer s1;
			s1.beleuchtungInit();
			s1.turnOffAllLight();
			for (int x = 0; x < std::size(s1.beleuchtungs_zustaende_); x++)
			{
				Assert::IsFalse(s1.beleuchtungs_zustaende_[x]);
			}
			
		}

		TEST_METHOD(TestgetLightInfo)
		{
			BasicServer s1;
			s1.beleuchtungInit();
			s1.getLightInfo();

			for (int x = 0; x < std::size(s1.beleuchtungs_zustaende_); x++)
			{
				Assert::AreEqual(s1.beleuchtungs_zustaende_[x],s1.server_beleuchtung_[x]);
			}

		}
		
	};
}
