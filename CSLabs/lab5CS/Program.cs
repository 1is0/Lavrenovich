using System;

namespace lab5cs
{
    class Program
    {
        static void ViewInfo(Processor[] processors)
        {
            Console.WriteLine("View each processor info:");
            foreach (Processor p in processors)
            {
                Console.WriteLine("\n\n");
                Console.WriteLine(p);
            }
        }
        static void Main()
        {
            IntelProc iproc = new IntelProc();
            AMDProc amdproc = new AMDProc("AM5");
            QuantumProc qproc = new QuantumProc("x28df5", 1780000, 256, ALUType.Fixed, 64, MemoryType.DDR3, 
                                                4.5, "Q8", Architecture.CISC, new Additionals{ L2 = 8, L3 = 38, tp = TechProcess.nm12});

            Processor[] processors = { iproc, amdproc, qproc };
            ViewInfo(processors);

            Console.WriteLine();
            iproc.IntelFunc(18, -56);
            amdproc.AMDFunc("Intel ", "*ucks");
            qproc.QuantumFunc(18001887);

            Console.ReadKey(true);
        }
    }
}
