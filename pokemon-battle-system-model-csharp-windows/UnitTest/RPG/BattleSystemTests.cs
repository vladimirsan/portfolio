using NUnit.Framework;
using FigaroLib;
using FigaroLib.RPG.Battle;
using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Factory;
using FigaroLib.RPG.Data;

namespace UnitTest.RPG
{
    [TestFixture]
    public class BattleSystemTests
    {
        #region members
        private TypeManager typeManager;
        private PokemonFactory pokemonFactory;
        private BattleCalculations calculations;
        private PokemonBattleManager pokemonManager;
        #endregion

        [SetUp]
        public void setUp()
        {
            Fi.startEngine();
            typeManager = new TypeManager();       
            pokemonFactory = new PokemonFactory();

            calculations = new BattleCalculations();
            pokemonManager = new PokemonBattleManager();
        }

        [Test]
        public void testCriticalStrikeChances()
        {
            Pokemon p = pokemonFactory.createPokemon(10, 25);
            PokemonData data = Fi.data.getPokemonData(p.id);

            Assert.AreEqual(data.baseSpeed / 512, calculations.calculateCriticalChangeValue(p));
        }

        [Test]
        public void testNoStatModifier()
        {
            Pokemon p = pokemonFactory.createPokemon(10, 25);
            pokemonManager.calculateDynamicAttributes(p);

            Assert.AreEqual(p.staticAttack, p.battleAttack);
            Assert.AreEqual(p.staticDefense, p.battleDefense);
            Assert.AreEqual(p.staticSpeed, p.battleSpeed);
            Assert.AreEqual(p.staticSpecial, p.battleSpecial);
        }

        [Test]
        public void testPositiveStatModifier()
        {
            Pokemon p = pokemonFactory.createPokemon(10, 25);
            p.attackModifier = 1;
            p.defenseModifier = 3;
            p.speedModifier = 5;
            p.specialModifier = 6; 
            pokemonManager.calculateDynamicAttributes(p);

            Assert.AreEqual((int) p.staticAttack * 1.5, p.battleAttack);
            Assert.AreEqual((int) p.staticDefense * 2.5 , p.battleDefense);
            Assert.AreEqual((int) p.staticSpeed * 3.5, p.battleSpeed);
            Assert.AreEqual((int) p.staticSpecial * 4, p.battleSpecial);
        }

        [Test]
        public void testNegativeStatModifiers()
        {
            Pokemon p = pokemonFactory.createPokemon(10, 25);
            p.attackModifier = -1;
            p.defenseModifier = -3;
            p.speedModifier = -5;
            p.specialModifier = -6; 
            pokemonManager.calculateDynamicAttributes(p);

            Assert.AreEqual(13, p.battleAttack);
            Assert.AreEqual(8, p.battleDefense);
            Assert.AreEqual(7, p.battleSpeed);
            Assert.AreEqual(3, p.battleSpecial);
        }
    }
}
