#pragma once

void Redirected_Send_Move()
{
	Move_Message_Structure Move_Message;

	unsigned __int8 Data[4000];

	Move_Message.Construct(Data);

	__int32 Choked_Commands = *(__int32*)540627872;

	__int32 Next_Command_Number = *(__int32*)540627868 + Choked_Commands + 1;

	__int32 Commands_Queue = std::clamp(Choked_Commands + 1, 0, 15);

	__int32 Extra_Commands_Queue = Choked_Commands + 1 - Commands_Queue;

	__int32 Backup_Commands = std::clamp(Extra_Commands_Queue, 2, 7);

	*(__int32*)((unsigned __int32)&Move_Message + 16) = Backup_Commands;

	*(__int32*)((unsigned __int32)&Move_Message + 20) = Commands_Queue;

	__int32 To = Next_Command_Number - (Commands_Queue + Backup_Commands) + 1;

	__int8 Is_New_Command;

	__int8 Should_Send_Packet = 1;

	__int32 From = -1;

	Write_Command_Label:
	{
		if (Should_Send_Packet == 1)
		{
			if (To < Next_Command_Number - Commands_Queue + 1)
			{
				Is_New_Command = 0;
			}
			else
			{
				Is_New_Command = 1;
			}

			using Write_Command_Type = __int8(__thiscall**)(void* Client, void* Data, __int32 From, __int32 To, __int8 New);

			static void* Client_Location = *(void**)540494868;

			__int8 Write_Command_Return_Value = (*Write_Command_Type(*(unsigned __int32*)Client_Location + 80))(Client_Location, (void*)((unsigned __int32)&Move_Message + 52), From, To, Is_New_Command);

			Should_Send_Packet = Write_Command_Return_Value;
		}

		From = To;

		To += 1;

		if (To <= Next_Command_Number)
		{
			goto Write_Command_Label;
		}
	}

	if (Should_Send_Packet == 1)
	{
		void* Network_Channel = *(void**)540608912;

		if (Extra_Commands_Queue > 0)
		{
			*(__int32*)((unsigned __int32)Network_Channel + 28) -= Extra_Commands_Queue;
		}

		using Send_Network_Message_Type = void(__thiscall**)(void* Network_Channel, void* Message, __int8 Unknown_Parameter);

		(*Send_Network_Message_Type(*(unsigned __int32*)Network_Channel + 144))(Network_Channel, &Move_Message, 0);
	}
}