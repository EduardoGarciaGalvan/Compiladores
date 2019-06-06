using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Resources;
using System.Diagnostics;
using System.Management;
using System.IO;
using System.Windows.Forms;

namespace CompilerUI
{
    public partial class compilerWindow : Form
    {
        String str;
        String FilePath;
        String dllFullPath;
        List<String> Token = new List<String>();
        dynamic compilerDLLInstance;
        bool isDLLLoader;
        bool currentAssemblyisDebug;
        bool currentAssembluisx64;
        bool isSaved;

        public compilerWindow()
        {
            InitializeComponent();
            dllFullPath = "";
            FilePath = null;
            isDLLLoader = false;
            isSaved = false;
        }

        private void nuevoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (textBox1.Modified)
            {
                IsSaved();
                textBox1.Text = "";
            }
        }

        private void abrirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string text;
            if (textBox1.Modified)
                IsSaved();
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                System.IO.StreamReader file = new System.IO.StreamReader(openFileDialog1.FileName);
                text = file.ReadLine();
                textBox1.Text = text.ToString();
            }
        }

        private void textBox1_ModifiedChanged(object sender, EventArgs e)
        {
            isSaved = false;
        }

        private void guardarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Guardar();
            isSaved = true;
        }

        private void guardarComoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GuardarComo();
        }

        private void salirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (textBox1.Modified)
                IsSaved();
            Environment.Exit(0);
        }

        private void compilerWindow_Load(object sender, EventArgs e)
        {
            if(!loadCompilerDLL())
            {
                MessageBox.Show("", "", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            isDLLLoader = true;
        }

        private void compilarProgramaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (isDLLLoader)
            {
                String[] output = compilerDLLInstance.compileProgram(textBox1.Text);
                Output.Text = output[0];
                if (output[2] != null)
                {
                    Output.Text += "\r\n";
                    Output.Text += output[2];
                }
                else
                {
                    Output.Text += "\r\n";
                    Output.Text += "no se detectaron errores";
                }
                Update();
                dataGridView1.Rows.Clear();
                String tokens = output[1];
                if (tokens != null)
                {
                    for (int i = 0; i < tokens.Length; i++)
                    {

                        if (tokens[i] != '@')
                        {
                            str += tokens[i];
                            //i++;
                        }
                        if (tokens[i + 1] == '@')
                        {
                            Token.Add(str);
                            str = "";
                            i++;
                        }
                        if (Token.Count == 3)
                        {
                            dataGridView1.Rows.Add(Token[0], Token[1], Token[2]);

                            Token.Clear();
                        }
                    }
                }
            }
            else
            {
                string mesg = "No se pudo cargar la DLL";
                string name = "cargar DLL";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(mesg, name, buttons, MessageBoxIcon.Error);
                return;
            }
        }

        private void IsSaved()
        {
            String message;
            if (null != FilePath)
                message = "¿Desea guardar los cambios?";
            else
                message = "¿Desea guardar el documento?";
            MessageBoxButtons buttons = MessageBoxButtons.YesNoCancel;
            DialogResult result;
            result = MessageBox.Show(message, "Sin Guardar", buttons);
            if (result == System.Windows.Forms.DialogResult.Yes)
            {
                if (null == FilePath)
                    Guardar();
                else
                    GuardarComo();
            }
        }
        
        private void Guardar()
        {
            if (saveFileDialog1.FileName != "")
            {
                FilePath = Path.GetFullPath(saveFileDialog1.FileName);
            }
            else
            {
                GuardarComo();
            }
        }

        private void GuardarComo()
        {
            saveFileDialog1.FileName = "Sin Titulo.txt";
            saveFileDialog1.Filter = "Archivos de texto (.txt)|*.txt|Todos los archivos (*.*)|*.*";
            saveFileDialog1.Title = "Guardar como...";
            var sf = saveFileDialog1.ShowDialog();
            if (sf == DialogResult.OK)
            {
                using (var SaveFile = new System.IO.StreamWriter(saveFileDialog1.FileName))
                {
                    SaveFile.WriteLine(textBox1.Text);
                }
            }
            isSaved = true;
        }

        private bool loadCompilerDLL()
        {
            String dllFilename;
            String processFullPath = Process.GetCurrentProcess().MainModule.FileName;//Solo funciona 64 bits
            DirectoryInfo up = Directory.GetParent(processFullPath);
            String baseProj = up.FullName;
            for (int i = 0; i < 4; i++)
            {
                up = Directory.GetParent(baseProj);
                baseProj = up.FullName;
            }
            currentAssemblyisDebug = System.Diagnostics.Debugger.IsAttached;
            currentAssembluisx64 = System.Environment.Is64BitProcess;
            if (currentAssemblyisDebug)
            {
                if (currentAssembluisx64)
                {
                    dllFilename = "Compilerx64d.dll";
                    dllFullPath = baseProj + "\\x64\\Exe\\Debug\\" + dllFilename;
                }
                else
                {
                    dllFilename = "Compilerx86.dll";
                    dllFullPath = baseProj + "\\x86\\Exe\\Debug\\" + dllFilename;
                }
            }
            else
            {
                if (currentAssembluisx64)
                {
                    dllFilename = "Compilerx64.dll";
                    dllFullPath = baseProj + "\\x64\\Exe\\Release\\" + dllFilename;
                }
                else
                {
                    dllFilename = "Compilerx86.dll";
                    dllFullPath = baseProj + "\\x86\\Exe\\Release\\" + dllFilename;
                }

            }
            var DLL = Assembly.UnsafeLoadFrom(dllFullPath);
            var DLLType = DLL.GetType("Compiler.Manager");
            compilerDLLInstance = Activator.CreateInstance(DLLType);
            isDLLLoader = compilerDLLInstance != null;
            return isDLLLoader;
        }

    }
}

/*Tarea: Investigar como
 * determinar en runtime
 * si un programa de c#
 * es 32 o 64 bits y 
 * debug o release
 Assembly. ()*/