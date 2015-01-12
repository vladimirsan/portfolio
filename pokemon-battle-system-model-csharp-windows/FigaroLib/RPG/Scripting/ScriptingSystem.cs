using FigaroLib.RPG.Battle.Combatants;
using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Battle;

using System;
using System.Collections.Generic;

namespace FigaroLib.RPG.Scripting
{

    public partial class ScriptingSystem
    {
        #region members
        public delegate void ItemDelegate();
        public delegate void MoveDelegate(Pokemon attacker,Pokemon defender);


        private Dictionary<int, ItemDelegate> itemDelegates;
        public Dictionary<int, MoveDelegate> moves;
        private PokemonBattleManager pokemonManager;
        #endregion

        public ScriptingSystem()
        { }

        public void start()
        {
            itemDelegates = new Dictionary<int, ItemDelegate>();
            moves = new Dictionary<int, MoveDelegate>();
            pokemonManager = new PokemonBattleManager();

            loadItemDelegates();
            loadMoveDelegates();
        }
    }
}
