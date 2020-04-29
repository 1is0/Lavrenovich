using System;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace _4._1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void ShowAllProcessesBtn_Click(object sender, EventArgs e)
        {
            Process anotherProc = null;
            IntPtr snap = WinAPIImport.CreateToolhelp32Snapshot(WinAPIImport.SnapshotFlags.Process, 0);
            WinAPIImport.PROCESSENTRY32 pe = new WinAPIImport.PROCESSENTRY32();
            pe.dwSize = (UInt32)Marshal.SizeOf(typeof(WinAPIImport.PROCESSENTRY32));
            try
            {
                if (WinAPIImport.Process32First(snap, ref pe))
                {
                    ProcessesTreeView.Nodes.Clear();
                    do
                    {
                        anotherProc = Process.GetProcessById((int)pe.th32ProcessID);
                        TreeNode tmp = ProcessesTreeView.Nodes.Add($"ID: {anotherProc.Id} Name: {anotherProc.ProcessName}");
                        tmp.Nodes.Add($"Memory size allocated for process: {anotherProc.VirtualMemorySize64} bytes");
                    } while (WinAPIImport.Process32Next(snap, ref pe));
                }
                else
                {
                    MessageBox.Show("Unable to get any process!");
                }

            }
            catch (System.ComponentModel.Win32Exception)
            {
                MessageBox.Show("Something went wrong, try again please (:");
            }
            catch (System.ArgumentException)
            {
                MessageBox.Show("Some process has just terminated in runtime, please try again.");
            }
            finally
            {
                // Must clean up the snapshot object!
                WinAPIImport.CloseHandle(snap);
            }
        }

        private void ExitBtn_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
