using FigaroLib.RPG.Battle;
using FigaroLib.Kernel.Debug;

using System;

namespace FigaroLib.RPG.Battle
{
    public interface IBattleCommand
    {
        BattleCommandType Type
        { get; }

        //Right now every command will handle its own errors
        void execute();

        String getDescription(String pokemonName);

    }
}
