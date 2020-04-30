using System;

namespace lab5cs
{
    class QuantumProc: Processor
    {
        public override string socket { get; set; }
        public override Architecture architecture { get; set; }
        //****************************METHODS***************************
        public QuantumProc(string socket = "Q567", Architecture architecture = Architecture.RISC) : base() { this.socket = socket; this.architecture = architecture; }
        public QuantumProc(string serial, int opPerSec, int version,
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
        public void QuantumFunc(int seed)
        {
            Random r = new Random(seed);
            Console.Write("Quantum corp.(random by seed generation): ");
            for (int i = 0; i < 10; i++)
                Console.Write($"{r.Next()} ");
            Console.WriteLine();
        }
    }
}
