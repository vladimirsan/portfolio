using FigaroLib.RPG.Data;
using FigaroLib.RPG.Characters;

using FigaroLib.Kernel.Debug;

namespace FigaroLib.RPG.Factory
{
    public class PokemonFactory
    {
        #region members
        private LevelManager levelManager;
        private MoveLearningManager moveLearningManager;

        #endregion

        public PokemonFactory()
        {
            levelManager = new LevelManager();
            moveLearningManager = new MoveLearningManager();
        }

        public Pokemon createPokemon(int id,int level)
        {
            fAssert.assert(level > 0, 
                "Tryng to create a new pokemon with level below 0");

            PokemonData data = Fi.data.getPokemonData(id);
            Pokemon p = new Pokemon();
            p.id = id;
            p.name = data.name;
            p.level = level;

            p.type1 = (PokemonType) data.typeId1;
            p.type2 = (PokemonType) data.typeId2;

            levelManager.performNewLevelStatCalculations(p);
            p.hp = p.maxHp;

            for (int i = 0; i <= p.level; i++)
            {
                moveLearningManager.learnMovesPerLevel(p,i);
            }
            //I'll use -1 to indicate that the pokemon wal built from a factory
            p.exp = -1;
            return p;
        }
    }
}
