using FigaroLib;
using FigaroLib.RPG.Data;
using FigaroLib.RPG.Characters;

using System.Collections.Generic;
using NUnit.Framework;

namespace UnitTest.RPG
{
    [TestFixture]
    public class DataSystemTests
    {
        #region members
            DataSystem data;
        #endregion

        [SetUp]
        public void setUp()
        {
            data = new DataSystem();
            data.start();
        }

        [Test]
        public void testNumberofPokemonInCatalog()
        {
            Assert.AreEqual(14, data.PokemonCatalogCount);
        }

        [Test]
        public void testCaterpieData()
        {
            PokemonData caterpie = data.getPokemonData(10);
            Assert.AreEqual(10,caterpie.id);
            Assert.AreEqual("Caterpie",caterpie.name);
            Assert.AreEqual(45,caterpie.baseHp);
            Assert.AreEqual(30,caterpie.baseAttack);
            Assert.AreEqual(35,caterpie.baseDefense);
            Assert.AreEqual(20,caterpie.baseSpecial);
            Assert.AreEqual(11,caterpie.typeId1);
            Assert.AreEqual(0,caterpie.typeId2);
        }

        [Test]
        public void testNumberElementCountPokemon_Move()
        {
            Assert.AreEqual(11, data.getPokemon_moveCountById(25));
        }

        [Test]
        public void testPokemon_MoveData()
        {
            List<int> list = data.getPokemonMovesPerLevel(25, 6);
            Assert.AreEqual(1, list.Count);
            Assert.AreEqual(5, list[0]);
        }

        [Test]
        public void testPokemon_MoveNoData()
        {
            List<int> list = data.getPokemonMovesPerLevel(25, 7);
            Assert.AreEqual(0, list.Count);
        }

        [Test]
        public void numberOfMovesInMoveCatalog()
        {
            Assert.AreEqual(49, data.MoveCatalogCount);
        }

        [Test]
        public void testMoveData()
        {
            PokemonData caterpie = data.getPokemonData(10);
            MoveData move = data.getMoveData(1);
            Assert.AreEqual(1,move.id);
            Assert.AreEqual("Tackle",move.name);
            Assert.AreEqual(35,move.basePower);
            Assert.AreEqual(95,move.accuracy);
            Assert.AreEqual(56,move.pp);
            Assert.AreEqual(1,move.typeId);
       }

        [Test]
        public void testNumberOfTypeRelations()
        {
            Assert.AreEqual(42, data.typeRelationCount);
        }

        [Test]
        public void testNormalTypeRelationData()
        {
            float multiplier = data.getTypeRelationMultiplier(
                PokemonType.Normal, PokemonType.Psychic);

            Assert.AreEqual(1, multiplier);
        }

        [Test]
        public void testpeRelationData()
        {
            float multiplier = data.getTypeRelationMultiplier(
                PokemonType.Electric, PokemonType.Flying);

            Assert.AreEqual(2, multiplier);
        }

        [Test]
        public void testNumberOfItems()
        {
            Assert.AreEqual(5, data.ItemCatalogCount);
        }

        [Test]
        public void testItemData()
        {
            ItemData testItem = data.getItem(1);
            Assert.AreEqual("Potion", testItem.name);
            Assert.AreEqual("Heals your Pokemon by 20 HP", testItem.description);
        }
    }
}
