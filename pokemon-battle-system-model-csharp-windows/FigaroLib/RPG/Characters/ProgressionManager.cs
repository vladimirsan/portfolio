using FigaroLib.Kernel.Debug; 

namespace FigaroLib.RPG.Characters
{
    public class ProgressionManager
    {
        #region members

            LevelManager levelManager;

        #endregion

        public ProgressionManager()
        {
            levelManager = new LevelManager();
        }
        
        public void addExp(Pokemon c,int exp)
        {
            fAssert.assert(exp > 0,"Experience should be bigger than 0");

            c.exp += exp;

            while (levelManager.isNewLevelAvailable(c))
            {
                levelManager.oneLevelUp(c);
            }
        }
    }
}
