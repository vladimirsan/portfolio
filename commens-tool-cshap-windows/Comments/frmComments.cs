/*
For my C++ classes I was required to write comments for every method and file in my projects. 
This is an example of the type of comments I was required to write:

//-----------------------------------------------------------------------------
//	Class:         EQueue
//	method:        EQueue<T>(size_t,T) 
//	description:   Constructor with elements
//	Input:         None 
//	Output:        None 
//  Calls:
//		DCList<T>::DCList();
//	Called By:     n/a 
//	Parameters:    size_t n_elements -- number of elements
//				    T datum -- initial value
//	Returns:       n/a
//	History Log:
//				05/16/14 VS completed version 1.0
//-----------------------------------------------------------------------------

After a few projects I decided to write a tool to ease the documentation process.
 */
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.VisualBasic;

namespace Comments
{
    public partial class frmComments : Form
    {

        public frmComments()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Generates the comment based on the information present in the form
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
            String declaration = txtDeclaration.Text.Trim();
            String returnType = declaration.Substring(0, declaration.IndexOf(' '));
            String argumentString = declaration.Substring(declaration.IndexOf('('));

            //Removing the ");" present in the declarations.
            argumentString = argumentString.Substring(1, argumentString.Length - 3);

            String[] arguments = argumentString.Split(',');

            //Comment Header
            String comment =
@"//-----------------------------------------------------------------------------
// Class: ";
            //Including the comment fields
            comment += txtClass.Text + Environment.NewLine;
            comment += "// Method: " + declaration + Environment.NewLine;
            comment += "// Description: " + txtDescription.Text + Environment.NewLine;
            comment += "// Input: " + txtInput.Text + Environment.NewLine;
            comment += "// Output: " + txtInput.Text + Environment.NewLine;
            comment += "// Calls: " + Environment.NewLine;

            foreach (string currentString in txtCalls.Lines)
            {
                comment += "//   " + currentString + Environment.NewLine;
            }

            comment += "// Called By: " + Environment.NewLine;

            foreach (string currentString in txtCalledBy.Lines)
            {
                comment += "//   " + currentString + Environment.NewLine;
            }
            comment += "// Arguments: " + Environment.NewLine;

            foreach (string currentString in arguments)
            {
                comment += "//   " + currentString + " -- " +  
                    Interaction.InputBox(currentString,"Describe the following argument")
                    + Environment.NewLine;
            }
            comment += "// Returns: " + Environment.NewLine;
            comment += "//   " + returnType + " -- " +  
                Interaction.InputBox(returnType,"Describe the return type")
                + Environment.NewLine;

            comment += "// History Log: " + Environment.NewLine;
            comment += "//    " + txtHistoryLog.Text + Environment.NewLine;
            comment += "//-----------------------------------------------------------------------------";

            txtComment.Text = comment;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Auto-Loading the current date in the "History Log" field
            txtHistoryLog.Text = DateTime.Today.ToString("d") + " VS -- completed version 1.0";
        }

    }
}
