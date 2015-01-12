using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Battle.Commands;

using System;

namespace FigaroLib.RPG.Battle.Combatants
{

    public class WildPokemon : ICombatant
    {
        #region members
        private Pokemon pokemon;
        #endregion

        public WildPokemon(Pokemon p)
        {
            this.pokemon = p;
        }

        public OpponentType Type
        {
            get { return OpponentType.WildPokemon; }
        }

        public String Name
        {
            get { return pokemon.name; }
        }

        public Characters.Pokemon CurrentPokemon
        {
            get { return pokemon; }
        }

        public IBattleCommand getNextCombatCommand()
        {
            return new RunCommand(this);
        }

        public int AlivePokemons
        {
            get 
            {
                if (pokemon.hp > 0)
                    return 1;
                return 0;
            }
        }

        public string OpeningMessage
        {
            get { return "A wild " + Name + "\n\n\nappeared!"; }
        }
    }
}
