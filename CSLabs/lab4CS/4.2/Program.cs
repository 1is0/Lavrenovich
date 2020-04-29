using System;
using System.Globalization;

namespace DLL_Link
{
    class Program
    {
        static void Main()
        {
            //for '.' separator in double
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            
            double r;
            int angle;
           
            Console.WriteLine($"\t\t\tCircle Functions");
            Console.WriteLine("Input radius of a circle: ");
            while (!double.TryParse(Console.ReadLine(), out r) || r <= 0)
            {
                Console.WriteLine("Bad input. Input radius of a circle: ");
            }
            Console.WriteLine("Input angle of sector (in degrees 1 - 360): ");
            while (!int.TryParse(Console.ReadLine(), out angle) ||  angle <= 0 || angle > 360)
            {
                Console.WriteLine("Bad input. Input angle of sector (in degrees 1 - 360): ");
            }
            Console.WriteLine($"Circle with radius {r:F} and sector angle {angle:D}:");
            Console.WriteLine("-------------------------");
            Console.WriteLine($"Area: {Linker.Area(r):F}");
            Console.WriteLine($"Perimeter: {Linker.Perimeter(r):F}");
            Console.WriteLine($"Area of sector: {Linker.SectorArea(r, angle):F}");

            Console.ReadKey();
        }
    }
}
