using FigaroLib;
using FigaroLib.RPG.Characters;

using NUnit.Framework;

namespace UnitTest.RPG
{
    [TestFixture]
    public class ProgressionTests
    {
        #region members
        ProgressionManager pm;
        #endregion

        [SetUp]
        public void setUp()
        {
            Fi.startEngine();
            pm = new ProgressionManager();
        }

        [Test]
        public void addExpTest()
        {
            Pokemon testChar = new Pokemon();
            testChar.id = 10;

            pm.addExp(testChar, 100);
            Assert.AreEqual(100, testChar.exp);
        }

        [Test]
        public void levelUpNumber_oneLevelTest()
        {
            Pokemon testChar = new Pokemon();
            testChar.id = 10;
            pm.addExp(testChar, 8);

            Assert.AreEqual(2, testChar.level);
        }

        [Test]
        public void levelUpNumber_severalLevelTest()
        {
            Pokemon testChar = new Pokemon();
            testChar.id = 10;
            pm.addExp(testChar, 1000);

            Assert.AreEqual(10, testChar.level);
        }


        [Test]
        public void testOneLevelUpValues()
        {
            Pokemon testChar = new Pokemon();
            testChar.id = 10;
            pm.addExp(testChar, 8);

            Assert.AreEqual(2, testChar.level);

            Assert.AreEqual(14, testChar.maxHp);
            Assert.AreEqual(6, testChar.staticAttack);
            Assert.AreEqual(6, testChar.staticDefense);
            Assert.AreEqual(7, testChar.staticSpeed);
            Assert.AreEqual(6, testChar.staticSpecial);
        }

        [Test]
        public void testSeveralLevelUpValues()
        {
            Pokemon testChar = new Pokemon();
            testChar.id = 10;
            pm.addExp(testChar, 1000);

            Assert.AreEqual(10, testChar.level);

            Assert.AreEqual(29, testChar.maxHp);
            Assert.AreEqual(11, testChar.staticAttack);
            Assert.AreEqual(12, testChar.staticDefense);
            Assert.AreEqual(14, testChar.staticSpeed);
            Assert.AreEqual(9, testChar.staticSpecial);
        }

        [Test]
        public void testLearnZeroMovements()
        {
            Pokemon testChar = new Pokemon();
            testChar.id = 25;
            pm.addExp(testChar, 8);
            Assert.AreEqual(2, testChar.level);


            Assert.AreEqual(0, testChar.moves.Count);
        }

        [Test]
        public void testLearnMovements()
        {
            Pokemon testChar = new Pokemon();
            testChar.id = 25;
            pm.addExp(testChar, 1000);

            Assert.AreEqual(10, testChar.level);
            Assert.AreEqual(2, testChar.moves.Count);

            Assert.IsTrue(testChar.moves.ContainsKey(5));
        }
    }
}
