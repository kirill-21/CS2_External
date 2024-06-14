#include "Offsets.h"
#include "MenuConfig.hpp"
#include <filesystem>

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

	std::string offsetPath = MenuConfig::path + "\\Offsets";
	if (!fs::exists(offsetPath)) {
		std::cerr << "Failed to locate offsets directory: " << offsetPath << std::endl;
		return false;
	}

	std::string dumper_offsets = offsetPath + "\\offsets.json";
	std::string dumper_buttons = offsetPath + "\\buttons.json";
	std::string dumper_client = offsetPath + "\\client.dll.json";

	std::map<std::string, int> offsets, buttons, CCSPlayerController, C_BaseEntity, C_BasePlayerPawn, C_CSPlayerPawn, C_CSPlayerPawnBase,
		CCSPlayer_ViewModelServices, CPlayer_MovementServices_Humanoid, CCSPlayer_BulletServices, CBasePlayerController,
		CCSPlayerBase_CameraServices, EntitySpottedState_t, CPlayer_ObserverServices, C_EconEntity, C_EconItemView,
		CModelState, C_AttributeContainer, CPlayer_WeaponServices, C_CSWeaponBase, CBasePlayerWeaponVData, C_BasePlayerWeapon, CCSWeaponBaseVData,
		C_PlantedC4, CCSPlayerController_InGameMoneyServices, C_SmokeGrenadeProjectile;

	OffsetsParser(offsets, dumper_offsets, "client.dll");
	OffsetsParser(offsets, dumper_offsets, "inputsystem.dll");
	OffsetsParser(buttons, dumper_buttons, "client.dll");

	Offset::EntityList = GetOffset(offsets, "dwEntityList");
	Offset::Matrix = GetOffset(offsets, "dwViewMatrix");
	Offset::ViewAngle = GetOffset(offsets, "dwViewAngles");
	Offset::LocalPlayerController = GetOffset(offsets, "dwLocalPlayerController");
	Offset::LocalPlayerPawn = GetOffset(offsets, "dwLocalPlayerPawn");
	Offset::GlobalVars = GetOffset(offsets, "dwGlobalVars");
	Offset::PlantedC4 = GetOffset(offsets, "dwPlantedC4");
	Offset::Sensitivity = GetOffset(offsets, "dwSensitivity");
	Offset::InputSystem = GetOffset(offsets, "dwInputSystem");
	Offset::ForceJump = GetOffset(buttons, "jump");

	// CCSPlayerController
	std::ifstream file(dumper_client);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << dumper_client << std::endl;
		return false;
	}

	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CCSPlayerController"]["fields"].items()) {
			CCSPlayerController[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_BaseEntity
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_BaseEntity"]["fields"].items()) {
			C_BaseEntity[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_BasePlayerPawn
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_BasePlayerPawn"]["fields"].items()) {
			C_BasePlayerPawn[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_BasePlayerPawn
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_BasePlayerPawn"]["fields"].items()) {
			C_BasePlayerPawn[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CCSPlayerController_InGameMoneyServices
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CCSPlayerController_InGameMoneyServices"]["fields"].items()) {
			CCSPlayerController_InGameMoneyServices[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_SmokeGrenadeProjectile
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_SmokeGrenadeProjectile"]["fields"].items()) {
			C_SmokeGrenadeProjectile[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_PlantedC4
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_PlantedC4"]["fields"].items()) {
			C_PlantedC4[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_AttributeContainer
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_AttributeContainer"]["fields"].items()) {
			C_AttributeContainer[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CPlayer_WeaponServices
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CPlayer_WeaponServices"]["fields"].items()) {
			CPlayer_WeaponServices[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_CSWeaponBase
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_CSWeaponBase"]["fields"].items()) {
			C_CSWeaponBase[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CBasePlayerWeaponVData
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CBasePlayerWeaponVData"]["fields"].items()) {
			CBasePlayerWeaponVData[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_BasePlayerWeapon
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_BasePlayerWeapon"]["fields"].items()) {
			C_BasePlayerWeapon[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CCSWeaponBaseVData
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CCSWeaponBaseVData"]["fields"].items()) {
			CCSWeaponBaseVData[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_CSPlayerPawn
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_CSPlayerPawn"]["fields"].items()) {
			C_CSPlayerPawn[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_EconItemView
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_EconItemView"]["fields"].items()) {
			C_EconItemView[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_EconEntity
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_EconEntity"]["fields"].items()) {
			C_EconEntity[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// C_CSPlayerPawnBase
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["C_CSPlayerPawnBase"]["fields"].items()) {
			C_CSPlayerPawnBase[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CCSPlayer_ViewModelServices
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CCSPlayer_ViewModelServices"]["fields"].items()) {
			CCSPlayer_ViewModelServices[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CPlayer_MovementServices_Humanoid
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CPlayer_MovementServices_Humanoid"]["fields"].items()) {
			CPlayer_MovementServices_Humanoid[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CCSPlayer_BulletServices
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CCSPlayer_BulletServices"]["fields"].items()) {
			CCSPlayer_BulletServices[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CBasePlayerController
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CBasePlayerController"]["fields"].items()) {
			CBasePlayerController[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CCSPlayerBase_CameraServices
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CCSPlayerBase_CameraServices"]["fields"].items()) {
			CCSPlayerBase_CameraServices[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// EntitySpottedState_t
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["EntitySpottedState_t"]["fields"].items()) {
			EntitySpottedState_t[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// CPlayer_ObserverServices
	file.seekg(0, std::ios::beg);
	try {
		nlohmann::json json;
		file >> json;
		for (auto& element : json["client.dll"]["classes"]["CPlayer_ObserverServices"]["fields"].items()) {
			CPlayer_ObserverServices[element.key()] = element.value();
		}
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON parsing error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	file.close();

	// Entity
	Offset::Entity.IsAlive = GetOffset(CCSPlayerController, "m_bPawnIsAlive");
	Offset::Entity.PlayerPawn = GetOffset(CCSPlayerController, "m_hPlayerPawn");
	Offset::Entity.iszPlayerName = GetOffset(CCSPlayerController, "m_iszPlayerName");
	Offset::Entity.GravityScale = GetOffset(C_BaseEntity, "m_flGravityScale");

	// Pawn
	Offset::Pawn.MovementServices = GetOffset(C_BasePlayerPawn, "m_pMovementServices");
	Offset::Pawn.WeaponServices = GetOffset(C_BasePlayerPawn, "m_pWeaponServices");
	Offset::Pawn.BulletServices = GetOffset(C_CSPlayerPawnBase, "m_pBulletServices");
	Offset::Pawn.CameraServices = GetOffset(C_BasePlayerPawn, "m_pCameraServices");
	Offset::Pawn.ViewModelServices = GetOffset(C_CSPlayerPawnBase, "m_pViewModelServices");
	Offset::Pawn.pClippingWeapon = GetOffset(C_CSPlayerPawnBase, "m_pClippingWeapon");
	Offset::Pawn.ViewModel = GetOffset(CCSPlayer_ViewModelServices, "m_hViewModel");
	Offset::Pawn.CrouchState = GetOffset(CPlayer_MovementServices_Humanoid, "m_nCrouchState");
	Offset::Pawn.isScoped = GetOffset(C_CSPlayerPawn, "m_bIsScoped");
	Offset::Pawn.isDefusing = GetOffset(C_CSPlayerPawn, "m_bIsDefusing");
	Offset::Pawn.TotalHit = GetOffset(CCSPlayer_BulletServices, "m_totalHitsOnServer");
	Offset::Pawn.Pos = GetOffset(C_BasePlayerPawn, "m_vOldOrigin");
	Offset::Pawn.CurrentArmor = GetOffset(C_CSPlayerPawn, "m_ArmorValue");
	Offset::Pawn.MaxHealth = GetOffset(C_BaseEntity, "m_iMaxHealth");
	Offset::Pawn.CurrentHealth = GetOffset(C_BaseEntity, "m_iHealth");
	Offset::Pawn.GameSceneNode = GetOffset(C_BaseEntity, "m_pGameSceneNode");
	// Offset::Pawn.BoneArray = 0; // TODO!
	Offset::Pawn.angEyeAngles = GetOffset(C_CSPlayerPawnBase, "m_angEyeAngles");
	Offset::Pawn.vecLastClipCameraPos = GetOffset(C_CSPlayerPawnBase, "m_vecLastClipCameraPos");
	Offset::Pawn.iShotsFired = GetOffset(C_CSPlayerPawn, "m_iShotsFired");
	Offset::Pawn.flFlashMaxAlpha = GetOffset(C_CSPlayerPawnBase, "m_flFlashMaxAlpha");
	Offset::Pawn.flFlashDuration = GetOffset(C_CSPlayerPawnBase, "m_flFlashDuration");
	Offset::Pawn.aimPunchAngle = GetOffset(C_CSPlayerPawn, "m_aimPunchAngle"); 
	Offset::Pawn.aimPunchCache = GetOffset(C_CSPlayerPawn, "m_aimPunchCache");
	Offset::Pawn.iIDEntIndex = GetOffset(C_CSPlayerPawnBase, "m_iIDEntIndex");
	Offset::Pawn.iTeamNum = GetOffset(C_BaseEntity, "m_iTeamNum");
	Offset::Pawn.DesiredFov = GetOffset(CBasePlayerController, "m_iDesiredFOV");
	Offset::Pawn.iFovStart = GetOffset(CCSPlayerBase_CameraServices, "m_iFOVStart");
	Offset::Pawn.fFlags = GetOffset(C_BaseEntity, "m_fFlags");
	Offset::Pawn.bSpottedByMask = GetOffset(C_CSPlayerPawn, "m_entitySpottedState") + GetOffset(EntitySpottedState_t, "m_bSpottedByMask");
	Offset::Pawn.IsBuying = GetOffset(C_CSPlayerPawn, "m_bIsBuyMenuOpen");
	
	// PlayerController
	Offset::PlayerController.m_hPawn = GetOffset(CBasePlayerController, "m_hPawn");
	Offset::PlayerController.m_pObserverServices = GetOffset(C_BasePlayerPawn, "m_pObserverServices");
	Offset::PlayerController.m_hObserverTarget = GetOffset(CPlayer_ObserverServices, "m_hObserverTarget");
	Offset::PlayerController.m_hController = GetOffset(C_BasePlayerPawn, "m_hController");
	Offset::PlayerController.PawnArmor = GetOffset(CCSPlayerController, "m_iPawnArmor");
	Offset::PlayerController.HasDefuser = GetOffset(CCSPlayerController, "m_bPawnHasDefuser");
	Offset::PlayerController.HasHelmet = GetOffset(CCSPlayerController, "m_bPawnHasHelmet");

	// EconEntity
	Offset::EconEntity.AttributeManager = GetOffset(C_EconEntity, "m_AttributeManager");
	Offset::EconEntity.FallbackPaintKit = GetOffset(C_EconEntity, "m_nFallbackPaintKit");
	Offset::EconEntity.FallbackSeed = GetOffset(C_EconEntity, "m_nFallbackSeed");
	Offset::EconEntity.FallbackWear = GetOffset(C_EconEntity, "m_flFallbackWear");
	Offset::EconEntity.FallbackStatTrak = GetOffset(C_EconEntity, "m_nFallbackStatTrak");
	Offset::EconEntity.szCustomName = GetOffset(C_EconItemView, "m_szCustomName");
	Offset::EconEntity.EntityQuality = GetOffset(C_EconItemView, "m_iEntityQuality");
	Offset::EconEntity.ItemIDHigh = GetOffset(C_EconItemView, "m_iItemIDHigh");

	// WeaponBaseData
	Offset::WeaponBaseData.WeaponDataPTR = GetOffset(C_BaseEntity, "m_nSubclassID") + 0x08;
	Offset::WeaponBaseData.szName = GetOffset(CCSWeaponBaseVData, "m_szName");
	Offset::WeaponBaseData.Clip1 = GetOffset(C_BasePlayerWeapon, "m_iClip1");
	Offset::WeaponBaseData.MaxClip = GetOffset(CBasePlayerWeaponVData, "m_iMaxClip1");
	Offset::WeaponBaseData.CycleTime = GetOffset(CCSWeaponBaseVData, "m_flCycleTime");
	Offset::WeaponBaseData.Penetration = GetOffset(CCSWeaponBaseVData, "m_flPenetration"); 
	Offset::WeaponBaseData.WeaponType = GetOffset(CCSWeaponBaseVData, "m_WeaponType");
	Offset::WeaponBaseData.Inaccuracy = GetOffset(CCSWeaponBaseVData, "m_flInaccuracyMove");
	Offset::WeaponBaseData.inReload = GetOffset(C_CSWeaponBase, "m_bInReload");
	Offset::WeaponBaseData.WeaponSize = 0x50;
	Offset::WeaponBaseData.ActiveWeapon = GetOffset(CPlayer_WeaponServices, "m_hActiveWeapon");
	Offset::WeaponBaseData.Item = GetOffset(C_AttributeContainer, "m_Item");
	Offset::WeaponBaseData.ItemDefinitionIndex = GetOffset(C_EconItemView, "m_iItemDefinitionIndex");
	Offset::WeaponBaseData.m_MeshGroupMask = GetOffset(CModelState, "m_MeshGroupMask");

	// C4
	Offset::C4.m_bBeingDefused = GetOffset(C_PlantedC4, "m_bBeingDefused");
	Offset::C4.m_flDefuseCountDown = GetOffset(C_PlantedC4, "m_flDefuseCountDown");
	Offset::C4.m_nBombSite = GetOffset(C_PlantedC4, "m_nBombSite");

	// InGameMoneyServices
	Offset::InGameMoneyServices.MoneyServices = GetOffset(CCSPlayerController, "m_pInGameMoneyServices");
	Offset::InGameMoneyServices.Account = GetOffset(CCSPlayerController_InGameMoneyServices, "m_iAccount");
	Offset::InGameMoneyServices.TotalCashSpent = GetOffset(CCSPlayerController_InGameMoneyServices, "m_iTotalCashSpent");
	Offset::InGameMoneyServices.CashSpentThisRound = GetOffset(CCSPlayerController_InGameMoneyServices, "m_iCashSpentThisRound");

	// SmokeGrenadeProjectile
	Offset::SmokeGrenadeProjectile.nSmokeEffectTickBegin = GetOffset(C_SmokeGrenadeProjectile, "m_nSmokeEffectTickBegin");
	Offset::SmokeGrenadeProjectile.bDidSmokeEffect = GetOffset(C_SmokeGrenadeProjectile, "m_bDidSmokeEffect");
	Offset::SmokeGrenadeProjectile.nRandomSeed = GetOffset(C_SmokeGrenadeProjectile, "m_nRandomSeed");
	Offset::SmokeGrenadeProjectile.vSmokeColor = GetOffset(C_SmokeGrenadeProjectile, "m_vSmokeColor");
	Offset::SmokeGrenadeProjectile.vSmokeDetonationPos = GetOffset(C_SmokeGrenadeProjectile, "m_vSmokeDetonationPos");
	Offset::SmokeGrenadeProjectile.VoxelFrameData = GetOffset(C_SmokeGrenadeProjectile, "m_VoxelFrameData");
	Offset::SmokeGrenadeProjectile.bSmokeVolumeDataReceived = GetOffset(C_SmokeGrenadeProjectile, "m_bSmokeVolumeDataReceived");
	Offset::SmokeGrenadeProjectile.bSmokeEffectSpawned = GetOffset(C_SmokeGrenadeProjectile, "m_bSmokeEffectSpawned");

	return true;
}
