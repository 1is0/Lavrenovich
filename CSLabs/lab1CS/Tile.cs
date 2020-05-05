using System;

namespace lab1CS
{
    class Tile : ICloneable
    {
        public Tile()
        {
            Value = 0;
            IsBlocked = false;
        }

        public int Value { get; set; }
        public bool IsBlocked { get; set; }

        public object Clone()
        {
            return new Tile { Value = this.Value, IsBlocked = this.IsBlocked };
        }
    }

}
