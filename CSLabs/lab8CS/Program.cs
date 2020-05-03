using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab8cs
{
    class Program
    {
        delegate void EfficiencyView();
        static event EfficiencyView ShowCoefs;
        static void ViewInfo(Processor[] processors)
        {
            Console.WriteLine("\nView each processor info:");
            foreach (Processor p in processors)
            {
                Console.WriteLine("\n\n");
                Console.WriteLine(p);
            }
        }
        static void Choose(out int choice)
        {
            Console.WriteLine("Select operation:\n(1)a+b\t(2)a-b\t(3)a*b\t(4)a/b:\n");
            while (!int.TryParse(Console.ReadKey(true).KeyChar.ToString(), out choice)|| choice == 0 || choice > 4)
            {
                Console.WriteLine("\nBad input.\nSelect operation:\n(1)a+b\t(2)a-b\t(3)a*b\t(4)a/b:\n");
            }
        }
        static int InputInt(string str)
        {
            Console.Write(str);
            int res;
            while (!int.TryParse(Console.ReadLine(), out res))
            {
                Console.WriteLine("Bad input. Input int value: ");
            }
            return res;
        }
        static void Main(string[] args)
        {
            IntelProc iproc = new IntelProc();
            AMDProc amdproc = new AMDProc("AM5");
            QuantumProc qproc = new QuantumProc("x28df5", 1780000, 256, ALUType.Fixed, 64, MemoryType.DDR3,
                                                4.5, "Q8", Architecture.CISC, new Additionals { L2 = 8, L3 = 38, tp = TechProcess.nm12 });

            Processor[] processors = { iproc, amdproc, qproc };
            ViewInfo(processors);

            Console.WriteLine();
            Choose(out int choice);
            IntelProc.Operation op = default;
            int a = InputInt("a="), b = InputInt("b=");
            string s = default;
            switch (choice)
            {
                case 1: 
                    op = delegate(int x, int y) { return x + y; };
                    s = "a + b = ";
                    break;
                case 2:
                    op = delegate (int x, int y) { return x - y; };
                    s = "a - b = ";
                    break;
                case 3:
                    op = (int x, int y) => x * y;
                    s = "a * b = ";
                    break;
                case 4:
                    op = (int x, int y) => x / y;
                    s = "a / b = ";
                    break;
            }

            try
            {
                iproc.IntelFunc(s, op, a, b);
            }
            catch (DivideByZeroException e)
            {
                Console.WriteLine(e.Message);
            }
            amdproc.AMDFunc("Intel ", "*ucks");
            qproc.QuantumFunc(18001887);

            IntelProc iproc1 = new IntelProc("ic7s1151l315", 18000000, 788, ALUType.Float, 8, MemoryType.DDR4,
                                            5.2, "1151", Architecture.CISC, new Additionals { L2 = 8, L3 = 48, tp = TechProcess.nm22 });
            processors[0] = (IntelProc)iproc1.Clone();
            Console.WriteLine("\n\nFirst processor replaced!");
            ViewInfo(processors);

            Array.Sort(processors);
            Console.WriteLine("\n\nNew sorted processors");
            ViewInfo(processors);

            Console.WriteLine("\n\nEfficiency coefficients of iproc & qproc:");
            ShowCoefs += () => Console.WriteLine($"iproc coef = {iproc.EfficiencyCoef()}");
            ShowCoefs += () => Console.WriteLine($"qproc coef = {qproc.EfficiencyCoef()}");
            ShowCoefs();

            Console.ReadKey(true);
        }
    }
}
