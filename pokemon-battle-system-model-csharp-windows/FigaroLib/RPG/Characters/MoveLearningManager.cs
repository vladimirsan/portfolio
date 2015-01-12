using FigaroLib.RPG.Data;
using FigaroLib.Kernel.Debug;

using System.Collections.Generic;

namespace FigaroLib.RPG.Characters
{

    public class MoveLearningManager
    {
        #region members

        #endregion
        
        public void learnMovesPerLevel(Pokemon p,int level)
        {
            List<int> newMoves = Fi.data.getPokemonMovesPerLevel(p.id, level);

            if (newMoves.Count > 0)
            {
                foreach (int move in newMoves)
                {
                    fAssert.assert(!p.moves.ContainsKey(move),
                        "Trying to learn a move twice");

                    MoveData data = Fi.data.getMoveData(move);
                    p.moves.Add(move, data.pp);
                }
            }
        }
    }
}
