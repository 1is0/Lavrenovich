using System;

namespace lab8cs
{
    enum MemoryType { DDR2, DDR3, DDR4 }
    enum Architecture { RISC, CISC }
    abstract class Processor : ALU, IProcessor, IComparable<Processor>
    {
        public int coresAmount { get; private set; }
        public MemoryType memT { get; private set; }
        public double frequency { get; private set; }
        public Additionals adds { get; private set; }
        abstract public string socket{ get; set; }
        abstract public Architecture architecture { get; set; }
        //****************************EVENTS****************************
        delegate void CreateNotify(string msg);
        static event CreateNotify onCreate;
        //****************************METHODS***************************
        public Processor() : base() 
        { 
            coresAmount = 2; 
            memT = MemoryType.DDR2; 
            frequency = 2.7; 
            adds = new Additionals{ L2 = 4, L3 = 18, tp = TechProcess.nm18};
            if (onCreate == null)
                onCreate += (string msg) => Console.WriteLine(msg);
            onCreate("Processor() constructor called.");
        }
        public Processor(string serial, int opPerSec, int version, 
                        ALUType type, int cores, MemoryType mt, 
                        double freq, Additionals ad) : base(serial, opPerSec, version, type) 
        {
            coresAmount = cores;
            memT = mt;
            frequency = freq;
            adds = ad;
            if (onCreate == null)
                onCreate += (string msg) => Console.WriteLine(msg);
            onCreate("Processor(args) constructor called.");
        }
        public override string ToString()
        {
            return base.ToString() + "\nCores amount: " + coresAmount.ToString() + "\nMemory type: " + memT.ToString() 
                + "\nFrequency(MHz): " + frequency.ToString() + adds.ToString();
        }
        public int CompareTo(Processor rhs)
        {
            return coresAmount.CompareTo(rhs.coresAmount);
        }
        public double EfficiencyCoef()
        {
            double coef = 1;
            coef *= (adds.L2 + adds.L3 * 0.5 + (double)adds.tp * 0.33);
            if (memT == MemoryType.DDR4)
                coef *= 3;
            else if (memT == MemoryType.DDR3)
                coef *= 2;
            coef += coresAmount * frequency;
            return coef;
        }
    }
}
