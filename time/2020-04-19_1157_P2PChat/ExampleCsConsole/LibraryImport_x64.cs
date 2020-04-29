using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Runtime.InteropServices;
using System.Text;

namespace ExampleCsConsole
{
    internal class LibraryImport_x64 : ILibraryImport
    {
        [DllImport("ExampleCppLib_x64", CallingConvention = CallingConvention.StdCall, ExactSpelling = false, EntryPoint = "_SetReceiveMessageCallBack@4")]
        private static extern void SetReceiveMessageCallBackInternal(OnReceiveMessageCallBack cb);

        [DllImport("ExampleCppLib_x64", CallingConvention = CallingConvention.StdCall, ExactSpelling = false, EntryPoint = "_StartCore@0")]
        private static extern void StartCoreInternal();

        [DllImport("ExampleCppLib_x64", CallingConvention = CallingConvention.StdCall, ExactSpelling = false, EntryPoint = "_SendMsg@4")]
        private static extern void SendMsgInternal(string msg);


        public void SetReceiveMessageCallBack(OnReceiveMessageCallBack cb)
        {
            SetReceiveMessageCallBackInternal(cb);
        }

        public void StartCore()
        {
            StartCoreInternal();
        }

        public void SendMsg(string msg)
        {
            SendMsgInternal(msg);
        }
    }
}
