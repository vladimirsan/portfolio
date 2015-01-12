namespace FigaroLib.RPG.Factory
{

    public class FactorySystem
    {
        #region members
        public OpponentFactory opponentFactory;
        #endregion

        public void start()
        {
            opponentFactory = new OpponentFactory(); 
        }
    }
}
