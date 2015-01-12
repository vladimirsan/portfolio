using FigaroLib.RPG.Characters;

using System;


namespace FigaroLib.RPG.Battle.Combatants
{
    public interface ICombatant
    {
        OpponentType Type
        { get; } 

        Pokemon CurrentPokemon
        { get; }

        String Name
        { get; }

        String OpeningMessage
        {
            get;
        }

        int AlivePokemons
        { get; }

        IBattleCommand getNextCombatCommand();
    }
}
