using FigaroLib.RPG.Data;
using System;


namespace FigaroLib.RPG.Characters
{

    public class LevelManager
    {
        #region members

        //No me gusta trabajar mucho con numeros fraccionarios pero como que nos llevo judas
        MoveLearningManager moveLearningManager;

        #endregion

        public LevelManager()
        {
            moveLearningManager = new MoveLearningManager();
        }

        public bool isNewLevelAvailable(Pokemon c)
        {
            //This is the level the character should have according to its experience
            int calculatedLevel = floatToInt((System.Math.Pow((double)c.exp, 1.0 / 3.0)));

            if (calculatedLevel > c.level)
            {
                return true;
            }
            return false;
        }

        public void oneLevelUp(Pokemon p)
        {
            p.level++;
            performNewLevelStatCalculations(p);
            moveLearningManager.learnMovesPerLevel(p,p.level);
        }

        public void performNewLevelStatCalculations(Pokemon p)
        {
            PokemonData baseStats = Fi.data.getPokemonData(p.id);
            /*! I'll be ignoring the DVs for now. It seems like too much complexity for 
             * almost no benefit */

            //HP = (Base Stat + DV + 50) * Level / 50 + 10 + extra points;
            p.maxHp = floatToInt((((baseStats.baseHp + 50.0) * p.level) / 50.0) + 10.0);

           // Other Stat = (Base Stat + DV) * Level / 50 + 5 + extra points
            p.staticAttack = floatToInt((baseStats.baseAttack) * p.level / 50.0 + 5.0);
            p.staticDefense = floatToInt((baseStats.baseDefense) * p.level / 50.0 + 5.0);
            p.staticSpecial = floatToInt((baseStats.baseSpecial) * p.level / 50.0 + 5.0);
            p.staticSpeed = floatToInt((baseStats.baseSpeed) * p.level / 50.0 + 5.0);
        }

        private int floatToInt(double value)
        {
            return (int) Math.Round(value);
        }

    }
}
