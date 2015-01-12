using FigaroLib.RPG.Battle.Combatants;
using FigaroLib.RPG.Battle;
using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Factory;
using FigaroLib.Kernel.Debug;

using System;

namespace FigaroLib.RPG
{

    public class Player : ICombatant
    {
        #region members
        Pokemon testPokemon;
        PokemonFactory pokemonfactory;

        String name;
        #endregion

        public Player()
        {
            pokemonfactory = new PokemonFactory();
            testPokemon = pokemonfactory.createPokemon(25, 10);

            name = "";
        }

        public OpponentType Type
        {
            get { return OpponentType.Player; }
        }

        public String Name
        {
            get { return name; }
        }


        public Pokemon CurrentPokemon
        {
            get { return testPokemon; }
        }

        public IBattleCommand getNextCombatCommand()
        {
            throw new System.NotImplementedException();
        }


        public int AlivePokemons
        {
            get 
            {
                if (testPokemon.hp > 0)
                    return 1;
                return 0;
            }
        }
        public string OpeningMessage
        {
            get 
            {
                fAssert.assert(1 == 2,
                    "Tryring to get an opening message from a player");
                return "";
            }
        }
    }
}
