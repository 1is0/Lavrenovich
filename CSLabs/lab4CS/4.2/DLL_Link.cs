using System.Runtime.InteropServices;

namespace DLL_Link
{
    class Linker
    {
        //chage this value for you own path to MyDLL.dll
        private const string path = @"D:\VS2020\lab4CS\4.2\MyDLL\MyDLL.dll";

        [DllImport(path, EntryPoint = "Perimeter", CallingConvention = CallingConvention.StdCall)]
        public static extern double Perimeter(double r);

        [DllImport(path, EntryPoint = "Area", CallingConvention = CallingConvention.Cdecl)]
        public static extern double Area(double r);

        [DllImport(path, EntryPoint = "SectorArea", CallingConvention = CallingConvention.StdCall)]
        public static extern double SectorArea(double r, int angle);

    }
}