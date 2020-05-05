using System;
using System.IO;


class G2048
{
    private bool isDone;
    private bool isWon;
    private bool isMoved;
    private int score;
    private Tile[,] board = new Tile[4, 4];
    private Random rand = new Random();

    public G2048()
    {
        isDone = false;
        isWon = false;
        isMoved = true;
        score = 0;
        InitializeBoard();
    }

    private void InitializeBoard()
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                board[x, y] = new Tile();
            }
        }
    }

    public void Loop()
    {
        AddTile();

        while (true)
        {
            if (isMoved)
            {
                AddTile();
            }

            DrawBoard();
            if (isDone)
            {
                break;
            }

            WaitKey();
        }

        string endMessage = isWon ? "You've made it!" : "Game Over!";
        Console.WriteLine(endMessage);
    }

    private void DrawBoard()//закинул сюда код для добавления таблицы в файл
    {
        Console.SetCursorPosition(0, 0);

        using (StreamWriter file = new StreamWriter(Environment.CurrentDirectory + "\\BoardState.txt", false))
        {
            Console.WriteLine("Score: " + score + "\n");
            for (int y = 0; y < 4; y++)
            {
                Console.WriteLine("+------+------+------+------+");
                Console.Write("| ");
                for (int x = 0; x < 4; x++)
                {
                    if (board[x, y].Value == 0)
                    {
                        const string empty = " ";
                        Console.Write(empty.PadRight(4));
                        file.Write("0 ");
                    }
                    else
                    {
                        Console.Write(board[x, y].Value.ToString().PadRight(4));
                        file.Write(board[x, y].Value.ToString() + " ");
                    }
                    Console.Write(" | ");
                }
                file.WriteLine();
                Console.WriteLine();
            }
            Console.WriteLine("+------+------+------+------+\n\n");
        }
    }

    private void WaitKey()
    {
        isMoved = false;
        Console.WriteLine("(W) Up (S) Down (A) Left (D) Right");
        char input;
        //char.TryParse(Console.ReadKey(true).Key.ToString(), out input);
        input = (char)Console.Read();
        input = Char.ToUpper(input);

        switch (input)
        {
            case 'W':
                Move(MoveDirection.Up);
                Console.WriteLine("    UP");
                break;
            case 'A':
                Move(MoveDirection.Left);
                Console.WriteLine("  LEFT");
                break;
            case 'S':
                Move(MoveDirection.Down);
                Console.WriteLine("  DOWN");
                break;
            case 'D':
                Move(MoveDirection.Right);
                Console.WriteLine(" RIGHT");
                break;
        }

        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                board[x, y].IsBlocked = false;
            }
        }
    }

    private void AddTile()
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (board[x, y].Value != 0)
                {
                    continue;
                }
                int a, b;
                do
                {
                    a = rand.Next(0, 4);
                    b = rand.Next(0, 4);
                } while (board[a, b].Value != 0);

                double r = rand.NextDouble();
                board[a, b].Value = r > 0.89f ? 4 : 2;

                if (CanMove())
                {
                    return;
                }
            }
        }
        isDone = true;
    }//здесь юзается CanMove()

    private bool CanMove()
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (board[x, y].Value == 0)
                {
                    return true;
                }
            }
        }

        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (TestAdd(x + 1, y, board[x, y].Value) || TestAdd(x - 1, y, board[x, y].Value) || TestAdd(x, y + 1, board[x, y].Value) || TestAdd(x, y - 1, board[x, y].Value))
                {
                    return true;
                }
            }
        }

        return false;
    }

    private bool TestAdd(int x, int y, int value)
    {
        if (x < 0 || x > 3 || y < 0 || y > 3)
        {
            return false;
        }

        return board[x, y].Value == value;
    }

    private void MoveVertically(int x, int y, int d)
    {
        if (board[x, y + d].Value != 0 && board[x, y + d].Value == board[x, y].Value && !board[x, y].IsBlocked && !board[x, y + d].IsBlocked)
        {
            board[x, y].Value = 0;
            board[x, y + d].Value *= 2;
            score += board[x, y + d].Value;
            board[x, y + d].IsBlocked = true;
            isMoved = true;
        }
        else if (board[x, y + d].Value == 0
                 && board[x, y].Value != 0)
        {
            board[x, y + d].Value = board[x, y].Value;
            board[x, y].Value = 0;
            isMoved = true;
        }

        if (d > 0)
        {
            if (y + d < 3)
            {
                MoveVertically(x, y + d, 1);
            }
        }
        else
        {
            if (y + d > 0)
            {
                MoveVertically(x, y + d, -1);
            }
        }
    }

    private void MoveHorizontally(int x, int y, int d)
    {
        if (board[x + d, y].Value != 0 && board[x + d, y].Value == board[x, y].Value && !board[x + d, y].IsBlocked && !board[x, y].IsBlocked)
        {
            board[x, y].Value = 0;
            board[x + d, y].Value *= 2;
            score += board[x + d, y].Value;
            board[x + d, y].IsBlocked = true;
            isMoved = true;
        }
        else if (board[x + d, y].Value == 0
                 && board[x, y].Value != 0)
        {
            board[x + d, y].Value = board[x, y].Value;
            board[x, y].Value = 0;
            isMoved = true;
        }

        if (d > 0)
        {
            if (x + d < 3)
            {
                MoveHorizontally(x + d, y, 1);
            }
        }
        else
        {
            if (x + d > 0)
            {
                MoveHorizontally(x + d, y, -1);
            }
        }
    }

    private void Move(MoveDirection direction)
    {
        switch (direction)
        {
            case MoveDirection.Up:
                for (int x = 0; x < 4; x++)
                {
                    int y = 1;
                    while (y < 4)
                    {
                        if (board[x, y].Value != 0)
                        {
                            MoveVertically(x, y, -1);
                        }

                        y++;
                    }
                }

                break;
            case MoveDirection.Down:
                for (int x = 0; x < 4; x++)
                {
                    int y = 2;
                    while (y >= 0)
                    {
                        if (board[x, y].Value != 0)
                        {
                            MoveVertically(x, y, 1);
                        }

                        y--;
                    }
                }

                break;
            case MoveDirection.Left:
                for (int y = 0; y < 4; y++)
                {
                    int x = 1;
                    while (x < 4)
                    {
                        if (board[x, y].Value != 0)
                        {
                            MoveHorizontally(x, y, -1);
                        }

                        x++;
                    }
                }

                break;
            case MoveDirection.Right:
                for (int y = 0; y < 4; y++)
                {
                    int x = 2;
                    while (x >= 0)
                    {
                        if (board[x, y].Value != 0)
                        {
                            MoveHorizontally(x, y, 1);
                        }

                        x--;
                    }
                }

                break;
        }
    }
}
