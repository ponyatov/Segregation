#pragma once

__int8 __thiscall Redirected_Is_Flag_Set(void* Interface, __int32 Flag)
{
	Flag &= ~8192;

	return (Flag & *(__int32*)((unsigned __int32)Interface + 20)) != 0;
}