using FigaroLib.RPG.Battle;
using FigaroLib.RPG.Battle.Combatants;
using FigaroLib.RPG.Characters;

namespace FigaroLib.RPG.Factory
{
    public class OpponentFactory
    {
        #region members
        private PokemonFactory pokemonFactory;
        #endregion

        public OpponentFactory()
        {
            pokemonFactory = new PokemonFactory();
        }

        public ICombatant createWildPokemon(int id,int level)
        {
            Pokemon pokemon = pokemonFactory.createPokemon(id, level);
            return new WildPokemon(pokemon);
        }
    }
}
