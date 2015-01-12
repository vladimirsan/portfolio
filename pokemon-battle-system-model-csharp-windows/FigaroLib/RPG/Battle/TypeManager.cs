using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Data;

using System.Collections.Generic;

namespace FigaroLib.RPG.Battle
{
    public class TypeManager
    {
        public enum TypeRelation
        {
            Null,
            Neutral,
            Good,
            Bad
        }

        #region members

        #endregion

        public TypeManager()
        {
            fillTypeRelationDictionary();
        }

        private void fillTypeRelationDictionary()
        {
        }

        public float calculateTypeMultiplier(int moveId,
            Pokemon a, Pokemon d,ref TypeRelation relation)
        {
            relation = TypeRelation.Null;

            float multiplier = 1;
            MoveData moveData = Fi.data.getMoveData(moveId);

            //If the move is the same type as the pokemon
            if ((PokemonType)moveData.typeId == a.type1
            || (PokemonType)moveData.typeId == a.type2)
                multiplier *= 1.5f;

            float typeMultiplier = Fi.data.getTypeRelationMultiplier( a.type1, d.type1);

            if (typeMultiplier == 2)
                relation = TypeRelation.Good;
            else if (typeMultiplier == 0.5)
                relation = TypeRelation.Bad;
            else
                relation = TypeRelation.Neutral;

            if (d.type2 != PokemonType.Null)
            {
                typeMultiplier *= Fi.data.getTypeRelationMultiplier(a.type1, d.type2);
                relation = TypeRelation.Neutral;
            }

            if (a.type2 != PokemonType.Null)
            {
                typeMultiplier *= Fi.data.getTypeRelationMultiplier(a.type2, d.type1);
                relation = TypeRelation.Neutral;
                
                if(d.type2 != PokemonType.Null)
                    typeMultiplier *= Fi.data.getTypeRelationMultiplier(a.type2, d.type2);
            }

            return multiplier;
        }
    }
}
