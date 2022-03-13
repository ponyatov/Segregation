#pragma once

Player_Data_Structure Players_Data[64];

void Get_Priorities()
{
	static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

	__int32 Maximum_Clients = Global_Variables->Maximum_Clients;

	if (Maximum_Clients != 0)
	{
		__int32 Entity_Number = 1;

		Traverse_Entity_List_Label:
		{
			using Get_Client_Name_Type = void(__thiscall*)(void* Engine, __int32 Number, char Name[132]);

			char Name[132];

			Get_Client_Name_Type(537018208)((void*)540435380, Entity_Number, Name);

			if (Name[0] != 0)
			{
				wprintf(L"[ ? ] \"%hs\" %i %i\n", Name, Entity_Number, Players_Data[Entity_Number - 1].Priority);
			}

			if (Entity_Number != Maximum_Clients)
			{
				Entity_Number += 1;

				goto Traverse_Entity_List_Label;
			}
		}
	}
}

void Set_Priority(Interface_Structure* Console_Variable)
{
	__int32 Player_Number = atoi(Console_Variable->String);

	__int32 Priority;

	if (Player_Number < 10)
	{
		Priority = atoi((char*)((unsigned __int32)Console_Variable->String + 2));
	}
	else
	{
		Priority = atoi((char*)((unsigned __int32)Console_Variable->String + 3));
	}

	Players_Data[Player_Number - 1].Priority = Priority;
}