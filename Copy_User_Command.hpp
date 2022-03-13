#pragma once

float Arc_Tangent_2(float X, float Y)
{
	asm("fpatan" : "+t"(X) : "u"(Y) : "st(1)");

	return X;
}

float Square_Root(float X)
{
	asm("fsqrt" : "+t"(X));

	return X;
}

void Angle_Vectors(float* Angles, float* Forward, float* Right, float* Up)
{
	using Angle_Vectors_Type = void(__cdecl*)(float* Angles, float* Forward, float* Right, float* Up);

	Angle_Vectors_Type(606384752)(Angles, Forward, Right, Up);
}

void Vector_Normalize(float* Vector)
{
	using Vector_Normalize_Type = float(__thiscall*)(float* Vector);

	Vector_Normalize_Type(606378096)(Vector);
}

void* Original_Copy_User_Command_Caller_Location;

void __thiscall Redirected_Copy_User_Command(void* Unknown_Parameter, User_Command_Structure* User_Command)
{
	Redirected_Run_Prediction();

	Shot_Tick_Number = -1;

	void* Local_Player = *(void**)607867332;

	float Local_Player_Previous_Origin[3] =
	{
		*(float*)((unsigned __int32)Local_Player + 668),

		*(float*)((unsigned __int32)Local_Player + 672),

		*(float*)((unsigned __int32)Local_Player + 676),
	};

	using Run_Command_Type = void(__thiscall*)(void* Prediction, void* Local_Player, User_Command_Structure* User_Command, void* Move_Helper);

	static void* Prediction = *(void**)540494880;

	Run_Command_Type(605207600)(Prediction, Local_Player, User_Command, (void*)607735532);

	*(__int32*)((unsigned __int32)Local_Player + 3592) -= 1;

	float Move_Angles[3] =
	{
		User_Command->View_Angles[0],

		User_Command->View_Angles[1],

		0
	};

	static float Previous_Move_Angle_Y = Move_Angles[1];

	if ((User_Command->Buttons_State & 2) == 2)
	{
		User_Command->Move[0] = 0;

		if (*(__int32*)((unsigned __int32)Local_Player + 456) != -1)
		{
			User_Command->Buttons_State &= ~2;
		}

		float Difference = __builtin_remainderf(User_Command->View_Angles[1] - Previous_Move_Angle_Y, 360);

		Previous_Move_Angle_Y = User_Command->View_Angles[1];

		float* Velocity = (float*)((unsigned __int32)Local_Player + 236);

		if (Absolute(Difference) < Arc_Tangent_2(Square_Root(__builtin_powf(Velocity[0], 2) + __builtin_powf(Velocity[1], 2)), 30) * 180 / 3.1415927f)
		{
			float Strafe_Angle = __builtin_remainderf(User_Command->View_Angles[1] - Arc_Tangent_2(Velocity[0], Velocity[1]) * 180 / 3.1415927f, 360);

			if (__builtin_signbitf(Strafe_Angle) == 0)
			{
				User_Command->Move[1] = -400;
			}
			else
			{
				User_Command->Move[1] = 400;
			}

			Move_Angles[1] -= Strafe_Angle;
		}
		else
		{
			if (__builtin_signbitf(Difference) == 0)
			{
				User_Command->Move[1] = -400;
			}
			else
			{
				User_Command->Move[1] = 400;
			}
		}
	}
	else
	{
		Previous_Move_Angle_Y = User_Command->View_Angles[1];
	}

	__int32 Choked_Commands_Count = *(__int32*)540627872;

	__int8 Send_Packet;

	__int32 Predicted_Choked_Commands_Count = Choked_Commands_Count + 1;

	__int8 Predicted_Send_Packet;

	float* Local_Player_Origin = (float*)((unsigned __int32)Local_Player + 668);

	if (Choked_Commands_Count < Console_Variable_Minimum_Choked_Commands.Integer)
	{
		Send_Packet = 0;

		if (Predicted_Choked_Commands_Count == Console_Variable_Minimum_Choked_Commands.Integer)
		{
			if (Predicted_Choked_Commands_Count < Console_Variable_Maximum_Choked_Commands.Integer)
			{
				goto Predict_Adaptive_Send_Packet_Label;
			}
			else
			{
				Predicted_Send_Packet = 1;
			}
		}
		else
		{
			Predicted_Send_Packet = -1;
		}
	}
	else
	{
		static float Previous_Networked_Origin[3];

		if (Choked_Commands_Count < Console_Variable_Maximum_Choked_Commands.Integer)
		{
			float Difference[3] =
			{
				Previous_Networked_Origin[0] - Local_Player_Previous_Origin[0],

				Previous_Networked_Origin[1] - Local_Player_Previous_Origin[1],

				Previous_Networked_Origin[2] - Local_Player_Previous_Origin[2]
			};

			if (__builtin_powf(Difference[0], 2) + __builtin_powf(Difference[1], 2) + __builtin_powf(Difference[2], 2) <= 4096)
			{
				Send_Packet = 0;
			}
			else
			{
				Previous_Networked_Origin[0] = *(float*)((unsigned __int32)Local_Player + 668);

				Previous_Networked_Origin[1] = *(float*)((unsigned __int32)Local_Player + 672);

				Previous_Networked_Origin[2] = *(float*)((unsigned __int32)Local_Player + 676);

				Send_Packet = 1;
			}

			Predict_Adaptive_Send_Packet_Label:
			{
				if (Predicted_Choked_Commands_Count == Console_Variable_Maximum_Choked_Commands.Integer)
				{
					Predicted_Send_Packet = 1;
				}
				else
				{
					Difference[0] = Previous_Networked_Origin[0] - Local_Player_Origin[0];

					Difference[1] = Previous_Networked_Origin[1] - Local_Player_Origin[1];

					Difference[2] = Previous_Networked_Origin[2] - Local_Player_Origin[2];

					if (__builtin_powf(Difference[0], 2) + __builtin_powf(Difference[1], 2) + __builtin_powf(Difference[2], 2) <= 4096)
					{
						Predicted_Send_Packet = -1;
					}
					else
					{
						Predicted_Send_Packet = 1;
					}
				}
			}
		}
		else
		{
			Previous_Networked_Origin[0] = *(float*)((unsigned __int32)Local_Player + 668);

			Previous_Networked_Origin[1] = *(float*)((unsigned __int32)Local_Player + 672);

			Previous_Networked_Origin[2] = *(float*)((unsigned __int32)Local_Player + 676);

			Send_Packet = 1;

			Predicted_Send_Packet = -1;
		}
	}

	__int32 Entity_Number = 1;

	__int32 Team_Number = *(__int32*)((unsigned __int32)Local_Player + 144);

	struct Target_Structure
	{
		__int8 Priority;

		float Distance;

		void* Target;
	};

	static std::vector<Target_Structure> Sorted_Target_List;

	Sorted_Target_List.clear();

	static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

	__int32 Maximum_Clients = Global_Variables->Maximum_Clients;

	Traverse_Entity_List_Label:
	{
		Player_Data_Structure* Player_Data = &Players_Data[Entity_Number - 1];

		if (Player_Data->Priority != -1)
		{
			void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));

			if (Entity != nullptr)
			{
				if (*(__int8*)((unsigned __int32)Entity + 135) == 0)
				{
					if (*(__int32*)((unsigned __int32)Entity + 144) != Team_Number)
					{
						if (*(__int8*)((unsigned __int32)Entity + 320) == 0)
						{
							Target_Structure Target;

							Target.Priority = Player_Data->Priority;

							float* Entity_Origin = (float*)((unsigned __int32)Entity + 668);

							Target.Distance = Square_Root(__builtin_powf(Local_Player_Origin[0] - Entity_Origin[0], 2) + __builtin_powf(Local_Player_Origin[1] - Entity_Origin[1], 2) + __builtin_powf(Local_Player_Origin[2] - Entity_Origin[2], 2));

							Target.Target = Entity;

							Sorted_Target_List.push_back(Target);
						}
					}
				}
			}
		}
		
		if (Entity_Number != Maximum_Clients)
		{
			Entity_Number += 1;

			goto Traverse_Entity_List_Label;
		}
	}

	auto Target_List_Sort = [](Target_Structure X, Target_Structure Y) -> __int8
	{
		if (X.Priority > Y.Priority)
		{
			return 1;
		}

		return X.Distance < Y.Distance;
	};
	
	std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort);

	__int8 In_Attack = 0;

	if (Global_Variables->Current_Time - Shot_Time > 0.2f)
	{
		if ((User_Command->Buttons_State & 2048) == 0)
		{
			if (Send_Packet == 0)
			{
				if (Predicted_Send_Packet == 1)
				{
					if (*(float*)((unsigned __int32)Local_Player + 2544) <= Global_Variables->Current_Time)
					{
						unsigned __int32 Weapon_Index = *(unsigned __int32*)((unsigned __int32)Local_Player + 2872);

						void* Weapon = *(void**)((unsigned __int32)607973860 + (((Weapon_Index & 4095) - 4097) << 4));

						if (Weapon != nullptr)
						{
							if (*(__int8*)((unsigned __int32)Weapon + 1732) == 0)
							{
								if (*(__int32*)((unsigned __int32)Weapon + 1788) > 0)
								{
									if (*(float*)((unsigned __int32)Weapon + 1720) <= Global_Variables->Current_Time)
									{
										size_t Target_Number = 0;

										void* Optimal_Target;

										using Eye_Position = void(__thiscall*)(void* Player, float* Eye_Position);

										float Local_Player_Eye_Position[3];

										Eye_Position(604058320)(Local_Player, Local_Player_Eye_Position);

										__int32 Target_Tick_Number;

										using Get_Latency_Type = float(__thiscall*)(void* Network_Channel, __int32 Flow_Type);

										void* Network_Channel = *(void**)540608912;

										float Total_Latency = Get_Latency_Type(537919008)(Network_Channel, 0) + Get_Latency_Type(537919008)(Network_Channel, 1);

										float Interpolation_Ratio = *(float*)607906336;

										float Minimum_Interpolation_Ratio = *(float*)542242312;

										float Maximum_Interpolation_Ratio = *(float*)542242072;

										if (Interpolation_Ratio < Minimum_Interpolation_Ratio)
										{
											Interpolation_Ratio = Minimum_Interpolation_Ratio;
										}
										else
										{
											if (Interpolation_Ratio > Maximum_Interpolation_Ratio)
											{
												Interpolation_Ratio = Maximum_Interpolation_Ratio;
											}
										}

										__int32 Update_Rate = *(__int32*)540495212;

										__int32 Maximum_Update_Rate = *(__int32*)542221412;

										__int32 Minimum_Update_Rate = *(__int32*)542221268;

										if (Update_Rate < Minimum_Update_Rate)
										{
											Update_Rate = Minimum_Update_Rate;
										}
										else
										{
											if (Update_Rate > Maximum_Update_Rate)
											{
												Update_Rate = Maximum_Update_Rate;
											}
										}

										float Interpolation_Time = Interpolation_Ratio / Update_Rate;

										float Interpolation = *(float*)541928632;

										if (Interpolation_Time < Interpolation)
										{
											Interpolation_Time = Interpolation;
										}

										float Corrected_Interpolation_Time = std::clamp(Total_Latency + Interpolation_Time, 0.f, 1.f);

										float Aim_Angles[2];

										Traverse_Sorted_Target_List_Label:
										{
											if (Target_Number == Sorted_Target_List.size())
											{
												Optimal_Target = nullptr;
											}
											else
											{
												using Setup_Bones_Type = __int8(__thiscall*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time);

												Optimal_Target = Sorted_Target_List.at(Target_Number).Target;

												float Bones[128][3][4];

												if (Setup_Bones_Type(604209888)((void*)((unsigned __int32)Optimal_Target + 4), Bones, 128, 524032, Global_Variables->Current_Time) == 1)
												{
													void* Model = *(void**)((unsigned __int32)Optimal_Target + 92);

													if (Model != nullptr)
													{
														using Get_Studio_Model_Type = void*(__thiscall*)(void* Model_Cache, void* Model);

														static void* Get_Studio_Model_Location = (void*)((unsigned __int32)GetModuleHandleW(L"datacache.dll") + 46416);

														static void* Model_Cache = (void*)((unsigned __int32)GetModuleHandleW(L"datacache.dll") + 125464);

														void* Studio_Model = Get_Studio_Model_Type((unsigned __int32)Get_Studio_Model_Location)(Model_Cache, *(void**)((unsigned __int32)Model + 144));

														if (Studio_Model != nullptr)
														{
															auto Trace_Ray = [&](float* End) -> __int8
															{
																struct Ray_Structure
																{
																	__int8 Additional_Bytes[50];
																};

																struct Trace_Structure
																{
																	__int8 Additional_Bytes_1[76];

																	void* Entity;

																	__int8 Additional_Bytes_2[4];
																};

																using Trace_Ray_Type = void(__cdecl*)(Ray_Structure* Ray, __int32 Mask, void* Skip, __int32 Group, Trace_Structure* Trace);

																using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End);

																Ray_Structure Ray;

																Initialize_Ray_Type(537380224)(&Ray, Local_Player_Eye_Position, End);

																Trace_Structure Trace;

																Trace_Ray_Type(604317152)(&Ray, 1174421515, Local_Player, 0, &Trace);

																if (Trace.Entity == nullptr)
																{
																	return 1;
																}

																if (Trace.Entity == Optimal_Target)
																{
																	return 1;
																}

																return 0;
															};

															void* Hitbox_Set = (void*)((unsigned __int32)Studio_Model + *(__int32*)((unsigned __int32)Studio_Model + 176));

															float* Bounding_Box_Minimum = (float*)((unsigned __int32)Hitbox_Set + 836);

															float* Bounding_Box_Maximum = (float*)((unsigned __int32)Hitbox_Set + 848);

															float Hitbox_Minimum[3] =
															{
																Bounding_Box_Minimum[0] * Bones[14][0][0] + Bounding_Box_Minimum[1] * Bones[14][0][1] + Bounding_Box_Minimum[2] * Bones[14][0][2] + Bones[14][0][3],

																Bounding_Box_Minimum[0] * Bones[14][1][0] + Bounding_Box_Minimum[1] * Bones[14][1][1] + Bounding_Box_Minimum[2] * Bones[14][1][2] + Bones[14][1][3],

																Bounding_Box_Minimum[0] * Bones[14][2][0] + Bounding_Box_Minimum[1] * Bones[14][2][1] + Bounding_Box_Minimum[2] * Bones[14][2][2] + Bones[14][2][3]
															};

															float Hitbox_Maximum[3] =
															{
																Bounding_Box_Maximum[0] * Bones[14][0][0] + Bounding_Box_Maximum[1] * Bones[14][0][1] + Bounding_Box_Maximum[2] * Bones[14][0][2] + Bones[14][0][3],

																Bounding_Box_Maximum[0] * Bones[14][1][0] + Bounding_Box_Maximum[1] * Bones[14][1][1] + Bounding_Box_Maximum[2] * Bones[14][1][2] + Bones[14][1][3],

																Bounding_Box_Maximum[0] * Bones[14][2][0] + Bounding_Box_Maximum[1] * Bones[14][2][1] + Bounding_Box_Maximum[2] * Bones[14][2][2] + Bones[14][2][3]
															};

															float Optimal_Target_Origin[3] =
															{
																(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2,

																(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2,

																Hitbox_Maximum[2] + (Hitbox_Maximum[2] - Hitbox_Minimum[2]) * (Console_Variable_Aim_Height.Floating_Point - 1)
															};

															if (Trace_Ray(Optimal_Target_Origin) == 1)
															{
																Target_Tick_Number = (*(float*)((unsigned __int32)Optimal_Target + 104) + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f;

																__int32 Tick_Number_Difference = Global_Variables->Tick_Number + 1 + Total_Latency / Global_Variables->Interval_Per_Tick + 0.5f - Target_Tick_Number;

																if (Tick_Number_Difference * -1 <= 7)
																{
																	if (Absolute(Corrected_Interpolation_Time - Tick_Number_Difference * Global_Variables->Interval_Per_Tick) <= 0.2f)
																	{
																		float Origin_Difference[3] =
																		{
																			Optimal_Target_Origin[0] - Local_Player_Eye_Position[0],

																			Optimal_Target_Origin[1] - Local_Player_Eye_Position[1],

																			Optimal_Target_Origin[2] - Local_Player_Eye_Position[2],
																		};

																		Aim_Angles[0] = Arc_Tangent_2(Square_Root(__builtin_powf(Origin_Difference[0], 2) + __builtin_powf(Origin_Difference[1], 2)), -Origin_Difference[2]) * 180 / 3.1415927f;

																		Aim_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f;

																		User_Command->Buttons_State |= 1;

																		goto Found_Optimal_Target_Label;
																	}
																}
															}
														}
													}
												}

												Target_Number += 1;

												goto Traverse_Sorted_Target_List_Label;

												Found_Optimal_Target_Label:
												{

												}
											}
										}

										if ((User_Command->Buttons_State & 1) == 1)
										{
											Shot_Time = Global_Variables->Current_Time;

											Shot_Tick_Number = *(__int32*)((unsigned __int32)Local_Player + 3592);

											In_Attack = 1;
											
											if (Optimal_Target != nullptr)
											{
												User_Command->Tick_Number = Target_Tick_Number;

												User_Command->View_Angles[0] = Aim_Angles[0];

												User_Command->View_Angles[1] = Aim_Angles[1];

												Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Optimal_Target + 80) - 1];

												if (Console_Variable_Bruteforce_Memory.Integer == 0)
												{
													Bruteforce_Label:
													{
														if (Player_Data->Tolerance == 0)
														{
															Player_Data->Shots_Fired = (Player_Data->Shots_Fired + 1) % (sizeof(Bruteforce_Angles) / sizeof(float));

															Player_Data->Tolerance = Console_Variable_Bruteforce_Tolerance.Integer;
														}
														else
														{
															Player_Data->Tolerance -= 1;
														}
													}
												}
												else
												{
													if (Player_Data->Memorized == 0)
													{
														goto Bruteforce_Label;
													}

													Player_Data->Memorized -= 1;
												}
											}

											float Forward[3];

											float Right[3];

											float Up[3];

											Angle_Vectors(User_Command->View_Angles, Forward, Right, Up);

											constexpr __int32 Random_Seed = 32;

											User_Command->Random_Seed = Random_Seed;

											User_Command->Command_Number = -2076434770;

											using Random_Seed_Type = void(__cdecl*)(__int32 Seed);

											static void* Random_Seed_Location = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11856);

											Random_Seed_Type((unsigned __int32)Random_Seed_Location)((Random_Seed & 255) + 1);

											using Random_Float_Type = float(__cdecl*)(float Min, float Max);

											static void* Random_Float_Location = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11872);

											float Random_X = Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f) + Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f);

											float Random_Y = Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f) + Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f);

											using Primary_Attack_Type = void(__thiscall**)(void* Weapon);

											Weapon_Spread = -1;

											(*Primary_Attack_Type(*(unsigned __int32*)Weapon + 856))(Weapon);

											float Direction[3] =
											{
												Forward[0] + Random_X * Weapon_Spread * Right[0] + Random_Y * Weapon_Spread * Up[1],

												Forward[1] + Random_X * Weapon_Spread * Right[1] + Random_Y * Weapon_Spread * Up[1],

												Forward[2] + Random_X * Weapon_Spread * Right[2] + Random_Y * Weapon_Spread * Up[2],
											};

											Vector_Normalize(Direction);

											Weapon_Spread = 0;

											float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

											User_Command->View_Angles[0] = Arc_Tangent_2(Square_Root(__builtin_powf(Direction[0], 2) + __builtin_powf(Direction[1], 2)), -Direction[2]) * 180 / 3.1415927f - Recoil[0] * 2;

											User_Command->View_Angles[1] = Arc_Tangent_2(Direction[0], Direction[1]) * 180 / 3.1415927f - Recoil[1] * 2;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (In_Attack == 0)
	{
		User_Command->Buttons_State &= ~1;

		if (Sorted_Target_List.size() != 0)
		{
			User_Command->View_Angles[0] = Console_Variable_Angle_X.Floating_Point;

			Update_Animation_Angle[0] = User_Command->View_Angles[0];

			float* Optimal_Target_Origin = (float*)((unsigned __int32)Sorted_Target_List.at(0).Target + 668);

			float Origin_Difference[2] =
			{
				Optimal_Target_Origin[0] - Local_Player_Origin[0],

				Optimal_Target_Origin[1] - Local_Player_Origin[1]
			};

			if (Send_Packet == 0)
			{
				if ((User_Command->Command_Number % 2) == 0)
				{
					User_Command->View_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f + Console_Variable_First_Choked_Angle_Y.Floating_Point;
				}
				else
				{
					User_Command->View_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f + Console_Variable_Second_Choked_Angle_Y.Floating_Point;
				}
			}
			else
			{
				User_Command->View_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f + Console_Variable_Angle_Y.Floating_Point;

				Update_Animation_Angle[1] = User_Command->View_Angles[1];
			}
		}
		else
		{
			Update_Animation_Angle[0] = User_Command->View_Angles[0];

			Update_Animation_Angle[1] = User_Command->View_Angles[1];
		}
	}

	*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 24) = Send_Packet;

	float Desired_Move_Forward[3];

	float Desired_Move_Right[3];

	Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right, nullptr);

	Desired_Move_Forward[2] = 0;

	Desired_Move_Right[2] = 0;

	Vector_Normalize(Desired_Move_Forward);

	Vector_Normalize(Desired_Move_Right);

	float Desired_Move[2] =
	{
		Desired_Move_Forward[0] * User_Command->Move[0] + Desired_Move_Right[0] * User_Command->Move[1],

		Desired_Move_Forward[1] * User_Command->Move[0] + Desired_Move_Right[1] * User_Command->Move[1]
	};

	float Move_Forward[3];

	float Move_Right[3];

	Angle_Vectors(User_Command->View_Angles, Move_Forward, Move_Right, nullptr);

	Move_Forward[2] = 0;

	Move_Right[2] = 0;

	Vector_Normalize(Move_Forward);

	Vector_Normalize(Move_Right);

	float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

	User_Command->Move[0] = (Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider;

	User_Command->Move[1] = (Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider;

	(decltype(&Redirected_Copy_User_Command)(Original_Copy_User_Command_Caller_Location))(Unknown_Parameter, User_Command);
}