using System;
using System.Diagnostics;
using System.IO;

namespace lab1CS
{
    class Program
    {
        static void Main()
        {
            /*
             * файл BoardState.txt необходимо закинуть в ту же директорию, что и 2048.exe!!!
            */        
            using (Process game = new Process())
            {
                ProcessStartInfo startInfo = new ProcessStartInfo();
                startInfo.UseShellExecute = false;
                startInfo.FileName = Environment.CurrentDirectory + "\\2048.exe";
                startInfo.RedirectStandardInput = true;
                game.StartInfo = startInfo;
                
                game.Start();
                StreamWriter input = game.StandardInput;
                Console.ReadKey();
                input.Write("n");//starting a new game
                Bot bot = new Bot(ref input);
                bot.Loop();
                Console.ReadKey();
                input.Write("p");
                input.Write("p");//этот баг был и в самом 2048
            }
        }
    }
}
