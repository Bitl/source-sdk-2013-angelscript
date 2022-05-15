#include "cbase.h"
#include "srceng_angelscript.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#ifdef CLIENT_DLL
//------------------------------------------------------------------------------
// Purpose: Disables all NPCs
//------------------------------------------------------------------------------
void CC_PrintVersion(void)
{
	Msg("Version: %s\n", ANGELSCRIPT_VERSION_STRING);
}
static ConCommand as_version("as_version", CC_PrintVersion, "", FCVAR_CLIENTDLL);
#endif

#ifdef  GAME_DLL
CAngelScript g_AngelScript_Server;
const char* m_sName = "GAME_DLL";
#elif	CLIENT_DLL
CAngelScript g_AngelScript_Client;
const char* m_sName = "CLIENT_DLL";
#else
const char* m_sName = "what the hell did you do";
#endif //  GAME_DLL

void MessageCallback(const asSMessageInfo* msg, void* param)
{
	const char* type = "ERR";
	if (msg->type == asMSGTYPE_WARNING)
	{
		type = "WARN";
		Warning("CAngelScript (%s): %s (%d, %d) : %s : %s\n", m_sName, msg->section, msg->row, msg->col, type, msg->message);
	}
	else if (msg->type == asMSGTYPE_INFORMATION)
	{
		type = "INFO";
		Msg("CAngelScript (%s): %s (%d, %d) : %s : %s\n", m_sName, msg->section, msg->row, msg->col, type, msg->message);
	}
	else
	{
		Error("CAngelScript (%s): %s (%d, %d) : %s : %s\n", m_sName, msg->section, msg->row, msg->col, type, msg->message);
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CAngelScript::CAngelScript()
{
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CAngelScript::~CAngelScript()
{
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CAngelScript::Init()
{
	Msg("CAngelScript (%s): Initalizing version %s...\n", m_sName, ANGELSCRIPT_VERSION_STRING);
	//init the engine
	m_hScriptEngine = asCreateScriptEngine();

	if (m_hScriptEngine == NULL)
	{
		Warning("CAngelScript (%s): Initalizion failed due to null script engine pointer...\n", m_sName);
		return;
	}
	else
	{
		// Set the message callback to receive information on errors in human readable form.
		int r = m_hScriptEngine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
		Msg("CAngelScript (%s): SetMessageCallback returned %i\n", m_sName, r);

		if (r >= 0)
		{
			Warning("CAngelScript (%s): Initalizion failed due to invalid script message callback code...\n", m_sName);
			return;
		}
		else
		{
			Msg("CAngelScript (%s): Initalized!\n", m_sName);
		}
	}
}

void CAngelScript::Shutdown()
{
	m_hScriptEngine->ShutDownAndRelease();
}