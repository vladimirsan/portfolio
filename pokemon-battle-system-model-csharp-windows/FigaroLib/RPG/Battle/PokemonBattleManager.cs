using FigaroLib.Kernel.Debug;
using FigaroLib.RPG.Characters; 

namespace FigaroLib.RPG.Battle
{
    public class PokemonBattleManager
    {
        public void resetModifiersAfterBattle(Pokemon p)
        {
            p.attackModifier = 0;
            p.defenseModifier = 0;
            p.speedModifier = 0;
            p.specialModifier = 0;
            p.accuracy = 0;
            p.evasion = 0;

            p.isParalyzed = false;

            p.temporalCriticalHitMultiplier = 1;
            p.specialDefenseMultiplier = 1;
        }

        public void processModifiersAfterTurn(Pokemon p)
        {
            p.temporalCriticalHitMultiplier = 1;
        }

        public void calculateDynamicAttributes(Pokemon p)
        {
            p.battleAttack = calculateADSSModifier(p.staticAttack, p.attackModifier);
            p.battleDefense = calculateADSSModifier(p.staticDefense, p.defenseModifier);
            p.battleSpeed = calculateADSSModifier(p.staticSpeed, p.speedModifier);
            if (p.isParalyzed)
                p.battleSpeed /= 4;

            p.battleSpecial = calculateADSSModifier(p.staticSpecial, p.specialModifier);
        }


        private int calculateADSSModifier(int attribute,int modifier)
        {//Attack, Defense, Speed, Special
            fAssert.assert(modifier >= -6 && modifier <= 6,
                "Modifier is out of bounds");

            float dynamicAttribute = 0;
            float multiplier = 0;

            if (modifier >= 0)
            {
                multiplier = 100 + modifier * 50;
                dynamicAttribute = attribute * (multiplier / 100);
            }
            else
            {
                switch (modifier)
                {
                    case -1:
                        multiplier = 0.677f;
                        break;
                    case -2:
                        multiplier = 0.50f;
                        break;
                    case -3:
                        multiplier = 0.40f;
                        break;
                    case -4:
                        multiplier = 0.333f;
                        break;
                    case -5:
                        multiplier = 0.285f;
                        break;
                    case -6:
                        multiplier = 0.25f;
                        break;
                }
                dynamicAttribute = attribute * multiplier;
                
            }
            return (int) dynamicAttribute;
        }
    }
}
