using FigaroLib.RPG.Battle;
using FigaroLib.RPG.Battle.Combatants;
using FigaroLib.Kernel.Debug;

using System;

namespace FigaroLib.RPG.Battle.Commands
{
    public class RunCommand : IBattleCommand
    {
        #region members     
        private ICombatant caller;
        private static Random random = new Random();
        #endregion

        /* I could add another constructor to this command (to calculate the opponent)
         * but it's not required now */
        public RunCommand(ICombatant caller)
        {
            fAssert.assert(caller.Type == OpponentType.Player ||
                caller.Type == OpponentType.WildPokemon,
                "Trying to run with an opponent trainer");
            this.caller = caller;
        }

        public BattleCommandType Type
        {
            get { return BattleCommandType.Run; }
        }

        public void execute()
        {
            Fi.logs.logMessage("Executing a run command");

            if (caller.Type == OpponentType.Player)
            {
                int a = caller.CurrentPokemon.battleSpeed;
                int b = (Fi.battle.Opponent.CurrentPokemon.battleSpeed / 4) % 256;
                Fi.battle.countPlayerEscapeAttempt();
                int c = Fi.battle.PlayerEscapeAttempts;

                int f = ((a * 32) / b) + 30 * c;

                if (f > 255)
                    Fi.battle.messageObservers(BattleObserverMessage.PlayerRunSuccesful);
                else
                {
                    int randomValue = random.Next(0, 255);
                    if (randomValue < f)
                        Fi.battle.messageObservers(BattleObserverMessage.PlayerRunSuccesful);
                    else
                        Fi.battle.messageObservers(BattleObserverMessage.PlayerRunFailed);
                }
            }
            else if (caller.Type == OpponentType.WildPokemon)
            {
                /* Right now if a wild pokemon want's to run...it can't do that */
                Fi.battle.messageObservers(BattleObserverMessage.PokemonRunFailed);
            }
        }

        public string getDescription(string pokemonName)
        {
            String description = pokemonName + " tried to run away...";
            return description;
        }
    }
}
