
namespace lab5cs
{
    enum TechProcess { nm7, nm8, nm12, nm14, nm18, nm22}
    struct Additionals
    {
        public int L2, L3;
        public TechProcess tp;
        //****************************METHODS***************************
        public override string ToString()
        {
            return "\n\n\tAdditionals:\nL2 cache size (MB): " + L2.ToString() + "\nL3 cache size (MB): " + L3.ToString() + "\nTech process: " + tp.ToString();
        }
    }
}
