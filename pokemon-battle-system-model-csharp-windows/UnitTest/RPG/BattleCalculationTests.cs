using NUnit.Framework;
using FigaroLib;

using FigaroLib.RPG.Battle;
using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Factory;
using FigaroLib.RPG.Data;

namespace UnitTest.RPG
{
    [TestFixture]
    public class BattleCalculationTests
    {
        #region members
        private PokemonFactory pokemonFactory;
        private BattleCalculations calculations;
        private PokemonBattleManager pokemonBattleManager;
        #endregion

        [SetUp]
        public void setUp()
        {
            Fi.startEngine();
            pokemonFactory = new PokemonFactory();
            calculations = new BattleCalculations();
            pokemonBattleManager = new PokemonBattleManager();

        }

        [Test]
        public void testRandomDageCalculation()
        {
            Pokemon p1 = pokemonFactory.createPokemon(D.PIKACHU, 25);
            Pokemon p2 = pokemonFactory.createPokemon(D.CATERPIE, 25);

            pokemonBattleManager.calculateDynamicAttributes(p1);
            pokemonBattleManager.calculateDynamicAttributes(p2);
            MoveData data = Fi.data.getMoveData(D.THUNDERSHOCK);
        }
    }
}
