using FigaroLib;
using FigaroLib.RPG.Battle;
using FigaroLib.RPG.Battle.Commands;

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;



namespace TestMVC
{
    public partial class BattleSimulator : Form, IBattleObserver 
    {
        public BattleSimulator()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Fi.startEngine();
            Fi.battle.registerObserver(this);
            Fi.battle.setUpBattle(Fi.factories.opponentFactory.createWildPokemon(10,10));

            loadPokemonData();
        }

        public void update()
        {
            Debug.Assert(Fi.battle.CurrentPhaseStatus != PhaseStatus.Null);
           
            switch (Fi.battle.CurrentPhaseStatus)
            {
                case PhaseStatus.Null:
                break;
                case PhaseStatus.RunSuccesful:
                    txtOutput.Text = "Ran away :)" + Environment.NewLine + txtOutput.Text;
                    break;
                case PhaseStatus.RunFailed:
                    txtOutput.Text = "Run Failed" + Environment.NewLine + txtOutput.Text;
                    break;
                default:
                    break;
            }
        }

        private void loadPokemonData()
        {
            lblPlayerPokemonName.Text = Fi.gameFlow.player.CurrentPokemon.name;
            lblOpponentName.Text = Fi.battle.Opponent.CurrentPokemon.name;

            lblOpponentHp.Text = Fi.battle.Opponent.CurrentPokemon.hp.ToString();
            lblPlayerPokemonHp.Text = Fi.gameFlow.player.CurrentPokemon.hp.ToString();

            lblPlayerPokemonLevel.Text = Fi.gameFlow.player.CurrentPokemon.level.ToString();
            lblOpponentPokemonLevel.Text = Fi.battle.Opponent.CurrentPokemon.level.ToString();

            txtOutput.Text = "A wild Caterpie Appears" + Environment.NewLine + txtOutput.Text;
        }

        private void btnRun_Click(object sender, EventArgs e)
        {
            Fi.battle.executeTurn(new RunCommand(Fi.gameFlow.player));
        }
    }
}
