using FigaroLib.Kernel.Debug;
using FigaroLib.RPG.Battle;
using FigaroLib.RPG.Factory;
using FigaroLib.RPG.Data;
using FigaroLib.RPG.GameFlow;
using FigaroLib.RPG.Scripting;
using FigaroLib.RPG;

using System;
 
namespace FigaroLib
{
    public class Fi
    {
        #region members

        public static LoggingSystem logs = new LoggingSystem();
        public static DataSystem data = new DataSystem();
        public static BattleSystem battle = new BattleSystem();
        public static ScriptingSystem scripts = new ScriptingSystem();

        public static FactorySystem factories = new FactorySystem(); //Creo que esto ssealed tiene que borrar
        public static GameFlowSystem flow = new GameFlowSystem();

        public static Random random = new Random();

        #endregion


        public static void startEngine()
        {
            logs.start();
            data.start();
            factories.start();
            scripts.start();

            battle.start();
            flow.start();

            logs.logMessage("Figaro engine started", LoggingSystem.LogLevel.Info);
        }
    }
}
