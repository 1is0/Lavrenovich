namespace _4._1
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.ShowAllProcessesBtn = new System.Windows.Forms.Button();
            this.ProcessesTreeView = new System.Windows.Forms.TreeView();
            this.ExitBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ShowAllProcessesBtn
            // 
            this.ShowAllProcessesBtn.Location = new System.Drawing.Point(288, 12);
            this.ShowAllProcessesBtn.Name = "ShowAllProcessesBtn";
            this.ShowAllProcessesBtn.Size = new System.Drawing.Size(135, 47);
            this.ShowAllProcessesBtn.TabIndex = 1;
            this.ShowAllProcessesBtn.Text = "Показать все процессы";
            this.ShowAllProcessesBtn.UseVisualStyleBackColor = true;
            this.ShowAllProcessesBtn.Click += new System.EventHandler(this.ShowAllProcessesBtn_Click);
            // 
            // ProcessesTreeView
            // 
            this.ProcessesTreeView.Location = new System.Drawing.Point(9, 6);
            this.ProcessesTreeView.Name = "ProcessesTreeView";
            this.ProcessesTreeView.Size = new System.Drawing.Size(273, 425);
            this.ProcessesTreeView.TabIndex = 2;
            // 
            // ExitBtn
            // 
            this.ExitBtn.Location = new System.Drawing.Point(288, 381);
            this.ExitBtn.Name = "ExitBtn";
            this.ExitBtn.Size = new System.Drawing.Size(135, 50);
            this.ExitBtn.TabIndex = 3;
            this.ExitBtn.Text = "Выход";
            this.ExitBtn.UseVisualStyleBackColor = true;
            this.ExitBtn.Click += new System.EventHandler(this.ExitBtn_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(437, 450);
            this.Controls.Add(this.ExitBtn);
            this.Controls.Add(this.ProcessesTreeView);
            this.Controls.Add(this.ShowAllProcessesBtn);
            this.Name = "Form1";
            this.Text = "ProcessManager";
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button ShowAllProcessesBtn;
        private System.Windows.Forms.TreeView ProcessesTreeView;
        private System.Windows.Forms.Button ExitBtn;
    }
}

