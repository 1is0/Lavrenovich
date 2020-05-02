using System;

namespace lab7CS
{
    class Fraction: IComparable, IEquatable<Fraction>
    {
        public int n { get; set; }
        public uint m { get; set; }
        public static explicit operator double(Fraction f)
        {
            return f.n / (double)f.m;
        }
        public static implicit operator int(Fraction f)
        {
            return (int)(double)f;
        }
        //********************CONSTRUCTORS***************************
        public Fraction()
        {
            n = 1;
            m = 1;
        }
        public Fraction(string s, out bool success)
        {
            int n = 1, m = 1;
            success = true;
            try
            {
                foreach (char c in s)
                    if ((c < '0' || c > '9') && c != '/' && c != '-')
                    {
                        success = false;
                        throw new Exception("Invalid string format!");
                    }
                int foundInd = s.IndexOf("/");//Если ничего не находит, то возвращает -1
                if (foundInd == -1)
                {
                    success = false;
                    throw new Exception("No fractions found!");
                }
                string ns, ms;
                ns = s.Substring(0, foundInd);
                ms = s.Substring(foundInd + 1, s.Length - foundInd - 1);
                if (ns == "" || ms == "")
                {
                    success = false;
                    throw new Exception("Can't find n or m!");
                }
                if (!int.TryParse(ns, out n) || !int.TryParse(ms, out m))
                {
                    success = false;
                    throw new Exception("Invalid string format!");
                }
                if (m == 0)
                {
                    success = false;
                    throw new Exception("Division by zero is not allowed.");
                }
                if ((n < 0 && m < 0) || (n > 0 && m < 0))
                {
                    n *= -1;
                    m *= -1;
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            finally
            {
                this.n = n;
                this.m = (uint)m;
                this.Reduce();
            }
        }
        public Fraction(int n, uint m)
        {
            this.n = n;
            this.m = m;
            this.Reduce();
        }
        public Fraction(double d)
        {
            int n = 1, m = 1;
            if (d < 0)
            {
                n *= -1;
                d *= -1;
            }
            int pow_10 = -1;
            
            if (d % 10 != 0)
            {
                while (d % 10 != 0 || Math.Abs(d) < 1)
                {
                    d *= 10;
                    pow_10++;
                }
                d /= 10;
                n = (int)d;
                m = (int)Math.Pow(10, pow_10);
            }
            else
            {
                n = (int)d;
                m = 1;
            }
            this.n = n;
            this.m = (uint)m;
        }
        //********************MATH OPERATORS*************************
        public static Fraction operator +(Fraction lhs, Fraction rhs)
        {
            if (lhs.n == 0)
                return new Fraction(rhs.n, rhs.m);
            if (rhs.n == 0)
                return new Fraction(lhs.n, lhs.m);


            long lcm = LCM((int)lhs.m, (int)rhs.m);

            lhs.n *= (int)(lcm / lhs.m);
            rhs.n *= (int)(lcm / rhs.m);
            lhs.m *= (uint)(lcm / lhs.m);
            rhs.m *= (uint)(lcm / rhs.m);

            Fraction tmp = new Fraction(lhs.n + rhs.n, lhs.m);
            rhs.Reduce();
            lhs.Reduce();
            return tmp;
        }
        public static Fraction operator -(Fraction lhs, Fraction rhs)
        {
            if (lhs.n == 0)
                return new Fraction(rhs.n * -1, rhs.m);
            if (rhs.n == 0)
                return new Fraction(lhs.n, lhs.m);

            long lcm = LCM((int)lhs.m, (int)rhs.m);

            lhs.n *= (int)(lcm / lhs.m);
            rhs.n *= (int)(lcm / rhs.m);
            lhs.m *= (uint)(lcm / lhs.m);
            rhs.m *= (uint)(lcm / rhs.m);

            Fraction tmp = new Fraction(lhs.n - rhs.n, lhs.m);
            rhs.Reduce();
            lhs.Reduce();
            return tmp;
        }
        public static Fraction operator *(Fraction lhs, Fraction rhs)
        {
            Fraction tmp = new Fraction(lhs.n * rhs.n, lhs.m * rhs.m);
            tmp.Reduce();
            return tmp;
        }
        public static Fraction operator /(Fraction lhs, Fraction rhs)
        {
            if (rhs.n == 0)
                throw new DivideByZeroException("Can't divide by zero!");

            Fraction tmp;
            if (rhs.n < 0)
                tmp = new Fraction(-1 * lhs.n * (int)rhs.m, lhs.m * (uint)(rhs.n * -1));
            else
                tmp = new Fraction(lhs.n * (int)rhs.m, lhs.m * (uint)rhs.n);
            tmp.Reduce();
            return tmp;
        }
        //*****************COMPARING OPERATORS***********************
        public static bool operator <(Fraction lhs, Fraction rhs)
        {
            if ((double)lhs < (double)rhs)
                return true;
            return false;
        }
        public static bool operator >(Fraction lhs, Fraction rhs)
        {
            if ((double)lhs > (double)rhs)
                return true;
            return false;
        }
        public static bool operator <=(Fraction lhs, Fraction rhs)
        {
            if ((double)lhs <= (double)rhs)
                return true;
            return false;
        }
        public static bool operator >=(Fraction lhs, Fraction rhs)
        {
            if ((double)lhs >= (double)rhs)
                return true;
            return false;
        }
        public override bool Equals(object other)
        {
            if (other is Fraction)
            {
                return base.Equals((Fraction)other);
            }
            return false;
        }
        public bool Equals(Fraction rhs)
        {
            if ((double)this == (double)rhs)
                return true;
            else
                return false;
        }
        int IComparable.CompareTo(object obj)
        {
            if ((double)this > (double)((Fraction)obj)) return 1;
            else if ((double)this < (double)((Fraction)obj)) return -1;
            else return 0;
        }
        public override int GetHashCode()
        {
            return this.ToString().GetHashCode();
        }
        //*****************OTHER METHODS***************************
        private void Reduce()
        {
            if (n == 0)
            {
                m = 1;
                return;
            }
            int reductor = GCD(Math.Abs(n), (int)m);
            n /= reductor;
            m /= (uint)reductor;
        }
        private static int GCD(int a, int b)
        {
            return (b != 0) ? GCD(b, a % b) : a;
        }
        private static long LCM(int a, int b)
        {
            return (long)a / (long)GCD(a, b) * b;
        }
        public Fraction GetRest()
        {
            Fraction tmp = new Fraction();
            tmp.n = Math.Abs(this.n);
            tmp.m = this.m;
            int wholePart = tmp;
            tmp.n -= wholePart * (int)tmp.m;
            tmp.Reduce();
            return tmp;
        }
        public string NormalView()
        {
            return n.ToString() + "/" + m.ToString();
        }
        public override string ToString()
        {
            int wholePart = this;
            Fraction rest = this.GetRest();//при нуле всё так себе 
            string toReturn = wholePart.ToString();
            if (wholePart < 0)
                toReturn += " - " + rest.n.ToString() + "/" + rest.m.ToString();
            else if (wholePart == 0)
            {
                if (this.n < 0)
                    toReturn += " - " + rest.n.ToString() + "/" + rest.m.ToString();
                else
                    toReturn += " + " + rest.n.ToString() + "/" + rest.m.ToString();
            }
            else
                toReturn += " + " + rest.n.ToString() + "/" + rest.m.ToString();
            return toReturn; 
        }
    }
}
