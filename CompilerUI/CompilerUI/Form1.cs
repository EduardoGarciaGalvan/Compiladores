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
        dynamic compilerDLLInstance;
        bool isDLLLoader;
        bool currentAssemblyisDebug;
        bool currentAssembluisx64;
        bool isSaved;
        public compilerWindow()
        {
            InitializeComponent();
            isDLLLoader = false;
            isSaved = false;
        }

        private void nuevoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!isSaved)
            {
                String message = "¿Desea guardar los cambios?";
                MessageBoxButtons buttons = MessageBoxButtons.YesNoCancel;
                DialogResult result;
                result = MessageBox.Show(message, " no guardado", buttons);
                if(result == System.Windows.Forms.DialogResult.Yes)
                {

                }
                if(result == System.Windows.Forms.DialogResult.No)
                {

                }
                if (result == System.Windows.Forms.DialogResult.Cancel)
                {

                }
            }
        }

        private void abrirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string text;
            openFileDialog1.ShowDialog();
            System.IO.StreamReader file = new System.IO.StreamReader(openFileDialog1.FileName);
            text = file.ReadLine();
            textBox1.Text = text.ToString();
        }

        private void textBox1_ModifiedChanged(object sender, EventArgs e)
        {
            isSaved = false;
        }

        private void guardarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveFileDialog1.FileName = "Sin Titulo.txt";
            using (var SaveFile = new System.IO.StreamWriter(saveFileDialog1.FileName))
            {
                SaveFile.WriteLine(textBox1.Text);
            }
            isSaved = true;
        }

        private void guardarComoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GuardarComo();
        }

        private void salirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!isSaved)
            {
                String message = "¿Desea guardar los cambios?";
                MessageBoxButtons buttons = MessageBoxButtons.YesNoCancel;
                DialogResult result;
                result = MessageBox.Show(message, " no guardado", buttons);
                if (result == System.Windows.Forms.DialogResult.Yes)
                {

                }
                if (result == System.Windows.Forms.DialogResult.Cancel)
                {

                }
            }
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
                Output.Lines = output;
            }
            else
            {

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
            String dllFullPath;
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