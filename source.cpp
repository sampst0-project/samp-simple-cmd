#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "SDK/plugincommon.h"
#include "SDK/amx/amx.h"

typedef void(*logprintf_t)(const char* format, ...);
logprintf_t logprintf;
void ** ppPluginData;
extern void * pAMXFunctions;

// [terminal]

cell AMX_NATIVE_CALL TerminalCommand(AMX* amx, cell* params)
{
	int len = NULL, ret = NULL;
	cell *addr = NULL;

	amx_GetAddr(amx, params[1], &addr);
	amx_StrLen(addr, &len);

	if (len)
	{
		len++;

		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		char buff[100];
		snprintf(buff, sizeof(buff), "%s", text);

		delete[] text;
		return system(buff);
	}

	return 0;
}

cell AMX_NATIVE_CALL print_t(AMX* amx, cell* params)
{
	int len = NULL, ret = NULL;
	cell *addr = NULL;

	amx_GetAddr(amx, params[1], &addr);
	amx_StrLen(addr, &len);

	if (len)
	{
		len++;

		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		char buff[100];
		snprintf(buff, sizeof(buff), "%s", text);

		delete[] text;
		return printf("%s", text);
	}

	return 0;
}

cell AMX_NATIVE_CALL TerminalTitle(AMX* amx, cell* params)
{
	int len = NULL, ret = NULL;
	cell *addr = NULL;

	amx_GetAddr(amx, params[1], &addr);
	amx_StrLen(addr, &len);

	if (len)
	{
		len++;

		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		HANDLE csl = GetStdHandle(STD_OUTPUT_HANDLE);;

		char buff[100];
		snprintf(buff, sizeof(buff), "%s", text);

		delete[] text;
		return SetConsoleTitleA(text);
	}

	return 0;
}

// hook



// ------------------------------------------------

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf(" * terminal load.");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf(" * terminal plugin unload.");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "TerminalCommand", TerminalCommand },
	{ "TerminalTitle", TerminalTitle },
	{ "print_t", print_t },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
