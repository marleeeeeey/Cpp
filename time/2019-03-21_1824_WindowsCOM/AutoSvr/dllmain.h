// dllmain.h : Declaration of module class.

class CAutoSvrModule : public ATL::CAtlDllModuleT< CAutoSvrModule >
{
public :
	DECLARE_LIBID(LIBID_AutoSvrLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_AUTOSVR, "{1bbad6a5-0770-47d7-bf64-a6489bd9e8a5}")
};

extern class CAutoSvrModule _AtlModule;
