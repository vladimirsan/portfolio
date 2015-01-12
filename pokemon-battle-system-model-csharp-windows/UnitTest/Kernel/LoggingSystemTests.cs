using NUnit.Framework;
using FigaroLib;
using FigaroLib.Kernel.Debug;

namespace UnitTestsDemo
{
    [TestFixture]
    public class LoggingSystemTests
    {
        [SetUp]
        public void setUp()
        {
            Fi.startEngine();
        }

        [Test]
        public void testNormalArguments()
        {
            Assert.AreEqual("a\n\tb",
            Fi.logs.createLogMessage("a", "b"));
            Fi.logs.logMessage("Figaro engine started", LoggingSystem.LogLevel.Info);
        }

        [Test]
        public void testSingleParameter()
        {
            Assert.AreEqual("a",
            Fi.logs.createLogMessage("a"));
        }
    }
}
