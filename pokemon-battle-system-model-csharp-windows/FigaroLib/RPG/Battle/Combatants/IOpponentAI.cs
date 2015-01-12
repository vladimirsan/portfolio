namespace FigaroLib.RPG.Battle.Combatants
{
    public interface IOpponentAI
    {
        BattleCommandType getNextAction();
    }
}
