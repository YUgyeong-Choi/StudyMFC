#pragma once

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
unsigned long Safe_Release(T& Temp)
{
	unsigned long dwRefCnt = 0;

	if (Temp)
	{
		dwRefCnt = Temp->Release();
		Temp = nullptr;
	}

	return dwRefCnt;
}
