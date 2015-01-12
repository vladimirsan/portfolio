using FigaroLib.Kernel.Debug;
using FigaroLib.RPG.Battle;

using System;
using System.Collections.Generic;

namespace FigaroLib.RPG.Characters
{
    //Esta enumeracion esta en base a la base de datos
    public enum PokemonType
    {          
        Null = 0,
        Normal = 1,
        Fire,
        Grass,
        Ice,
        Water,
        Electric,
        Poison,
        Ground,
        Fighting,
        Flying,
        Bug,
        Ghost,
        Dragon,
        Rock,
        Psychic
    }

    public class Pokemon
    {
        #region members
        //Progression 
        public int id;
        public int level;
        public int exp;

        //Static
        public String name;

        //Combat Static
        public int maxHp;
        public int staticAttack;
        public int staticDefense;
        public int staticSpeed;
        public int staticSpecial;

        //Combat Dynamic
        public int hp;
        public int battleAttack;
        public int battleDefense;
        public int battleSpeed;
        public int battleSpecial;

        public int attackModifier;
        public int defenseModifier;
        public int speedModifier;
        public int specialModifier;

        public int accuracy;
        public int evasion;
        public int temporalCriticalHitMultiplier;
        public int permanentCriticalHitMultiplier;
        public float specialDefenseMultiplier;

        //Status
        public bool isParalyzed;
        public bool isPoisoned;

        //Other Data

        /* Estoy usando un diccionario porque me va a permitir no solo almacenar la informacion
         * de los id, si no tambien almacenar la informacion particular de los pp sin
         * eliminarme la facilidad de busqueda por id */
        public Dictionary<int, int> moves;

        public PokemonType type1;
        public PokemonType type2;
        #endregion

        public Pokemon()
        {
            //No estoy del todo seguro si esto implica mucha perdida de performance
            id = -1;
            level = 1;
            temporalCriticalHitMultiplier = 1;
            permanentCriticalHitMultiplier = 1;
            specialDefenseMultiplier = 1;

            isParalyzed = false;
            isPoisoned = false;

            moves = new Dictionary<int, int>(); 
            type1 = type2 = PokemonType.Null;
        }
    }
}
