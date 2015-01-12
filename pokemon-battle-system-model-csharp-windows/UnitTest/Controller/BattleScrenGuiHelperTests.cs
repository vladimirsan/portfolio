using FigaroLib;
using FigaroLib.RPG.Factory;
using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Data;

using FigaroLib.Controller;

using NUnit.Framework;

using System.Collections.Generic;

namespace UnitTest.Controller
{
    [TestFixture]
    public class BattleScrenGuiHelperTests
    {
        #region members
        private PokemonFactory pokemonFactory;
        private BattleScreenGuiHelper battleGuiHelper;
        #endregion

        [SetUp]
        public void setUp()
        {
            Fi.startEngine();
            pokemonFactory = new PokemonFactory();
            battleGuiHelper = new BattleScreenGuiHelper();
        }

        [Test]
        public void normalPokemonMoveQueryTest()
        {
            Pokemon p = pokemonFactory.createPokemon(10, 25);
            List<MoveData> pokemonMoves = battleGuiHelper.queryPokemonMoveData(p);
            Assert.AreEqual(p.moves.Count, pokemonMoves.Count);
        }
    }
}
