using FigaroLib.RPG.Battle.Combatants;
using FigaroLib.RPG.Battle.Commands;

using FigaroLib.Kernel.Debug;

using System;

namespace FigaroLib.RPG.Battle
{
    public class BattleSystem
    {
        #region members  

        private ICombatant opponent;
        private ICombatant player;
        public ICombatant Opponent
        {
            get { return opponent; }
        }

        private IBattleCommand oppCommand;
        private IBattleObserver observer;

        private IBattleCommand playerCommand;


        private int escapeAttemptCounter;

        public int PlayerEscapeAttempts
        {
            get { return escapeAttemptCounter; }
        }

        public bool DefenderFlinched
        {
            get;
            set;
        }

        public int PhaseDamage { set; get; }
        public int PhasePoisonDamage { set; get; }
        public bool criticalHit { set; get; }

        public TypeManager.TypeRelation PhaseTypeRelation { get; set; }

        public enum BattleState
        {
            Inactive,
            BattleSetUpComplete,
            TurnSetUpComplete,
            PhaseAComplete,
            TurnComplete
        }
        private BattleState state;

        public BattleState State
        {
            get{return state;}
        }

        private bool playerFirst;

        public bool WasLastActionByPlayer
        {
            get;
            private set;
        }

        private PokemonBattleManager pokemonBattleManager;
        #endregion

        public string PlayerCommandDescription
        {
            get
            {
                fAssert.assert(state == BattleState.TurnComplete
                    || state == BattleState.PhaseAComplete,
                    "Trying to read a command description in an invalid batle status");

                return playerCommand.getDescription(player.CurrentPokemon.name);
            }
        }

        public string OponentCommandDescription
        {
            get
            {
                fAssert.assert(state == BattleState.TurnComplete
                    || state == BattleState.PhaseAComplete,
                    "Trying to read a command description in an invalid batle status");

                return oppCommand.getDescription("Enemy " + opponent.CurrentPokemon.name);
            }
        }

        public void start()
        {
            observer = null;
            pokemonBattleManager = new PokemonBattleManager();
            state = BattleState.Inactive;
        }

        public void countPlayerEscapeAttempt()
        {
            escapeAttemptCounter++;
        }

        public void setUpBattle(ICombatant opponent)
        {
            fAssert.assert(state == BattleState.Inactive,
                "Trying to set up a battle in an invalid state");

            this.opponent = opponent;
            this.player = Fi.flow.player;
            state = BattleState.BattleSetUpComplete;
            escapeAttemptCounter = 0;
            //sospecho que aca me falta resetear al player

            Fi.logs.logMessage("Battle set-up");

        }

        public void messageObservers(BattleObserverMessage message)
        {
            if (observer != null)
                observer.enqueueMessage(message);
        }

        public void registerObserver(IBattleObserver observer)
        {
            this.observer = observer;
        }

        public void setUpTurnPlayerMoveCommand(int moveId)
        {
            //I don't need to check for moveId integrity here, for it's done in the command
            MoveCommand command = new MoveCommand(
                player.CurrentPokemon, Opponent.CurrentPokemon, moveId);
            setUpTurn(command);
        }

        private void setUpTurn(IBattleCommand playerCommand)
        {
            fAssert.assert(state == BattleState.BattleSetUpComplete ||
                state == BattleState.TurnComplete,
                "Trying to set up a turn in an invalid state");

            this.playerCommand = playerCommand;
            oppCommand = opponent.getNextCombatCommand();

            pokemonBattleManager.calculateDynamicAttributes(player.CurrentPokemon);
            pokemonBattleManager.calculateDynamicAttributes(opponent.CurrentPokemon);

            state = BattleState.TurnSetUpComplete;

            Fi.logs.logMessage("Turn set-up");
        }

        public bool usePhaseACalculations()
        {
            fAssert.assert(state == BattleState.PhaseAComplete || 
                state == BattleState.TurnComplete,
                "Trying to ask for phase information in an invalid state");

            if (state == BattleState.PhaseAComplete)
                return true;
            return false;
        }


        public void executePhaseA()
        {
            fAssert.assert(state == BattleState.TurnSetUpComplete,
                "Trying  to execute phase A in an invalid state");

            DefenderFlinched = false; //Set up this to make sure it's false

            playerFirst = calculateIsPlayerFirst(playerCommand);
            if (playerFirst)
            {
                messageObservers(BattleObserverMessage.ShowPlayerCommand);
                playerCommand.execute();
                WasLastActionByPlayer = true;
            }
            else
            {
                messageObservers(BattleObserverMessage.ShowComputerCommand);
                oppCommand.execute();
                WasLastActionByPlayer = false;
            }

            checkForDefeatedCombatant();

            messageObservers(BattleObserverMessage.PhaseADone);
            Fi.logs.logMessage("Phase A executed");
            state = BattleState.PhaseAComplete;
        }

        public void executePhaseB()
        {
            fAssert.assert(state == BattleState.PhaseAComplete,
                "Trying to execute phase A in an invalid state");

            if (DefenderFlinched == false)
            {
                playerFirst = calculateIsPlayerFirst(playerCommand);
                if (playerFirst)
                {
                    messageObservers(BattleObserverMessage.ShowComputerCommand);
                    oppCommand.execute();
                    WasLastActionByPlayer = false;
                }
                else
                {
                    messageObservers(BattleObserverMessage.ShowPlayerCommand);
                    playerCommand.execute();
                    WasLastActionByPlayer = false;
                }
            }

            checkForDefeatedCombatant();

            messageObservers(BattleObserverMessage.PhaseBDone);
            Fi.logs.logMessage("Phase B executed");
            state = BattleState.TurnComplete; 
        }

        public void checkForDefeatedCombatant()
        {
            //! Aca eventualmente voy a tener que programar mas acciones para cada caso
            fAssert.assert(player.CurrentPokemon.hp >= 0,
                "Trying to work with a pokemon with negative health");
            fAssert.assert(opponent.CurrentPokemon.hp >= 0,
                "Trying to work with a pokemon with negative health");

            if (player.CurrentPokemon.hp == 0)
            {
                if(player.AlivePokemons > 0)
                    messageObservers(BattleObserverMessage.PlayerPokemonDefeated);
                else
                    messageObservers(BattleObserverMessage.PlayerDefeated);
            }

            if (opponent.CurrentPokemon.hp == 0)
            {
                if (opponent.Type == OpponentType.WildPokemon)
                {
                    messageObservers(BattleObserverMessage.WildPokemonDefeated);
                }
                else
                {
                    if(opponent.AlivePokemons > 0)
                        messageObservers(BattleObserverMessage.TrainerPokemonDefeated);
                    else
                        messageObservers(BattleObserverMessage.TrainerDefeated);
                }
            }
        }

        public bool isPlayerFirst()
        {
            return playerFirst;
        }

        private bool calculateIsPlayerFirst(IBattleCommand playerCommand)
        {
            if (playerCommand.Type != BattleCommandType.Attack)
            {
                //playerCommand is run, pokechange, or item and has priority
                return true;
            }
            else //player is attacking
            {
                if (oppCommand.Type != BattleCommandType.Attack)
                {
                    //oppCommand is run,pokeChange,item and has priority
                    return false;
                }
                else //both are attacking
                {
                    //!add priority attack check
                    if (player.CurrentPokemon.battleSpeed > 
                        opponent.CurrentPokemon.battleSpeed)
                        return true;
                    else
                        return false;
                }
            }
        }
    }
}
