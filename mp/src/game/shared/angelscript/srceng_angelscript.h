#ifndef SRCENG_ANGELSCRIPT_H
#define SRCENG_ANGELSCRIPT_H

#ifdef _WIN32
#pragma once
#endif

#include "../../angelscript/sdk/angelscript/include/angelscript.h"
#include "../../angelscript/sdk/add_on/scriptstdstring/scriptstdstring.h"
#include "../../angelscript/sdk/add_on/scriptbuilder/scriptbuilder.h"
#include "const.h"

class CAngelScript
{
public:
	CAngelScript();
	~CAngelScript();

	void		Init();
	void		Shutdown();
	asIScriptEngine* GetScriptEngine() { return  m_hScriptEngine; }

private:
	asIScriptEngine* m_hScriptEngine;
};

#ifdef  GAME_DLL
extern CAngelScript g_AngelScript_Server;
#elif	CLIENT_DLL
extern CAngelScript g_AngelScript_Client;
#endif //  GAME_DLL
#endif