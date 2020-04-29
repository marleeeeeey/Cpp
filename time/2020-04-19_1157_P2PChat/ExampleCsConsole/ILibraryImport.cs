using System.Runtime.InteropServices;

namespace ExampleCsConsole
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Ansi)]
    public delegate void OnReceiveMessageCallBack(string value);

    public interface ILibraryImport
    {
        void SetReceiveMessageCallBack(OnReceiveMessageCallBack cb);
        void StartCore();
        void SendMsg(string msg);
    }
}