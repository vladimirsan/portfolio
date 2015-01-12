namespace TestMVC
{
    partial class BattleSimulator
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnRun = new System.Windows.Forms.Button();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.lblPlayerPokemonName = new System.Windows.Forms.Label();
            this.lblPlayerPokemonHp = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lblPlayerPokemonLevel = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lblOpponentPokemonLevel = new System.Windows.Forms.Label();
            this.lblOpponentName = new System.Windows.Forms.Label();
            this.lblOpponentHp = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnRun
            // 
            this.btnRun.Location = new System.Drawing.Point(397, 310);
            this.btnRun.Name = "btnRun";
            this.btnRun.Size = new System.Drawing.Size(75, 23);
            this.btnRun.TabIndex = 0;
            this.btnRun.Text = "Run";
            this.btnRun.UseVisualStyleBackColor = true;
            this.btnRun.Click += new System.EventHandler(this.btnRun_Click);
            // 
            // txtOutput
            // 
            this.txtOutput.Location = new System.Drawing.Point(12, 156);
            this.txtOutput.Multiline = true;
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.Size = new System.Drawing.Size(460, 148);
            this.txtOutput.TabIndex = 1;
            // 
            // lblPlayerPokemonName
            // 
            this.lblPlayerPokemonName.AutoSize = true;
            this.lblPlayerPokemonName.Location = new System.Drawing.Point(6, 16);
            this.lblPlayerPokemonName.Name = "lblPlayerPokemonName";
            this.lblPlayerPokemonName.Size = new System.Drawing.Size(35, 13);
            this.lblPlayerPokemonName.TabIndex = 2;
            this.lblPlayerPokemonName.Text = "label1";
            // 
            // lblPlayerPokemonHp
            // 
            this.lblPlayerPokemonHp.AutoSize = true;
            this.lblPlayerPokemonHp.Location = new System.Drawing.Point(6, 39);
            this.lblPlayerPokemonHp.Name = "lblPlayerPokemonHp";
            this.lblPlayerPokemonHp.Size = new System.Drawing.Size(35, 13);
            this.lblPlayerPokemonHp.TabIndex = 3;
            this.lblPlayerPokemonHp.Text = "label1";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.lblPlayerPokemonLevel);
            this.groupBox1.Controls.Add(this.lblPlayerPokemonName);
            this.groupBox1.Controls.Add(this.lblPlayerPokemonHp);
            this.groupBox1.Location = new System.Drawing.Point(272, 88);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 62);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            // 
            // lblPlayerPokemonLevel
            // 
            this.lblPlayerPokemonLevel.AutoSize = true;
            this.lblPlayerPokemonLevel.Location = new System.Drawing.Point(159, 16);
            this.lblPlayerPokemonLevel.Name = "lblPlayerPokemonLevel";
            this.lblPlayerPokemonLevel.Size = new System.Drawing.Size(35, 13);
            this.lblPlayerPokemonLevel.TabIndex = 4;
            this.lblPlayerPokemonLevel.Text = "label1";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.lblOpponentPokemonLevel);
            this.groupBox2.Controls.Add(this.lblOpponentName);
            this.groupBox2.Controls.Add(this.lblOpponentHp);
            this.groupBox2.Location = new System.Drawing.Point(12, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(200, 62);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            // 
            // lblOpponentPokemonLevel
            // 
            this.lblOpponentPokemonLevel.AutoSize = true;
            this.lblOpponentPokemonLevel.Location = new System.Drawing.Point(159, 16);
            this.lblOpponentPokemonLevel.Name = "lblOpponentPokemonLevel";
            this.lblOpponentPokemonLevel.Size = new System.Drawing.Size(35, 13);
            this.lblOpponentPokemonLevel.TabIndex = 4;
            this.lblOpponentPokemonLevel.Text = "label1";
            // 
            // lblOpponentName
            // 
            this.lblOpponentName.AutoSize = true;
            this.lblOpponentName.Location = new System.Drawing.Point(6, 16);
            this.lblOpponentName.Name = "lblOpponentName";
            this.lblOpponentName.Size = new System.Drawing.Size(35, 13);
            this.lblOpponentName.TabIndex = 2;
            this.lblOpponentName.Text = "label1";
            // 
            // lblOpponentHp
            // 
            this.lblOpponentHp.AutoSize = true;
            this.lblOpponentHp.Location = new System.Drawing.Point(6, 39);
            this.lblOpponentHp.Name = "lblOpponentHp";
            this.lblOpponentHp.Size = new System.Drawing.Size(35, 13);
            this.lblOpponentHp.TabIndex = 3;
            this.lblOpponentHp.Text = "label1";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(316, 310);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 6;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(235, 310);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 7;
            this.button3.Text = "button3";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(154, 310);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 8;
            this.button4.Text = "button4";
            this.button4.UseVisualStyleBackColor = true;
            // 
            // BattleSimulator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(481, 378);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.txtOutput);
            this.Controls.Add(this.btnRun);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "BattleSimulator";
            this.Text = "Battle Simulator";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnRun;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.Label lblPlayerPokemonName;
        private System.Windows.Forms.Label lblPlayerPokemonHp;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lblPlayerPokemonLevel;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label lblOpponentPokemonLevel;
        private System.Windows.Forms.Label lblOpponentName;
        private System.Windows.Forms.Label lblOpponentHp;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
    }
}

