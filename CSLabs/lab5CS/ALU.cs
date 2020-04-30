using System;

namespace lab5cs
{
    enum ALUType { Decimal, Fixed, Float }
    class ALU
    {
        private static Random rand = new Random();
        public int id { get; private set; }//unique id
        public string serial { get; private set; }//serial
        public int opPerSec { get; private set; }
        private int version;
        private ALUType type;
        //***************************************METHODS******************************************
        public ALU()
        {
            id = MakeID();
            serial = "XXXXXXXXX";
            opPerSec = 9000000;
            version = 0;
            type = ALUType.Decimal;
        }
        public ALU(string serial, int opPerSec, int version, ALUType type) : this()
        {
            this.serial = serial;
            this.opPerSec = opPerSec;
            this.version = version;
            this.type = type;
        }
        public int this[int offset]
        {
            get
            {
                try
                {
                    switch (offset)
                    {
                        case 0: return id;
                        case 1: return opPerSec;
                        case 2: return version;
                        default: throw new IndexOutOfRangeException(); 
                    }
                }
                catch (IndexOutOfRangeException e)
                {
                    Console.WriteLine($"Error {e.Message}");
                    return -1;
                }
            }
            set
            {
                try
                {
                    switch (offset)
                    {
                        case 0: id = value; break;
                        case 1: opPerSec = value; break;
                        case 2: version = value; break;
                        default: throw new IndexOutOfRangeException();
                    }
                }
                catch (IndexOutOfRangeException e)
                {
                    Console.WriteLine($"Error {e.Message}");
                }
            }
        }
        public override string ToString()
        {
            return "ID: " + id.ToString() + "\nSerial: " + serial + "\nVersion: " + version.ToString() 
                + "\nOperations per second: " + opPerSec.ToString() + "\nALU Type: " + type.ToString();
        }
        private static int MakeID()
        {
            return 1 + rand.Next(10000);
        }
        public int GetVersion() { return version; }
        public new ALUType GetType() { return type; }
        public void SetVersion(int ver) { version = ver; }
        public void SetType(ALUType t) { type = t; }
    }
}
