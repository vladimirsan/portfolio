using FigaroLib.RPG.Characters;
using FigaroLib.RPG.Battle;

namespace FigaroLib.RPG.Scripting
{
    public partial class ScriptingSystem
    {
        #region members

        #endregion

        private void loadMoveDelegates()
        {
            moves.Add(1, tackle);
            moves.Add(2,stringShot);
            moves.Add(3,thunderShock);
            moves.Add(4,growl);
            moves.Add(5,tailWhip);

            moves.Add(6,harden);
            moves.Add(7,poisonSting);
            moves.Add(8,furyAttack);
            moves.Add(9,poisonSting);
            moves.Add(10,twinNeedle);

            moves.Add(11,rage);
            moves.Add(12,pinMissile);
            moves.Add(13,sandAttack);
            moves.Add(14,gust);
            moves.Add(15,quickAttack);

            moves.Add(16,whirlwind);
            moves.Add(17,wingAttack);
            moves.Add(18,agility);
            moves.Add(19,mirrorMove);
            moves.Add(20,hyperFang);

            moves.Add(21,superFang);
            moves.Add(22,peck);
            moves.Add(23,leer);
            moves.Add(24,drillPeck);
            moves.Add(25,wrap);

            moves.Add(26,bite);
            moves.Add(27,glare);
            moves.Add(28,screech);
            moves.Add(29,acid);
            moves.Add(30,haze);

            moves.Add(31,thunderWave);
            moves.Add(32,doubleTeam);
            moves.Add(33,slam);
            moves.Add(34,thunderBolt);
            moves.Add(35,thunder);

            moves.Add(36,lightScreen);
            moves.Add(37,scratch);
            moves.Add(38,payDay);
            moves.Add(39,furySwipes);
            moves.Add(40,slash);
            moves.Add(50,lowKick);

            moves.Add(51,karateChop);
            moves.Add(53,seismicToss);
            moves.Add(54,poisonGas);
            moves.Add(55,smog);

            moves.Add(56,selfDestruct);
            moves.Add(57,sludge);
            moves.Add(58,smokeScreen);
            moves.Add(59,explosion);

        }

        private bool isAdssBetweenBounds(int modifier)
        {
            if(modifier >= -5 && modifier <= 5)
                return true;
            return false;
        }

        private bool isAccuracyBetweenBounds(int modifier)
        {
            if(modifier > -6 && modifier <= 0)
                return true;
            return false;
        }

        private bool isEvasionBetweenBounds(int modifier)
        {
            if(modifier >= 0 && modifier < 6)
                return true;
            return false;
        }

        /* --------------------------------------------------------------- */
        /* post-processed:
         * 
         * focus enengy
         * slash
         * karate chop
         */
        private void tackle(Pokemon attacker, Pokemon defender)
        { }

        private void stringShot(Pokemon attacker, Pokemon defender)
        {
            if(isAdssBetweenBounds(defender.speedModifier))
            {
                defender.speedModifier -= 1;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderSpeedDecreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void thunderShock(Pokemon attacker, Pokemon defender)
        {
            if(defender.isParalyzed == false && Fi.random.Next(100) < 10)
            {
                defender.isParalyzed = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderParalyzed);
            }
        }

        private void growl(Pokemon attacker, Pokemon defender)
        {
            if(isAdssBetweenBounds(defender.attackModifier))
            {
                defender.attackModifier -= 1;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderAttackDecreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void tailWhip(Pokemon attacker, Pokemon defender)
        {
            if(isAdssBetweenBounds(defender.defenseModifier))
            {
                defender.defenseModifier -= 1;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderDefenseDecreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void harden(Pokemon attacker, Pokemon defender)
        {
            if(isAdssBetweenBounds(attacker.defenseModifier))
            {
                attacker.defenseModifier += 1;
                Fi.battle.messageObservers(BattleObserverMessage.AttackerDefenseIncreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void poisonSting(Pokemon attacker, Pokemon defender)
        {
            if(defender.isPoisoned == false && Fi.random.Next(100) < 30)
            {
                defender.isPoisoned = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderPoisoned);
            }
        }

        private void furyAttack(Pokemon attacker, Pokemon defender)
        { }

        private void focusEnergy(Pokemon attacker, Pokemon defender)
        {
            if (attacker.battleSpeed <= defender.battleSpeed)
            {
                attacker.permanentCriticalHitMultiplier = 4;
                Fi.battle.messageObservers(BattleObserverMessage.AttackerFocusEnergy);
            }
        }

        private void twinNeedle(Pokemon attacker, Pokemon defender)
        {
            if (defender.isPoisoned == false && Fi.random.Next(100) < 10)
            {
                defender.isPoisoned = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderPoisoned);
            }
        }

        private void rage(Pokemon attacker, Pokemon defender)
        { }

        private void pinMissile(Pokemon attacker, Pokemon defender)
        { }

        private void sandAttack(Pokemon attacker, Pokemon defender)
        {
            if (isAccuracyBetweenBounds(defender.accuracy))
            {
                defender.accuracy -= 1;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderAccuracyDecreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void gust(Pokemon attacker, Pokemon defender)
        { }

        private void quickAttack(Pokemon attacker, Pokemon defender)
        { }

        private void whirlwind(Pokemon attacker, Pokemon defender)
        { }

        private void wingAttack(Pokemon attacker, Pokemon defender)
        { }

        private void agility(Pokemon attacker, Pokemon defender)
        {
            if (isAdssBetweenBounds(attacker.speedModifier))
            {
                attacker.speedModifier += 2;
                if (attacker.speedModifier > 6)
                {
                    attacker.speedModifier = 6;
                }
                Fi.battle.messageObservers(BattleObserverMessage.AttackerSpeedGreatlyIncreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void mirrorMove(Pokemon attacker, Pokemon defender)
        { }

        private void hyperFang(Pokemon attacker, Pokemon defender)
        { 
            if (Fi.random.Next(100) < 10)
            {
                Fi.battle.DefenderFlinched = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderFlinched);
            }
        }

        private void superFang(Pokemon attacker, Pokemon defender)
        { }

        private void peck(Pokemon attacker, Pokemon defender)
        { }

        private void leer(Pokemon attacker, Pokemon defender)
        { 
            if(isAdssBetweenBounds(defender.defenseModifier))
            {
                defender.defenseModifier -= 1;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderDefenseDecreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void drillPeck(Pokemon attacker, Pokemon defender)
        { }

        private void wrap(Pokemon attacker, Pokemon defender)
        { }

        private void bite(Pokemon attacker, Pokemon defender)
        { 
            if (Fi.random.Next(100) < 10)
            {
                Fi.battle.DefenderFlinched = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderFlinched);
            }
        }

        private void glare(Pokemon attacker, Pokemon defender)
        { 
            if (defender.isParalyzed == false)
            {
                defender.isParalyzed = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderParalyzed);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void screech(Pokemon attacker, Pokemon defender)
        { 
            if(isAdssBetweenBounds(defender.defenseModifier))
            {
                defender.defenseModifier -= 2;

                if (defender.defenseModifier < -6)
                    defender.defenseModifier = 6;

                Fi.battle.messageObservers(BattleObserverMessage.DefenderDefenseGreatlyDecreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void acid(Pokemon attacker, Pokemon defender)
        { 
            if(Fi.random.Next(100) < 10 && isAdssBetweenBounds(defender.defenseModifier))
            {
                defender.defenseModifier -= 1;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderDefenseDecreased);
            }
        }

        private void haze(Pokemon attacker, Pokemon defender)
        {
            pokemonManager.resetModifiersAfterBattle(attacker);
            pokemonManager.resetModifiersAfterBattle(defender);

            attacker.isPoisoned = false;
            defender.isPoisoned = false;
            Fi.battle.messageObservers(BattleObserverMessage.Haze);
        }

        private void thunderWave(Pokemon attacker, Pokemon defender)
        {
            if (defender.isParalyzed == false)
            {
                defender.isParalyzed = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderParalyzed);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void doubleTeam(Pokemon attacker, Pokemon defender)
        {
            if (isEvasionBetweenBounds(attacker.evasion))
            {
                attacker.evasion += 1;
                Fi.battle.messageObservers(BattleObserverMessage.AttackerEvasionIncreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void slam(Pokemon attacker, Pokemon defender)
        { }

        private void thunderBolt(Pokemon attacker, Pokemon defender)
        { 
            if (Fi.random.Next(100) < 10 && defender.isParalyzed == false)
            {
                defender.isParalyzed = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderParalyzed);
            }
        }

        private void thunder(Pokemon attacker, Pokemon defender)
        { 
            if (defender.isParalyzed == false && Fi.random.Next(100) < 100)
            {
                defender.isParalyzed = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderParalyzed);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void lightScreen(Pokemon attacker, Pokemon defender)
        {
            if (attacker.specialDefenseMultiplier == 1)
            {
                attacker.specialDefenseMultiplier = 0.5f;
                Fi.battle.messageObservers(BattleObserverMessage.AttackerLightScreen);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }

        private void scratch(Pokemon attacker, Pokemon defender)
        { }

        private void payDay(Pokemon attacker, Pokemon defender)
        { }

        private void furySwipes(Pokemon attacker, Pokemon defender)
        { }

        private void slash(Pokemon attacker, Pokemon defender)
        {
            attacker.temporalCriticalHitMultiplier = 8;
        }

        //private void disable(Pokemon attacker, Pokemon defender)
        //{
        //}       

        //private void supersonic(Pokemon attacker, Pokemon defender)
        //{
        //    if (defender.confused == false)
        //    {
        //        defender.confused = true;
        //        Fi.battle.messageObservers(BattleObserverMessage.DefenderConfused);
        //    }
        //    else
        //        Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        //}       

        //private void confusion(Pokemon attacker, Pokemon defender)
        //{
        //    if (defender.confused == false && Fi.random.Next(100) < 10)
        //    {
        //        defender.confused = true;
        //        Fi.battle.messageObservers(BattleObserverMessage.DefenderConfused);
        //    }
        //    else
        //        Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        //}       

        //private void poisonPowder(Pokemon attacker, Pokemon defender)
        //{
        //    if(defender.poisoned == false && Fi.random.Next(100) < 30)
        //    {
        //        defender.poisoned = true;
        //        Fi.battle.messageObservers(BattleObserverMessage.DefenderPoisoned);
        //    }
        //    else
        //        Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        //}      

        //private void leechLife(Pokemon attacker, Pokemon defender)
        //{
        //}      

        //private void leechSeed(Pokemon attacker, Pokemon defender)
        //{
        //}      

        //private void stunSpore(Pokemon attacker, Pokemon defender)
        //{
        //    if (defender.paralyzed == false)
        //    {
        //        defender.paralyzed = true;
        //        Fi.battle.messageObservers(BattleObserverMessage.DefenderParalyzed);
        //    }
        //    else
        //        Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        //}      

        //private void psybeam(Pokemon attacker, Pokemon defender)
        //{
        //    if (defender.confused == false && Fi.random.Next(100) < 10)
        //    {
        //        defender.confused = true;
        //        Fi.battle.messageObservers(BattleObserverMessage.DefenderConfused);
        //    }
        //}      

        //private void sleepPowder(Pokemon attacker, Pokemon defender)
        //{
        //    if (defender.sleeping == false)
        //    {
        //        defender.sleeping = true;
        //        Fi.battle.messageObservers(BattleObserverMessage.DefenderSleeping);
        //    }
        //    else
        //        Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        //}      

        //private void psychic(Pokemon attacker, Pokemon defender)
        //{
        //    if (Fi.random.Next(100) < 30 && isAdssBetweenBounds(defender.specialModifier))
        //    {
        //        defender.specialModifier -= 1;
        //        Fi.battle.messageObservers(BattleObserverMessage.DefenderSpecialDecreased);
        //    }
        //}      

        private void lowKick(Pokemon attacker, Pokemon defender)
        {
            if (Fi.random.Next(100) < 30)
            {
                Fi.battle.DefenderFlinched = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderFlinched);
            }
        }      

        private void karateChop(Pokemon attacker, Pokemon defender)
        {
            attacker.temporalCriticalHitMultiplier = 8;
        }      

        private void seismicToss(Pokemon attacker, Pokemon defender)
        {
        }      

        private void poisonGas(Pokemon attacker, Pokemon defender)
        {
            if(defender.isPoisoned == false && Fi.random.Next(100) < 30)
            {
                defender.isPoisoned = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderPoisoned);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }      

        private void smog(Pokemon attacker, Pokemon defender)
        {
            if (defender.isPoisoned == false && Fi.random.Next(100) < 50)
            {
                defender.isPoisoned = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderPoisoned);
            }
        }      

        private void selfDestruct(Pokemon attacker, Pokemon defender)
        {
        }      

        private void sludge(Pokemon attacker, Pokemon defender)
        {
            if (defender.isPoisoned == false && Fi.random.Next(100) < 50)
            {
                defender.isPoisoned = true;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderPoisoned);
            }
        }      

        private void smokeScreen(Pokemon attacker, Pokemon defender)
        {
            if (isAccuracyBetweenBounds(defender.accuracy))
            {
                defender.accuracy -= 1;
                Fi.battle.messageObservers(BattleObserverMessage.DefenderAccuracyDecreased);
            }
            else
                Fi.battle.messageObservers(BattleObserverMessage.NoEffect);
        }      

        private void explosion(Pokemon attacker, Pokemon defender)
        {
        }      
    }
}
