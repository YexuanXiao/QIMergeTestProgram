#pragma once
#include "TestWinRT.TestPerf.g.h"

namespace winrt::TestWinRT::implementation
{
	struct TestPerf : TestPerfT<TestPerf>
	{
		TestPerf() = default;

		void DoDirect();
		void DoQI();
	};
}
