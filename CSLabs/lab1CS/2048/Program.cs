using System;

public interface ICloneable
{
    object Clone();
}

enum MoveDirection
{
    Up,
    Down,
    Left,
    Right
}


class Program
{
    static void Main()
    {
        CheckRestart();
    }

    private static void RunGame()
    {
        G2048 game = new G2048();
        Console.Clear();
        game.Loop();

        CheckRestart();
    }

    private static void CheckRestart()
    {
        Console.WriteLine("(N) New game (P) Exit");
        while (true)
        {
            char input;
            //char.TryParse(Console.ReadKey(true).Key.ToString(), out input);
            input = (char)Console.Read();
            input = Char.ToUpper(input);
            switch (input)
            {
                case 'N':
                    RunGame();
                    break;
                case 'P':
                    return;
            }
        }
    }
}
