using System;

namespace lab8cs
{
    class IntelProc: Processor, ICloneable
    {
        public delegate int Operation(int a, int b);
        public override string socket { get; set; }
        public override Architecture architecture { get; set; }
        //****************************METHODS***************************
        public IntelProc(string socket = "1151", Architecture architecture = Architecture.CISC) : base() { this.socket = socket; this.architecture = architecture; }
        public IntelProc(string serial, int opPerSec, int version,
                        ALUType type, int cores, MemoryType mt,
                        double freq, string soc, Architecture arc, Additionals ad)
        : base(serial, opPerSec, version, type, cores, mt, freq, ad)
        {
            socket = soc;
            architecture = arc;
        }
        public override string ToString()
        {
            return base.ToString() + "\nSocket: " + socket + "\nArchitecture: " + architecture.ToString();
        }
        public void IntelFunc(string str, Operation op, int a, int b)
        {
            Console.WriteLine(str + op(a, b).ToString());
        }
        public object Clone()
        {
            return this.MemberwiseClone();
        }
    }
}
