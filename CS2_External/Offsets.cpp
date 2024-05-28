#include "Offsets.h"
#include <KnownFolders.h>
#include <ShlObj.h>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

DWORD64 SearchOffsets(std::string Signature, DWORD64 ModuleAddress)
{
	std::vector<DWORD64> TempAddressList;
	DWORD64 Address = 0;
	DWORD Offsets = 0;

	TempAddressList = ProcessMgr.SearchMemory(Signature, ModuleAddress, ModuleAddress + 0x4000000);

	if (TempAddressList.size() <= 0)
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD>(TempAddressList.at(0) + 3, Offsets))
		return 0;

	Address = TempAddressList.at(0) + Offsets + 7;
	return Address;
}

bool Offset::UpdateOffsets()
{
	using namespace Updater;

	char documentsPath[MAX_PATH];
	if (SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, documentsPath) != S_OK) {
		std::cout << "[Info] Error: Failed to get the Documents folder path." << std::endl;
		return false;
	}

	std::string path = documentsPath;
	path += "\\Documents\\TKazer";

	std::string offsetPath = path + "\\Offsets";
	if (!fs::exists(offsetPath)) {
		std::cerr << "Failed to locate offsets directory: " << offsetPath << std::endl;
		return false;
	}

	std::string dumper_offsets = offsetPath + "\\offsets.json";
	std::string dumper_buttons = offsetPath + "\\buttons.json";
	std::string dumper_client = offsetPath + "\\client.json";

	std::map<std::string, int> offsets, buttons;
	OffsetsParser(offsets, dumper_offsets, "client.dll");
	OffsetsParser(offsets, dumper_offsets, "inputsystem.dll");
	OffsetsParser(buttons, dumper_buttons, "client.dll");

	Offset::EntityList = GetOffset(offsets, "dwEntityList");
	Offset::LocalPlayerController = GetOffset(offsets, "dwLocalPlayerController");
	Offset::Matrix = GetOffset(offsets, "dwViewMatrix");
	Offset::GlobalVars = GetOffset(offsets, "dwGlobalVars");
	Offset::ViewAngle = GetOffset(offsets, "dwViewAngles");
	Offset::LocalPlayerPawn = GetOffset(offsets, "dwLocalPlayerPawn");
	Offset::PlantedC4 = GetOffset(offsets, "dwPlantedC4");
	Offset::Sensitivity = GetOffset(offsets, "dwSensitivity");
	Offset::InputSystem = GetOffset(offsets, "dwInputSystem");
	Offset::ForceJump = GetOffset(buttons, "jump");

	return true;
}