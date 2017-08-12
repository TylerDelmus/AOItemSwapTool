#include "windows.h"
#include <detours.h>
#include "N3Engine_t.h"

#pragma comment(lib, "detours.lib") 

using namespace std;

typedef bool (N3EngineClientAnarchy_t::*N3Msg_MoveItemToInventory)(Identity_t* pSource, int eInvId, int slot);
N3Msg_MoveItemToInventory pMoveItemToInventory(nullptr);

typedef bool (N3EngineClientAnarchy_t::*N3Msg_UseItemOnItem)(Identity_t* pSource, Identity_t* pDest);
N3Msg_UseItemOnItem pUseItemOnItem(nullptr);

typedef int* (N3EngineClientAnarchy_t::*N3Msg_GetInventoryVec)(Identity_t* pIdentity);
N3Msg_GetInventoryVec pGetInventoryVec(nullptr);

typedef int* (N3EngineClientAnarchy_t::*N3Msg_GetContainerInventoryList)(Identity_t* pIdentity);
N3Msg_GetContainerInventoryList pGetContainerInventoryList(nullptr);

int HookMethod(LPCSTR pszModule, LPCSTR pszFunction, PVOID* ppPointer, PVOID pDetour)
{
	auto function = DetourFindFunction(pszModule, pszFunction);

	if (function == NULL)
		return ERROR_INVALID_HANDLE;

	*ppPointer = function;

	if (pDetour == NULL)
		return NULL;

	return DetourAttach(ppPointer, pDetour);
}

void __fastcall OnUseItemOnItem(N3EngineClientAnarchy_t *const pN3Engine, int /*dummy*/, Identity_t* pSource, Identity_t* pDest)
{
	int* items = (pN3Engine->*pGetInventoryVec) (&pN3Engine->LocalPlayer->Identity);

	Identity_t* pContainer = (Identity_t*)(*(int*)(*items + (pDest->Instance * 0x4)) + 0x4);

	if (pDest->Type == 0x68 && pContainer->Type == 51017)
	{
		int* pContainerInvList = (pN3Engine->*pGetContainerInventoryList) (pContainer);
		int bagHandle = *(int*)(*(int*)*pContainerInvList + 0x0C);

		pDest->Type = 0x6B;
		pDest->Instance = bagHandle;

		(pN3Engine->*pMoveItemToInventory) (pDest, 1, pSource->Instance);
		return;
	}

	(pN3Engine->*pUseItemOnItem) (pSource, pDest);
}

BOOL APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch (Reason)
	{
		case DLL_PROCESS_ATTACH:
			MessageBox(0, "Successfully injected.", "", MB_OK);

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			HookMethod("Gamecode.dll", "?N3Msg_MoveItemToInventory@n3EngineClientAnarchy_t@@QBE_NABVIdentity_t@@W4InventoryId_e@@H@Z", (void**)&pMoveItemToInventory, NULL);
			HookMethod("Gamecode.dll", "?N3Msg_UseItemOnItem@n3EngineClientAnarchy_t@@QAEXABVIdentity_t@@0@Z", (void**)&pUseItemOnItem, OnUseItemOnItem);
			HookMethod("Gamecode.dll", "?N3Msg_GetInventoryVec@n3EngineClientAnarchy_t@@QAEPBV?$vector@PAVNewInventoryEntry_t@@V?$allocator@PAVNewInventoryEntry_t@@@std@@@std@@ABVIdentity_t@@@Z", (void**)&pGetInventoryVec, NULL);
			HookMethod("Gamecode.dll", "?N3Msg_GetContainerInventoryList@n3EngineClientAnarchy_t@@QBEPBV?$list@VInventoryEntry_t@@V?$allocator@VInventoryEntry_t@@@std@@@std@@ABVIdentity_t@@@Z", (void**)&pGetContainerInventoryList, NULL);
			DetourTransactionCommit();
			break;
	}

	return TRUE;
}