using System;
using System.Threading;
using System.IO;

namespace lab1CS
{
    enum MoveDirection
    {
        Up,
        Down,
        Left,
        Right
    }
    struct WorthPoints
    {
        public bool canMove;
        public double points;
    }
    class Bot
    {
        private bool isMoved;
        private int sideScore;
        private StreamWriter input;

        private Tile[,] board = new Tile[4, 4];
        private Tile[,] testBoard = new Tile[4, 4];

        public Bot(ref StreamWriter streamInput)
        {
            isMoved = true;
            input = streamInput;
            InitializeBoard();
        }

        private void InitializeBoard()
        {
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    board[x, y] = new Tile();
                    testBoard[x, y] = new Tile();
                }
            }
        }

        public void Loop()
        {
            Thread.Sleep(1000);
            while (CanMove(board))
            {
                using (StreamReader file = new StreamReader(Environment.CurrentDirectory + "\\BoardState.txt"))
                {
                    for (int y = 0; y < 4; y++)
                    {
                        string tmp = file.ReadLine();
                        string[] vals = tmp.Split(' ');
                        for (int x = 0; x < 4; x++)
                            board[x, y].Value = Int32.Parse(vals[x]);
                    }
                }
                //Thread.Sleep(500);
                BotInput();
                Thread.Sleep(1000);
            } 
        }

        private void AddTile(Tile[,] board, int x, int y, int k, out bool possibility)
        {
            if (board[x, y].Value == 0)
            {
                board[x, y].Value = (k + 1) * 2;
                possibility = true;
            }
            else
                possibility = false;
        }

        private void CopyBoards(Tile[,] b1, Tile[,] b2)//копирование b1 в b2
        {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    b1[i, j] = (Tile)b2[i, j].Clone();
        }

        private int FilledTilesCount(Tile[,] board)
        {
            int counter = 0;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (board[i, j].Value != 0)
                        counter++;
            return counter;
        }//считает количество непустых клеток (нулю никогда не равно)

        private void SecondMove(WorthPoints[] worthyness, int n)
        {
            Tile[,] mov2Test = new Tile[4, 4];//нужен для копии testBoard для просмотра на 2 хода вперёд
            Tile[,] tmp = new Tile[4, 4];

            double max = 0, sum_of_max = 0;
            int count = 0;
            bool possibile = true;

            if (isMoved)
            {
                CopyBoards(mov2Test, testBoard);
                CopyBoards(tmp, mov2Test);
                //создать карту событий на каждое движение и рассмотреть сумму(!) выигрышных вариантов
                for (int i = 0; i < 16; i++)//начало карты событий
                {
                    for (int j = 0; j < 2; j++)
                    {
                        AddTile(mov2Test, i / 4, i % 4, j, out possibile);//попеременное добавление клеток 2 и 4 для полноты карты
                        if (!possibile)
                            break;
                        else
                            count++;//считает дважды

                        for (int k = 0; k < 4; k++)
                        {
                            sideScore = 0;
                            switch (k)
                            {
                                case 0: Move(MoveDirection.Down, mov2Test); break;
                                case 1: Move(MoveDirection.Left, mov2Test); break;
                                case 2: Move(MoveDirection.Right, mov2Test); break;
                                default: Move(MoveDirection.Up, mov2Test); break;
                            }
                            if (max < sideScore)
                                max = sideScore;//просмотр максимального профита
                            CopyBoards(mov2Test, tmp);//вернёмся немного назад
                        }

                        if (j == 0)//2
                            max *= 0.89 / FilledTilesCount(mov2Test);
                        else//4
                            max *= 0.11 / FilledTilesCount(mov2Test);
                        sum_of_max += max;
                    }
                    if (possibile)//после очередной свободной клетки и подстановки мы её освобождаем, не задевая остальную доску
                        mov2Test[i / 4, i % 4].Value = 0;
                }
                worthyness[n].points += sum_of_max / count * 2;
            }
            else// вариант, что после такого хода походить уже невозможно
                worthyness[n].canMove = false;
        }

        private char CheckBestDir()
        {
            WorthPoints[] worthyness = new WorthPoints[4];

            for (int i = 0; i < 4; i++)
            {
                CopyBoards(testBoard, board);
                sideScore = 0;
                switch (i)
                {
                    case 0:
                        Move(MoveDirection.Down, testBoard);
                        break;
                    case 1:
                        Move(MoveDirection.Left, testBoard);
                        break;
                    case 2:
                        Move(MoveDirection.Right, testBoard);
                        break;
                    default:
                        Move(MoveDirection.Up, testBoard);
                        break;
                }//изменяется доска _test_board
                worthyness[i].points += (double)sideScore / FilledTilesCount(testBoard);
                SecondMove(worthyness, i);
                worthyness[i].canMove = isMoved;
                isMoved = false;
            }
            //ищем максимально выгодный вариант
            double max = worthyness[0].points;
            int index = 0;
            for (int i = 1; i < 4; i++)
                if (worthyness[i].points >= max && worthyness[i].canMove)//>= это костыль, часто выбирается W D
                {
                    max = worthyness[i].points;
                    index = i;
                }
            switch (index)
            {
                case 0: return 'S';
                case 1: return 'A';
                case 2: return 'D';
                default: return 'W';
            }
        }

        private void BotInput()
        {
            isMoved = false;
            char dir = CheckBestDir();

            input.Write(dir);//закинули в перенаправленный поток ввода нужное направление
            
            for (int y = 0; y < 4; y++)//возможно это стоит убрать
            {
                for (int x = 0; x < 4; x++)
                {
                    board[x, y].IsBlocked = false;
                }
            }
        }

        private bool CanMove(Tile[,] board)//есть ли возможные ходы для продолжения игры
        {
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    if (board[x, y].Value == 2048)
                    {
                        return false;
                    }
                }
            }

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
        }//проверка на возможность сложить 2 клетки вместе

        private void MoveVertically(int x, int y, int d, Tile[,] board)
        {
            if (board[x, y + d].Value != 0 && board[x, y + d].Value == board[x, y].Value && !board[x, y].IsBlocked && !board[x, y + d].IsBlocked)
            {
                board[x, y].Value = 0;
                board[x, y + d].Value *= 2;
                sideScore += board[x, y + d].Value;
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
                    MoveVertically(x, y + d, 1, board);
                }
            }
            else
            {
                if (y + d > 0)
                {
                    MoveVertically(x, y + d, -1, board);
                }
            }
        }

        private void MoveHorizontally(int x, int y, int d, Tile[,] board)
        {
            if (board[x + d, y].Value != 0 && board[x + d, y].Value == board[x, y].Value && !board[x + d, y].IsBlocked && !board[x, y].IsBlocked)
            {
                board[x, y].Value = 0;
                board[x + d, y].Value *= 2;
                sideScore += board[x + d, y].Value;
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
                    MoveHorizontally(x + d, y, 1, board);
                }
            }
            else
            {
                if (x + d > 0)
                {
                    MoveHorizontally(x + d, y, -1, board);
                }
            }
        }

        private void Move(MoveDirection direction, Tile[,] board)
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
                                MoveVertically(x, y, -1, board);
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
                                MoveVertically(x, y, 1, board);
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
                                MoveHorizontally(x, y, -1, board);
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
                                MoveHorizontally(x, y, 1, board);
                            }

                            x--;
                        }
                    }

                    break;
            }
        }
    }
}