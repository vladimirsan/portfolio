namespace FigaroLib.RPG.Battle
{
    public enum BattleCommandType
    {
        ChangePokemon,UseItem,Run,Attack
    }

    public enum OpponentType
    {
       Trainer,WildPokemon,Player
    }

    public enum BattleObserverMessage
    {
        PhaseADone,PhaseBDone,
        
        ShowPlayerCommand,ShowComputerCommand,

        PlayerRunSuccesful,PlayerRunFailed,
        PokemonRunSuccesful,PokemonRunFailed,

        WildPokemonDefeated,
        TrainerPokemonDefeated,TrainerDefeated,
        PlayerPokemonDefeated,PlayerDefeated,

        DamageDone,
        MoveMisses,

        DefenderSpeedDecreased,
        DefenderSpecialDecreased,
        DefenderAttackDecreased,
        DefenderDefenseDecreased,
        DefenderDefenseGreatlyDecreased,
        DefenderAccuracyDecreased,
        DefenderParalyzed,
        DefenderPoisoned,
        DefenderFlinched,
        DefenderConfused,
        DefenderSleeping,

        AttackerDefenseIncreased,
        AttackerFocusEnergy,
        AttackerSpeedGreatlyIncreased,
        AttackerEvasionIncreased,
        AttackerLightScreen,
        AttackerisParalyzedCantAttack,
        AttackerPoisonDamage,

        Haze,
        NoEffect
    }
}