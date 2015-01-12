using FigaroLib.Kernel.Debug;
using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Data;
using System;

namespace FigaroLib.RPG.Battle
{

    public class BattleCalculations
    {
        #region members
        Random random;
        TypeManager typeManager;
        #endregion

        public BattleCalculations()
        {
            random = new Random();
            typeManager = new TypeManager();
        }

        public int calculateDamage(Pokemon a, Pokemon d,bool isSpecialAttack,int moveId)
        {
          //Damage = ((((Level * 0.4) + 2) * A * B / 50  / D) + 2) * M * R / 255

            MoveData data = Fi.data.getMoveData(moveId);

            if (data.basePower == -1)
                return -1;

            int damage = 0;
            int attackValue = isSpecialAttack ? a.battleSpecial : a.battleAttack;
            int defenseValue = isSpecialAttack ? d.battleSpecial : d.battleDefense;
            int randomValue = random.Next(217,255);
            TypeManager.TypeRelation relation = new TypeManager.TypeRelation();

            float multiplier = typeManager.calculateTypeMultiplier(moveId,a, d, ref relation);
            Fi.logs.logMessage("Multiplier: " + multiplier.ToString());

            if (isCriticalHit(a))
            {
                Fi.logs.logMessage("Critical Hit!!");
                Fi.battle.criticalHit = true;
                multiplier *= 2;
            }


            damage = (int) Math.Round(
                (((a.level * 0.4) + 2) * attackValue * data.basePower / 50.0 / defenseValue + 2.0) * 1.0 *
                multiplier* randomValue / 255.0
            );
            Fi.logs.logMessage("Damage Calculation: " + damage.ToString());
            Fi.battle.PhaseTypeRelation = relation;

            switch(relation)
            {
                case TypeManager.TypeRelation.Bad:
                    Fi.logs.logMessage("Not Very Effective");
                    break;
                case TypeManager.TypeRelation.Good:
                    Fi.logs.logMessage("Super Effective");
                    break;
                case TypeManager.TypeRelation.Neutral:
                    Fi.logs.logMessage("Neutral Attack");
                    break;
            }

            fAssert.assert(damage >= 0, 
                "Negative damace calculation where it should have been positive");
            return damage;
        }

        private bool isCriticalHit(Pokemon p)
        {
            int chances = calculateCriticalChangeValue(p);

            if (chances >= random.Next(0, 100))
            {
                return true;
            }
            return false;
        }

        public int calculateCriticalChangeValue(Pokemon p)
        {
            PokemonData pokeData = Fi.data.getPokemonData(p.id);

            int chances = pokeData.baseSpeed / 512;

            if (chances < 0)
                chances = 0;
            if (chances > 100)
                chances = 100;

            Fi.logs.logMessage("Critical Hit Value: " + chances.ToString());

            return chances * p.temporalCriticalHitMultiplier;
        }
    }
}
