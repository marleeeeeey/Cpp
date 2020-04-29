using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExampleCsConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            ILibraryImport import = LibraryImport.Select();
            import.SendMsg("Bye");
            import.SetReceiveMessageCallBack(msg => Console.WriteLine($"{msg} Kitty"));
            import.StartCore();
        }
    }
}
