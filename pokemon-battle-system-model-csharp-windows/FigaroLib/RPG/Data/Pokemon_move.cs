using System;

namespace FigaroLib.RPG.Data
{

    public class Pokemon_move : IComparable<Pokemon_move> 
    {
        #region members

        public int level;
        public int moveId;

        #endregion

        public int CompareTo(Pokemon_move other)
        {
            return level.CompareTo(other.level);
        }
    }
}
