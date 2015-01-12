using NUnit.Framework;

using FigaroLib.RPG.Factory;
using FigaroLib.RPG.Characters;
using FigaroLib;

namespace UnitTest.RPG
{
    [TestFixture]
    public class FactoryTests
    {
        #region members
        PokemonFactory pokemonFactory;
        #endregion

        [SetUp]
        public void setUp()
        {
            Fi.startEngine();
            pokemonFactory = new PokemonFactory();
        }

        [Test]
        public void testPokemonFactoryMoves()
        {
            Pokemon testChar = pokemonFactory.createPokemon(25, 10); 

            Assert.AreEqual(10, testChar.level);
            Assert.AreEqual(4, testChar.moves.Count);

            Assert.IsTrue(testChar.moves.ContainsKey(5));
            Assert.AreEqual(PokemonType.Electric, testChar.type1);
            Assert.AreEqual(PokemonType.Null, testChar.type2);
        }

        [Test]
        public void testPokemonFactoryMoves_Level1()
        {
            Pokemon testChar = pokemonFactory.createPokemon(25, 1); 

            Assert.AreEqual(1, testChar.level);
            Assert.AreEqual(2, testChar.moves.Count);
        }

        [Test]
        public void testPokemonFactoryData()
        {
            Pokemon testChar = pokemonFactory.createPokemon(10, 10); 

            Assert.AreEqual(10, testChar.level);

            Assert.AreEqual(29, testChar.maxHp);
            Assert.AreEqual(11, testChar.staticAttack);
            Assert.AreEqual(12, testChar.staticDefense);
            Assert.AreEqual(14, testChar.staticSpeed);
            Assert.AreEqual(9, testChar.staticSpecial);

            Assert.AreEqual(PokemonType.Bug, testChar.type1);
            Assert.AreEqual(PokemonType.Null, testChar.type2);

        }
    }
}
