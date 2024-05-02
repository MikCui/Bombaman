#include "tools.h"

namespace TOOLS
{
	bool SUCCESS(RESULT rResult)
	{
		return  rResult==OK?true:false;
	}

	bool FAIL(RESULT rResult)
	{
		return  rResult!=OK?true:false;
	}
}
