namespace FigaroLib.RPG.Battle
{
    public interface IBattleObserver
    {
        void enqueueMessage(BattleObserverMessage message);
    }
}
