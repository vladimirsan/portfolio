using FigaroLib.Kernel.Debug;
using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Data;

namespace FigaroLib.RPG.Battle.Commands
{

    public class MoveCommand : IBattleCommand
    {
        #region members
        private Pokemon attacker;
        private Pokemon defender;
        private int moveId;

        private static BattleCalculations battleCalculations = new BattleCalculations();

        #endregion

        public MoveCommand(Pokemon attacker,Pokemon defender,int moveId)
        {
            fAssert.assert(attacker.moves.ContainsKey(moveId),
                "Trying to create a command with an invalid id");

            this.attacker = attacker;
            this.defender = defender;
            this.moveId = moveId;
        }

        public BattleCommandType Type
        {
            get { return BattleCommandType.Attack; }
        }


        public void execute()
        {

            Fi.logs.logMessage("Executing a move command with id " + this.moveId.ToString());

            if (attacker.isParalyzed && Fi.random.Next(100) < 25)
            {
                Fi.battle.messageObservers(BattleObserverMessage.AttackerisParalyzedCantAttack);
                return;
            }

            //PP calculations
            fAssert.assert(attacker.moves[moveId] > 0,"Trying to execute a move without PP");
            attacker.moves[moveId] -= 1; // -1 to PP

            //Initial Accuracy calculations
            MoveData data = Fi.data.getMoveData(moveId);
            int finalAccuracy = calculateFinalAccuracy(data.accuracy);

            //Move-nature calculation
            bool isSpecialMove;
            if (data.typeId == 1 || data.typeId == 10 || data.typeId == 9)
                isSpecialMove = false; //normal, flying, fighting
            else
                isSpecialMove = true;

            //Hit or miss
            if (Fi.random.Next(255) < finalAccuracy)
            {
                int damage;
                //the move hits...straight from the Pokemon rules
                /* First, we'll check if the move is pre-processing or post-processing
                   pre: slash, and karate chop */
                if (moveId == 40 || moveId == 51)
                {
                    Fi.scripts.moves[moveId](attacker, defender);
                    damage = battleCalculations.calculateDamage(attacker, defender, isSpecialMove, moveId);

                    Fi.battle.PhaseDamage = damage;
                    if (damage >= 0)
                    {
                        defender.hp -= damage;
                        if (defender.hp < 0) defender.hp = 0;
                        Fi.battle.messageObservers(BattleObserverMessage.DamageDone);
                    }
                }
                else
                {
                    damage = battleCalculations.calculateDamage(attacker, defender, isSpecialMove, moveId);

                    Fi.battle.PhaseDamage = damage;
                    if (damage >= 0)
                    {
                        defender.hp -= damage;
                        if (defender.hp < 0) defender.hp = 0;
                        Fi.battle.messageObservers(BattleObserverMessage.DamageDone);
                    }
                    Fi.scripts.moves[moveId](attacker, defender);
                }

                if (attacker.isPoisoned)
                {
                    Fi.battle.PhasePoisonDamage = (int)attacker.maxHp / 16;
                    attacker.hp -= (int) attacker.maxHp / 16;
                    if (attacker.hp < 0) attacker.hp = 0;
                    Fi.battle.messageObservers(BattleObserverMessage.AttackerPoisonDamage);
                }
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.MoveMisses);
        }

        /*This function will take into account the accuracy and the evasion of the pokemons * */
        private int calculateFinalAccuracy(float moveAccuracy)
        {
            //First I want to make sure that the values are within the correct bounds
            fAssert.assert(attacker.accuracy >= -6 && attacker.accuracy <= 0,
                "Trying to execute a move with invalid accuracy values");
            fAssert.assert(defender.evasion >= 0 && defender.evasion <= 6,
                "Trying to execute a move with invalid evasion values");

            //these values were taken straight from the Pokemon rules
            switch(attacker.accuracy)
            {
                case -1:
                    moveAccuracy *= 0.75f;
                break;
                case -2:
                    moveAccuracy *= 0.60f;
                break;
                case -3:
                    moveAccuracy *= 0.50f;
                break;
                case -4:
                    moveAccuracy *= 0.43f;
                break;
                case -5:
                    moveAccuracy *= 0.38f;
                break;
                case -6:
                    moveAccuracy *= 0.33f;
                break;
            }

            switch(defender.evasion)
            {
                case 1:
                    moveAccuracy *= 1.75f;
                break;
                case 2:
                    moveAccuracy *= 1.60f;
                break;
                case 3:
                    moveAccuracy *= 1.50f;
                break;
                case 4:
                    moveAccuracy *= 1.43f;
                break;
                case 5:
                    moveAccuracy *= 1.38f;
                break;
                case 6:
                    moveAccuracy *= 1.33f;
                break;
            }

            return (int) (moveAccuracy * 2.56);
        }


        public string getDescription(string pokemonName)
        {
            MoveData data = Fi.data.getMoveData(moveId);
            return pokemonName + " used " + data.name + "!"; 
        }
    }
}
