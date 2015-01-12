using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Data;

using System.Collections.Generic;
using System;


namespace FigaroLib.Controller
{
    public class BattleScreenGuiHelper
    {
        #region members

        #endregion

        public List<MoveData> queryPokemonMoveData(Pokemon p)
        {
            List<MoveData> moveList = new List<MoveData>();
            MoveData moveData;

            foreach (int moveId in p.moves.Keys)
            {
                moveData = Fi.data.getMoveData(moveId);
                moveList.Add(moveData);
            }

            return moveList;
        }
    }
}
