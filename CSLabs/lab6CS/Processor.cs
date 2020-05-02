
namespace lab5cs
{
    enum MemoryType { DDR2, DDR3, DDR4 }
    enum Architecture { RISC, CISC }
    abstract class Processor : ALU
    {
        public int coresAmount { get; private set; }
        public MemoryType memT { get; private set; }
        public double frequency { get; private set; }
        public Additionals adds { get; private set; }
        abstract public string socket{ get; set; }
        abstract public Architecture architecture { get; set; }
        //****************************METHODS***************************
        public Processor() : base() { coresAmount = 2; memT = MemoryType.DDR2; frequency = 2.7; adds = new Additionals{ L2 = 4, L3 = 18, tp = TechProcess.nm18}; }
        public Processor(string serial, int opPerSec, int version, 
                        ALUType type, int cores, MemoryType mt, 
                        double freq, Additionals ad) : base(serial, opPerSec, version, type) 
        {
            coresAmount = cores;
            memT = mt;
            frequency = freq;
            adds = ad;
        }
        public override string ToString()
        {
            return base.ToString() + "\nCores amount: " + coresAmount.ToString() + "\nMemory type: " + memT.ToString() 
                + "\nFrequency(MHz): " + frequency.ToString() + adds.ToString();
        }
    }
}
