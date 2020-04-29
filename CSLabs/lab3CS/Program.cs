using System;

namespace lab3CS
{
    class Program
    {
        private static void AppRun()
        {
            ALU ob1 = new ALU();
            Console.WriteLine("The regular object " + typeof(ALU) + " ob1");
            Console.WriteLine(ob1);
            Console.WriteLine("Trying to do stuff with indexator..");
            Console.Write("Input your index: ");
            int index;
            while (!int.TryParse(Console.ReadLine(), out index))
            {
                Console.Write("Bad input. Input your index: ");
            }
            Console.WriteLine($"\nYour choice is ob1[{index}]: " + ob1[index]);
            Console.WriteLine($"\nInput new value for ob1[{index}]: ");
            int data;
            while (!int.TryParse(Console.ReadLine(), out data))
            {
                Console.Write("Bad input. Input your data: ");
            }
            ob1[index] = data;
            Console.WriteLine($"\nNew info on ob1:\n{ob1}");

            Console.WriteLine("\nLet's create new object using specified constructor.");
            Console.Write("\nInput serial: ");
            string ser = Console.ReadLine();
            while (ser.Equals("") || ser.Contains(" "))
            {
                Console.Write("Bad input. Input serial: ");
                ser = Console.ReadLine();
            }
            int ops, v;
            Console.WriteLine("\nInput operations per second: ");
            while (!int.TryParse(Console.ReadLine(), out ops) || ops <= 10000)
            {
                Console.WriteLine("Bad input. Input operations per second: ");
            }
            Console.WriteLine("\nInput version: ");
            while (!int.TryParse(Console.ReadLine(), out v) || v < 1)
            {
                Console.WriteLine("Bad input. Input operations per second: ");
            }
            Console.WriteLine("\nInput ALU Type:\n(1)Decimal\n(2)Fixed\n(3)Float");
            int choice;
            while (!int.TryParse(Console.ReadLine(), out choice) || choice <= 0 || choice > 3)
            {
                Console.WriteLine("Bad input. Input ALU Type:\n(1)Decimal\n(2)Fixed\n(3)Float");
            }
            ALUType t = (ALUType)(choice - 1);
            ob1 = new ALU(ser, ops, v, t);
            Console.WriteLine($"\nOur new ob1:{ob1}");

            Console.Write("\nPress any key...");
            Console.ReadKey(true);
        }
        static void Main()
        {
            AppRun();
        }
    }
}
