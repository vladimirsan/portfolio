namespace Comments
{
    partial class frmComments
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
            this.txtDeclaration = new System.Windows.Forms.TextBox();
            this.txtComment = new System.Windows.Forms.TextBox();
            this.btnGo = new System.Windows.Forms.Button();
            this.lblClass = new System.Windows.Forms.Label();
            this.txtClass = new System.Windows.Forms.TextBox();
            this.lblDescription = new System.Windows.Forms.Label();
            this.txtDescription = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtInput = new System.Windows.Forms.TextBox();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtCalls = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txtCalledBy = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtHistoryLog = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // txtDeclaration
            // 
            this.txtDeclaration.Location = new System.Drawing.Point(26, 22);
            this.txtDeclaration.Name = "txtDeclaration";
            this.txtDeclaration.Size = new System.Drawing.Size(1108, 20);
            this.txtDeclaration.TabIndex = 0;
            this.txtDeclaration.Text = "\t\tQueue<T> operator=(const Queue<T>& rq);";
            // 
            // txtComment
            // 
            this.txtComment.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtComment.Location = new System.Drawing.Point(12, 200);
            this.txtComment.Multiline = true;
            this.txtComment.Name = "txtComment";
            this.txtComment.Size = new System.Drawing.Size(1122, 361);
            this.txtComment.TabIndex = 1;
            // 
            // btnGo
            // 
            this.btnGo.Location = new System.Drawing.Point(792, 137);
            this.btnGo.Name = "btnGo";
            this.btnGo.Size = new System.Drawing.Size(342, 57);
            this.btnGo.TabIndex = 2;
            this.btnGo.Text = "Generate Comment";
            this.btnGo.UseVisualStyleBackColor = true;
            this.btnGo.Click += new System.EventHandler(this.button1_Click);
            // 
            // lblClass
            // 
            this.lblClass.AutoSize = true;
            this.lblClass.Location = new System.Drawing.Point(23, 47);
            this.lblClass.Name = "lblClass";
            this.lblClass.Size = new System.Drawing.Size(32, 13);
            this.lblClass.TabIndex = 4;
            this.lblClass.Text = "Class";
            // 
            // txtClass
            // 
            this.txtClass.Location = new System.Drawing.Point(26, 63);
            this.txtClass.Name = "txtClass";
            this.txtClass.Size = new System.Drawing.Size(167, 20);
            this.txtClass.TabIndex = 5;
            this.txtClass.Text = "CRPNCalc";
            // 
            // lblDescription
            // 
            this.lblDescription.AutoSize = true;
            this.lblDescription.Location = new System.Drawing.Point(23, 100);
            this.lblDescription.Name = "lblDescription";
            this.lblDescription.Size = new System.Drawing.Size(60, 13);
            this.lblDescription.TabIndex = 6;
            this.lblDescription.Text = "Description";
            // 
            // txtDescription
            // 
            this.txtDescription.Location = new System.Drawing.Point(26, 116);
            this.txtDescription.Name = "txtDescription";
            this.txtDescription.Size = new System.Drawing.Size(375, 20);
            this.txtDescription.TabIndex = 7;
            this.txtDescription.Text = "write description here";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(23, 158);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(31, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Input";
            // 
            // txtInput
            // 
            this.txtInput.Location = new System.Drawing.Point(26, 174);
            this.txtInput.Name = "txtInput";
            this.txtInput.Size = new System.Drawing.Size(167, 20);
            this.txtInput.TabIndex = 9;
            this.txtInput.Text = "N/A";
            // 
            // txtOutput
            // 
            this.txtOutput.Location = new System.Drawing.Point(234, 174);
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.Size = new System.Drawing.Size(167, 20);
            this.txtOutput.TabIndex = 11;
            this.txtOutput.Text = "N/A";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(231, 158);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Output";
            // 
            // txtCalls
            // 
            this.txtCalls.Location = new System.Drawing.Point(418, 63);
            this.txtCalls.Multiline = true;
            this.txtCalls.Name = "txtCalls";
            this.txtCalls.Size = new System.Drawing.Size(181, 131);
            this.txtCalls.TabIndex = 12;
            this.txtCalls.Text = "writeFunctionHere()";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(415, 48);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Calls";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(602, 48);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(50, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Called by";
            // 
            // txtCalledBy
            // 
            this.txtCalledBy.Location = new System.Drawing.Point(605, 63);
            this.txtCalledBy.Multiline = true;
            this.txtCalledBy.Name = "txtCalledBy";
            this.txtCalledBy.Size = new System.Drawing.Size(181, 131);
            this.txtCalledBy.TabIndex = 14;
            this.txtCalledBy.Text = "writeFunctionHere()";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(789, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 16;
            this.label1.Text = "History Log";
            // 
            // txtHistoryLog
            // 
            this.txtHistoryLog.Location = new System.Drawing.Point(792, 64);
            this.txtHistoryLog.Multiline = true;
            this.txtHistoryLog.Name = "txtHistoryLog";
            this.txtHistoryLog.Size = new System.Drawing.Size(342, 67);
            this.txtHistoryLog.TabIndex = 17;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(23, 6);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(99, 13);
            this.label6.TabIndex = 18;
            this.label6.Text = "Function Signature:";
            // 
            // frmComments
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1146, 573);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.txtHistoryLog);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.txtCalledBy);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtCalls);
            this.Controls.Add(this.txtOutput);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtInput);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtDescription);
            this.Controls.Add(this.lblDescription);
            this.Controls.Add(this.txtClass);
            this.Controls.Add(this.lblClass);
            this.Controls.Add(this.btnGo);
            this.Controls.Add(this.txtComment);
            this.Controls.Add(this.txtDeclaration);
            this.Name = "frmComments";
            this.Text = "Comments 1.0";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtDeclaration;
        private System.Windows.Forms.TextBox txtComment;
        private System.Windows.Forms.Button btnGo;
        private System.Windows.Forms.Label lblClass;
        private System.Windows.Forms.TextBox txtClass;
        private System.Windows.Forms.Label lblDescription;
        private System.Windows.Forms.TextBox txtDescription;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtInput;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtCalls;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtCalledBy;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtHistoryLog;
        private System.Windows.Forms.Label label6;
    }
}

