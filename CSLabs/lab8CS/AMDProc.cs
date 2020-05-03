using System;

namespace lab8cs
{
    class AMDProc: Processor, ICloneable
    {
        public override string socket { get; set; }
        public override Architecture architecture { get; set; }
        //****************************METHODS***************************
        public AMDProc(string socket = "AM4", Architecture architecture = Architecture.RISC): base() { this.socket = socket; this.architecture = architecture; }
        public AMDProc(string serial, int opPerSec, int version,
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
        public void AMDFunc(string s1, string s2)
        {
            Console.WriteLine($"AMD corp.(s1+s2):{s1 + s2}");
        }
        public object Clone()
        {
            return this.MemberwiseClone();
        }
    }
}
