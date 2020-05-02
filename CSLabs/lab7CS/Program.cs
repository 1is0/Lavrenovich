using System;

namespace lab7CS
{
    class Program
    {
        static void ViewInfo(Fraction[] fractions)
        {
            Console.WriteLine("Current fractions:");
            foreach (Fraction f in fractions)
                Console.WriteLine($"{f}");
            Console.WriteLine();
        }
        static Fraction DoubleParse()
        {
            double d;
            Console.WriteLine("Double representation.\nInput double value: ");
            while (!double.TryParse(Console.ReadLine(), out d))
            {
                Console.WriteLine("Bad input. Input double value: ");
            }
            return new Fraction(d);
        }
        static Fraction NMParse()
        {
            int n;
            uint m;
            Console.WriteLine("n, m representation.\nInput n: ");
            while (!int.TryParse(Console.ReadLine(), out n))
            {
                Console.WriteLine("Bad input. Input n: ");
            }
            Console.WriteLine("Input m: ");
            while (!uint.TryParse(Console.ReadLine(), out m) || m == 0)
            {
                Console.WriteLine("Bad input. Input m: ");
            }
            return new Fraction(n, m);
        }
        static Fraction StringParse()
        {
            Fraction tmp = new Fraction();
            bool success = false;
            Console.WriteLine("String representation.");
            while (!success)
            {
                Console.WriteLine("Input string representation (n/m): ");
                tmp = new Fraction(Console.ReadLine(), out success);
            }
            return tmp;
        }
        static void MathOpsBlock(Fraction[] fracs)
        {
            Random rand = new Random();
            int i, j;
            Fraction sum, diff, prod, quot;
            Console.WriteLine("Math operations: ");
            i = rand.Next(fracs.Length); j = rand.Next(fracs.Length);//only one time

            sum = fracs[i] + fracs[j];
            Console.WriteLine($"{fracs[i].NormalView()} + {fracs[j].NormalView()} = {sum.NormalView()}");
            diff = fracs[i] - fracs[j];
            Console.WriteLine($"{fracs[i].NormalView()} - {fracs[j].NormalView()} = {diff.NormalView()}");
            prod = fracs[i] * fracs[j];
            Console.WriteLine($"{fracs[i].NormalView()} * {fracs[j].NormalView()} = {prod.NormalView()}");
            bool canDivide = true;
            try
            {
                quot = fracs[i] / fracs[j];
            }
            catch (DivideByZeroException e)
            {
                Console.WriteLine(e.Message);
                canDivide = false;
                quot = new Fraction();
            }
            Console.WriteLine($"{fracs[i].NormalView()} / {fracs[j].NormalView()} = " + ((canDivide) ? quot.NormalView() : "NaN"));
        }
        static void ComparingBlock(Fraction[] fracs)
        {
            Random rand = new Random();
            int i, j;

            i = rand.Next(fracs.Length); j = rand.Next(fracs.Length);
            Console.WriteLine($"{fracs[i].NormalView()} == {fracs[j].NormalView()} ? ---> {fracs[i].Equals(fracs[j]).ToString()}");
            i = rand.Next(fracs.Length); j = rand.Next(fracs.Length);
            Console.WriteLine($"{fracs[i].NormalView()} != {fracs[j].NormalView()} ? ---> {(!fracs[i].Equals(fracs[j])).ToString()}");
            i = rand.Next(fracs.Length); j = rand.Next(fracs.Length);
            Console.WriteLine($"{fracs[i].NormalView()} > {fracs[j].NormalView()} ? ---> {(fracs[i] > fracs[j]).ToString()}");
            i = rand.Next(fracs.Length); j = rand.Next(fracs.Length);
            Console.WriteLine($"{fracs[i].NormalView()} >= {fracs[j].NormalView()} ? ---> {(fracs[i] >= fracs[j]).ToString()}");
            i = rand.Next(fracs.Length); j = rand.Next(fracs.Length);
            Console.WriteLine($"{fracs[i].NormalView()} < {fracs[j].NormalView()} ? ---> {(fracs[i] < fracs[j]).ToString()}");
            i = rand.Next(fracs.Length); j = rand.Next(fracs.Length);
            Console.WriteLine($"{fracs[i].NormalView()} <= {fracs[j].NormalView()} ? ---> {(fracs[i] <= fracs[j]).ToString()}");
        }

        static void Main()
        {
            //for '.' separator in double
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

            Fraction[] fracs = new Fraction[8];
            fracs[0] = new Fraction();
            fracs[1] = new Fraction(0, 15);
            fracs[2] = new Fraction(-185, 25);
            fracs[3] = new Fraction("1857/-6347", out bool s);
            fracs[4] = new Fraction(1.133);
            fracs[5] = DoubleParse();
            fracs[6] = NMParse();
            fracs[7] = StringParse();
            ViewInfo(fracs);

            //math ops block
            Console.WriteLine("Checking math operations");
            MathOpsBlock(fracs);

            //sorting block
            Console.WriteLine("\n\nSorting things up...\nSorted!");
            Array.Sort(fracs);
            ViewInfo(fracs);

            //comparing block
            Console.WriteLine("Comparing random elements");
            ComparingBlock(fracs);

            Console.Write("Press any key to close the window.");
            Console.ReadKey(true);
        }
    }
}
