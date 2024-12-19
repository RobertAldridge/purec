using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Diagnostics;

namespace TicTacToe
{
	/// <summary>
	/// Summary description for TicTacToe.
	/// </summary>
   public class TicTacToe : System.Windows.Forms.Form
   {
      private System.Windows.Forms.Label Author;

      private System.Windows.Forms.Label Difficulty;
      private System.Windows.Forms.RadioButton Easy;
      private System.Windows.Forms.RadioButton Medium;
      private System.Windows.Forms.RadioButton Hard;
      
      private System.Windows.Forms.CheckBox First;

      private System.Windows.Forms.Button ButtonStart;

      /// <summary>
      /// Required designer variable.
      /// </summary>
      private System.ComponentModel.Container components = null;


      private Image clear;
      private Image o9;
      private Image x9;
      private Image current;

      private int state;
      private int difficulty;
      private bool meFirst;
      private double timeLeft;
      private int row, col;

      private int [,] board;
      private Point mouse = new Point(0,0);
      private Random rand = new Random();
      System.Timers.Timer trigger = new System.Timers.Timer();

      // ... crappy ass utility functions
      private int BoolMark( int inputToCheck, int whatToCheckFor )
      {
         return (int)((inputToCheck==whatToCheckFor)?(1):(0));
      }
      private int BoolMark( bool inputToCheck, bool whatToCheckFor )
      {
         return (byte)((inputToCheck==whatToCheckFor)?(1):(0));
      }
      private bool ArrayWin( int[,] start )
      {
         return ArrayWin(1,start,3)>0 || ArrayWin(2,start,3)>0;
      }
      private int ArrayWin( int turnWho, int[,] start, int numMarksToCheckFor )
      {
         int z1 = BoolMark(start[0,0],0) + BoolMark(start[0,1],0) + BoolMark(start[0,2],0);
         int z2 = BoolMark(start[1,0],0) + BoolMark(start[1,1],0) + BoolMark(start[1,2],0);
         int z3 = BoolMark(start[2,0],0) + BoolMark(start[2,1],0) + BoolMark(start[2,2],0);
         int z4 = BoolMark(start[0,0],0) + BoolMark(start[1,0],0) + BoolMark(start[2,0],0);
         int z5 = BoolMark(start[0,1],0) + BoolMark(start[1,1],0) + BoolMark(start[2,1],0);
         int z6 = BoolMark(start[0,2],0) + BoolMark(start[1,2],0) + BoolMark(start[2,2],0);
         int z7 = BoolMark(start[0,0],0) + BoolMark(start[1,1],0) + BoolMark(start[2,2],0);
         int z8 = BoolMark(start[2,0],0) + BoolMark(start[1,1],0) + BoolMark(start[0,2],0);

         int w1 = BoolMark(start[0,0],turnWho) + BoolMark(start[0,1],turnWho) + BoolMark(start[0,2],turnWho);
         int w2 = BoolMark(start[1,0],turnWho) + BoolMark(start[1,1],turnWho) + BoolMark(start[1,2],turnWho);
         int w3 = BoolMark(start[2,0],turnWho) + BoolMark(start[2,1],turnWho) + BoolMark(start[2,2],turnWho);
         int w4 = BoolMark(start[0,0],turnWho) + BoolMark(start[1,0],turnWho) + BoolMark(start[2,0],turnWho);
         int w5 = BoolMark(start[0,1],turnWho) + BoolMark(start[1,1],turnWho) + BoolMark(start[2,1],turnWho);
         int w6 = BoolMark(start[0,2],turnWho) + BoolMark(start[1,2],turnWho) + BoolMark(start[2,2],turnWho);
         int w7 = BoolMark(start[0,0],turnWho) + BoolMark(start[1,1],turnWho) + BoolMark(start[2,2],turnWho);
         int w8 = BoolMark(start[2,0],turnWho) + BoolMark(start[1,1],turnWho) + BoolMark(start[0,2],turnWho);

         return (int)(
            BoolMark(w1==numMarksToCheckFor && w1+z1==3,true) +
            BoolMark(w2==numMarksToCheckFor && w2+z2==3,true) +
            BoolMark(w3==numMarksToCheckFor && w3+z3==3,true) +
            BoolMark(w4==numMarksToCheckFor && w4+z4==3,true) +
            BoolMark(w5==numMarksToCheckFor && w5+z5==3,true) +
            BoolMark(w6==numMarksToCheckFor && w6+z6==3,true) +
            BoolMark(w7==numMarksToCheckFor && w7+z7==3,true) +
            BoolMark(w8==numMarksToCheckFor && w8+z8==3,true)
            );
      }


      private struct clipData
      {
         public static PointF [] clipPoints = new PointF[16];

         public static PointF [,][] clipGroups = {  {null,null,null},
                                                    {null,null,null},
                                                    {null,null,null}
                                                 };

         public static Rectangle [][] invalidateGroups = {  null,
                                                            null,
                                                            null
                                                         };

         public static byte [] dummyBytes = {  (byte)PathPointType.Start,
                                               (byte)PathPointType.Line,
                                               (byte)PathPointType.Line,
                                               (byte)PathPointType.Line,
                                               (byte)PathPointType.Line
                                            };

         public static void init()
         {
            clipPoints[0]=new PointF(0,0);
            /**/clipPoints[1]=new PointF(305,0);
            /**//**/clipPoints[2]=new PointF(494,0);
            /**//**//**/clipPoints[3]=new PointF(799,0);

            clipPoints[4]=new PointF(0,166);
            /**/clipPoints[5]=new PointF(298.35F,166);
            /**//**/clipPoints[6]=new PointF(500.65F,166);
            /**//**//**/clipPoints[7]=new PointF(799,166);

            clipPoints[8]=new PointF(0,353);
            /**/clipPoints[9]=new PointF(290.86F,353);
            /**//**/clipPoints[10]=new PointF(508.14F,353);
            /**//**//**/clipPoints[11]=new PointF(799,353);

            clipPoints[12]=new PointF(0,599);
            /**/clipPoints[13]=new PointF(281,599);
            /**//**/clipPoints[14]=new PointF(518,599);
            /**//**//**/clipPoints[15]=new PointF(799,599);

            clipGroups[0,0]=new PointF[5]{clipPoints[0],clipPoints[4],clipPoints[5],clipPoints[1],clipPoints[0]};
            /**/clipGroups[0,1]=new PointF[5]{clipPoints[1],clipPoints[5],clipPoints[6],clipPoints[2],clipPoints[1]};
            /**//**/clipGroups[0,2]=new PointF[5]{clipPoints[2],clipPoints[6],clipPoints[7],clipPoints[3],clipPoints[2]};

            clipGroups[1,0]=new PointF[5]{clipPoints[4],clipPoints[8],clipPoints[9],clipPoints[5],clipPoints[4]};
            /**/clipGroups[1,1]=new PointF[5]{clipPoints[5],clipPoints[9],clipPoints[10],clipPoints[6],clipPoints[5]};
            /**//**/clipGroups[1,2]=new PointF[5]{clipPoints[6],clipPoints[10],clipPoints[11],clipPoints[7],clipPoints[6]};

            clipGroups[2,0]=new PointF[5]{clipPoints[8],clipPoints[12],clipPoints[13],clipPoints[9],clipPoints[8]};
            /**/clipGroups[2,1]=new PointF[5]{clipPoints[9],clipPoints[13],clipPoints[14],clipPoints[10],clipPoints[9]};
            /**//**/clipGroups[2,2]=new PointF[5]{clipPoints[10],clipPoints[14],clipPoints[15],clipPoints[11],clipPoints[10]};

            invalidateGroups[0]=new Rectangle[3]{  new Rectangle(0,0,306,167),
                                                   new Rectangle(298,0,204,167),
                                                   new Rectangle(494,0,306,167)
                                                };

            invalidateGroups[1]=new Rectangle[3]{  new Rectangle(0,166,299,188),
                                                   new Rectangle(290,166,219,188),
                                                   new Rectangle(500,166,300,188)
                                                };

            invalidateGroups[2]=new Rectangle[3]{  new Rectangle(0,353,291,247),
                                                   new Rectangle(281,353,238,247),
                                                   new Rectangle(508,353,292,247)
                                                };
         }
         public static void term()
         {
         }
      };
      


      private struct hugeTable
      {
         private static int [,,,,,,,,] countBest = new int[3,3,3,3,3,3,3,3,3];
         private static int [,,,,,,,,] countAll = new int[3,3,3,3,3,3,3,3,3];
         private static double [,,,,,,,,] weightBest = new double[3,3,3,3,3,3,3,3,3];
         private static double [,,,,,,,,][] weights = new double[3,3,3,3,3,3,3,3,3][];
         private static int [,,,,,,,,][][,] matches = new int[3,3,3,3,3,3,3,3,3][][,];

         public static void init()
         {
            Array.Clear(weightBest,0,weightBest.Length);
            Array.Clear(countBest,0,countBest.Length);
            Array.Clear(countAll,0,countAll.Length);
            Array.Clear(weights,0,weights.Length);
            Array.Clear(matches,0,matches.Length);

            StreamReader file = new StreamReader(@"sorted_start_weight_end_hi2low.txt");
            while(file.Peek()>=0)
            {
               string match = file.ReadLine();

               string m = match.Substring(0,9);
               string n = match.Substring(10,9);
               double weight = System.Convert.ToDouble(match.Remove(0,20));

               if(countBest[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']==0)
                  weightBest[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']=weight;

               if(Math.Abs(weightBest[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']-weight)<0.0000001)
                  countBest[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']++;

               countAll[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']++;
            }
            file.Close();

            int weightIndex=0;
            int matchIndex=0;

            file = new StreamReader(@"sorted_start_weight_end_hi2low.txt");
            while(file.Peek()>=0)
            {
               string match = file.ReadLine();

               string m = match.Substring(0,9);
               string n = match.Substring(10,9);
               double weight = System.Convert.ToDouble(match.Remove(0,20));

               if(weights[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']==null)
               {
                  weightIndex=0;
                  weights[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']=new double[countAll[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']];
               }

               weights[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0'][weightIndex++]=weight;

               if(matches[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']==null)
               {
                  matchIndex=0;
                  matches[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']=new int[countAll[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0']][,];
               }

               matches[m[0]-'0',m[1]-'0',m[2]-'0',m[3]-'0',m[4]-'0',m[5]-'0',m[6]-'0',m[7]-'0',m[8]-'0'][matchIndex++]=new int[,]{{n[0]-'0',n[1]-'0',n[2]-'0'},{n[3]-'0',n[4]-'0',n[5]-'0'},{n[6]-'0',n[7]-'0',n[8]-'0'}};
            }
            file.Close();
         }

         public static void term()
         {
            // ah well it's no biggie-this data only gets released at end of application so no need to do that myself when C# does it anyway
         }


         public static bool checkValidity(int [,] before,int [,] after)
         {
            if(matches[before[0,0],before[0,1],before[0,2],before[1,0],before[1,1],before[1,2],before[2,0],before[2,1],before[2,2]]!=null)
               for(int i=0;i<countAll[before[0,0],before[0,1],before[0,2],before[1,0],before[1,1],before[1,2],before[2,0],before[2,1],before[2,2]];i++)
               {
                  int [,] check = matches[before[0,0],before[0,1],before[0,2],before[1,0],before[1,1],before[1,2],before[2,0],before[2,1],before[2,2]][i];

                  if((after[0,0]==check[0,0])&&(after[0,1]==check[0,1])&&(after[0,2]==check[0,2])&&
                     (after[1,0]==check[1,0])&&(after[1,1]==check[1,1])&&(after[1,2]==check[1,2])&&
                     (after[2,0]==check[2,0])&&(after[2,1]==check[2,1])&&(after[2,2]==check[2,2])
                    )
                     return true;
               }

            return false;
         }

         public static Point getBestMove(int [,] before,int difficulty,ref Random rand)
         {
            int possibleMoves;

            if(difficulty==0 || (difficulty==1 && rand.Next(2)==0))
               possibleMoves = countAll[before[0,0],before[0,1],before[0,2],before[1,0],before[1,1],before[1,2],before[2,0],before[2,1],before[2,2]];
            else
               possibleMoves = countBest[before[0,0],before[0,1],before[0,2],before[1,0],before[1,1],before[1,2],before[2,0],before[2,1],before[2,2]];

            int moveToMake = rand.Next(possibleMoves);

            int [,] after = matches[before[0,0],before[0,1],before[0,2],before[1,0],before[1,1],before[1,2],before[2,0],before[2,1],before[2,2]][moveToMake];

            if(before[0,0]!=after[0,0])return new Point(150,100);
            if(before[0,1]!=after[0,1])return new Point(400,100);
            if(before[0,2]!=after[0,2])return new Point(600,100);

            if(before[1,0]!=after[1,0])return new Point(150,250);
            if(before[1,1]!=after[1,1])return new Point(400,250);
            if(before[1,2]!=after[1,2])return new Point(600,250);

            if(before[2,0]!=after[2,0])return new Point(150,450);
            if(before[2,1]!=after[2,1])return new Point(400,450);
            if(before[2,2]!=after[2,2])return new Point(600,450);

            Debug.Assert(false);
            return new Point(0,0);
         }
      };



      public TicTacToe()
      {
         //
         // Required for Windows Form Designer support
         //
         InitializeComponent();

         //
         // TODO: Add any constructor code after InitializeComponent call
         //
         this.state = 0;
         this.switchCase();
      }


      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      protected override void Dispose( bool disposing )
      {
         if( disposing )
         {
            if (components != null) 
            {
               this.state = -1;
               this.switchCase();

               components.Dispose();
            }
         }
         base.Dispose( disposing );
      }


      #region Windows Form Designer generated code
      /// <summary>
      /// Required method for Designer support - do not modify
      /// the contents of this method with the code editor.
      /// </summary>
      private void InitializeComponent()
      {
         this.Author = new System.Windows.Forms.Label();
         this.Easy = new System.Windows.Forms.RadioButton();
         this.Medium = new System.Windows.Forms.RadioButton();
         this.Hard = new System.Windows.Forms.RadioButton();
         this.Difficulty = new System.Windows.Forms.Label();
         this.ButtonStart = new System.Windows.Forms.Button();
         this.First = new System.Windows.Forms.CheckBox();
         this.SuspendLayout();
         // 
         // Author
         // 
         this.Author.BackColor = System.Drawing.Color.Transparent;
         this.Author.CausesValidation = false;
         this.Author.Font = new System.Drawing.Font("Courier New", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Author.ForeColor = System.Drawing.Color.FromArgb(((System.Byte)(224)), ((System.Byte)(224)), ((System.Byte)(224)));
         this.Author.Location = new System.Drawing.Point(8, 8);
         this.Author.Name = "Author";
         this.Author.Size = new System.Drawing.Size(560, 24);
         this.Author.TabIndex = 0;
         this.Author.Text = "Neural Networks Tic-Tac-Toe By Robert Aldridge";
         // 
         // Easy
         // 
         this.Easy.BackColor = System.Drawing.Color.Transparent;
         this.Easy.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Easy.ForeColor = System.Drawing.Color.Red;
         this.Easy.Location = new System.Drawing.Point(8, 104);
         this.Easy.Name = "Easy";
         this.Easy.Size = new System.Drawing.Size(88, 24);
         this.Easy.TabIndex = 2;
         this.Easy.TabStop = true;
         this.Easy.Text = "Easy";
         // 
         // Medium
         // 
         this.Medium.BackColor = System.Drawing.Color.Transparent;
         this.Medium.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Medium.ForeColor = System.Drawing.Color.Red;
         this.Medium.Location = new System.Drawing.Point(8, 128);
         this.Medium.Name = "Medium";
         this.Medium.Size = new System.Drawing.Size(88, 24);
         this.Medium.TabIndex = 3;
         this.Medium.TabStop = true;
         this.Medium.Text = "Medium";
         // 
         // Hard
         // 
         this.Hard.BackColor = System.Drawing.Color.Transparent;
         this.Hard.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Hard.ForeColor = System.Drawing.Color.Red;
         this.Hard.Location = new System.Drawing.Point(8, 152);
         this.Hard.Name = "Hard";
         this.Hard.Size = new System.Drawing.Size(88, 24);
         this.Hard.TabIndex = 4;
         this.Hard.TabStop = true;
         this.Hard.Text = "Hard";
         // 
         // Difficulty
         // 
         this.Difficulty.BackColor = System.Drawing.Color.Transparent;
         this.Difficulty.CausesValidation = false;
         this.Difficulty.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.Difficulty.ForeColor = System.Drawing.Color.Lime;
         this.Difficulty.Location = new System.Drawing.Point(8, 56);
         this.Difficulty.Name = "Difficulty";
         this.Difficulty.Size = new System.Drawing.Size(120, 40);
         this.Difficulty.TabIndex = 1;
         this.Difficulty.Text = "Choose Difficulty:";
         // 
         // ButtonStart
         // 
         this.ButtonStart.BackColor = System.Drawing.Color.DimGray;
         this.ButtonStart.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.ButtonStart.ForeColor = System.Drawing.Color.LightGray;
         this.ButtonStart.Location = new System.Drawing.Point(8, 232);
         this.ButtonStart.Name = "ButtonStart";
         this.ButtonStart.Size = new System.Drawing.Size(72, 32);
         this.ButtonStart.TabIndex = 6;
         this.ButtonStart.Text = "Start";
         this.ButtonStart.Click += new System.EventHandler(this.ButtonStart_Click);
         // 
         // First
         // 
         this.First.BackColor = System.Drawing.Color.Transparent;
         this.First.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
         this.First.ForeColor = System.Drawing.Color.Red;
         this.First.Location = new System.Drawing.Point(8, 192);
         this.First.Name = "First";
         this.First.TabIndex = 5;
         this.First.Text = "Me First";
         // 
         // TicTacToe
         // 
         this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
         this.BackColor = System.Drawing.Color.Black;
         this.ClientSize = new System.Drawing.Size(800, 600);
         this.Controls.Add(this.First);
         this.Controls.Add(this.ButtonStart);
         this.Controls.Add(this.Difficulty);
         this.Controls.Add(this.Hard);
         this.Controls.Add(this.Medium);
         this.Controls.Add(this.Easy);
         this.Controls.Add(this.Author);
         this.Name = "TicTacToe";
         this.Text = "Neural Networks Tic-Tac-Toe";
         this.ResumeLayout(false);

      }
      #endregion

      /// <summary>
      /// The main entry point for the application.
      /// </summary>
      [STAThread]
      static void Main() 
      {
         Application.Run(new TicTacToe());
      }



      private void casen1()
      {
         this.MouseUp -= new MouseEventHandler(this.TicTacToe_MouseUp);
         this.BackgroundImage = null;
         this.current.Dispose();
         this.o9.Dispose();
         this.x9.Dispose();
         this.clear.Dispose();
         TicTacToe.hugeTable.term();
         TicTacToe.clipData.term();
      }


      private void case0()
      {
         TicTacToe.clipData.init();
         TicTacToe.hugeTable.init();
         this.clear = Image.FromFile(@"clear_800_600.bmp",false);
         this.x9 = Image.FromFile(@"x9_800_600.bmp",false);
         this.o9 = Image.FromFile(@"o9_800_600.bmp",false);
         this.current = (Image)this.clear.Clone();
         this.BackgroundImage = this.current;
         this.MouseUp += new MouseEventHandler(this.TicTacToe_MouseUp);
         this.board = new int[,]{{0,0,0},{0,0,0},{0,0,0}};
      }


      private void casep1()
      {
         this.BackgroundImage = null;
         this.current.Dispose();
         this.current = (Image)this.clear.Clone();
         this.BackgroundImage = this.current;
         this.board = new int[,]{{0,0,0},{0,0,0},{0,0,0}};
         this.trigger.Dispose();
         this.trigger = new System.Timers.Timer();
      }


      private void casep2()
      {
         bool test1 = this.Easy.Checked;
         bool test2 = this.Medium.Checked;
         bool test3 = this.Hard.Checked;
         bool test4 = this.First.Checked;

         if(test1)this.difficulty=0;
         if(test2)this.difficulty=1;
         if(test3)this.difficulty=2;
         this.meFirst=test4;
      }


      private void computeMousePoint()
      {
         this.mouse = TicTacToe.hugeTable.getBestMove(this.board,this.difficulty,ref this.rand);
      }
      private bool inputTransform(int whoseTurn)
      {
         this.row=2;
         if(this.mouse.Y<=166)
            this.row=0;
         else if(this.mouse.Y<=353)
            this.row=1;

         double i = (double)this.mouse.Y/599.0;
         int x0 = (int)(305.0+(281.0-305.0)*i);
         int x1 = (int)(494.0+(518.0-494.0)*i);
         if(x0>x1)
         {x0+=x1;x1=x0-x1;x0-=x1;}

         this.col=2;
         if(this.mouse.X<=x0)
            this.col=0;
         else if(this.mouse.X<=x1)
            this.col=1;

         int [,] after = (int[,])this.board.Clone();
         after[row,col] = whoseTurn;

         if(!TicTacToe.hugeTable.checkValidity(this.board,after))
            return false;

         this.board[row,col]=whoseTurn;
         return true;
      }

      private void TicTacToe_Start_x(object sender,System.Timers.ElapsedEventArgs e)
      {
         this.switchCase();
      }
      private bool casep3()
      {
         // if human opponent then they clicked, otherwise it is the computer's turn
         if(this.trigger.Enabled)
         {
            this.trigger.Enabled = false;
            this.trigger.Elapsed -= new System.Timers.ElapsedEventHandler(this.TicTacToe_Start_x);

            if(!this.meFirst)
               this.computeMousePoint();
         }

         if(!this.inputTransform(1))
            return false;

         this.timeLeft = 3.0;
         this.trigger.Elapsed += new System.Timers.ElapsedEventHandler(this.TicTacToe_Elapsed_x);
         this.trigger.Interval = 30;
         this.trigger.Enabled = true;
         return true;
      }


      private void TicTacToe_Start_o(object sender,System.Timers.ElapsedEventArgs e)
      {
         this.switchCase();
      }
      private bool casep5()
      {
         if(this.trigger.Enabled)
         {
            this.trigger.Enabled = false;
            this.trigger.Elapsed -= new System.Timers.ElapsedEventHandler(this.TicTacToe_Start_o);

            if(this.meFirst)
               this.computeMousePoint();
         }

         if(!this.inputTransform(2))
            return false;

         this.timeLeft = 3.0;
         this.trigger.Elapsed += new System.Timers.ElapsedEventHandler(this.TicTacToe_Elapsed_o);
         this.trigger.Interval = 30;
         this.trigger.Enabled = true;
         return true;
      }

      
      private void TicTacToe_Elapsed_x(object sender,System.Timers.ElapsedEventArgs e)
      {
         this.timeLeft -= 4.0;
         if(this.timeLeft<=0)
         {
            this.timeLeft = 0;
            trigger.Enabled = false;
            trigger.Elapsed -= new System.Timers.ElapsedEventHandler(this.TicTacToe_Elapsed_x);
            this.switchCase();
            this.state = 5;

            if(this.ArrayWin(this.board))
            {
               Invalidate(TicTacToe.clipData.invalidateGroups[row][col],false);
               this.casep7();
            }

            if(this.meFirst)
            {
               this.trigger.Elapsed += new System.Timers.ElapsedEventHandler(this.TicTacToe_Start_o);
               this.trigger.Interval = 30;
               this.trigger.Enabled = true;
            }
         }
         else
            this.switchCase();

         Invalidate(TicTacToe.clipData.invalidateGroups[row][col],false);
      }
      private void TicTacToe_Elapsed_o(object sender,System.Timers.ElapsedEventArgs e)
      {
         this.timeLeft -= 4.0;
         if(this.timeLeft<=0)
         {
            this.timeLeft = 0;
            trigger.Enabled = false;
            trigger.Elapsed -= new System.Timers.ElapsedEventHandler(this.TicTacToe_Elapsed_o);
            this.switchCase();
            this.state = 3;

            if(this.ArrayWin(this.board))
            {
               Invalidate(TicTacToe.clipData.invalidateGroups[row][col],false);
               this.casep7();
            }

            if(!this.meFirst)
            {
               this.trigger.Elapsed += new System.Timers.ElapsedEventHandler(this.TicTacToe_Start_x);
               this.trigger.Interval = 30;
               this.trigger.Enabled = true;
            }
         }
         else
            this.switchCase();

         Invalidate(TicTacToe.clipData.invalidateGroups[row][col],false);
      }


      private void casep4()
      {
         this.trigger.Enabled=false;
         Graphics g = Graphics.FromImage(this.BackgroundImage);
         g.Clip = new Region(new GraphicsPath(TicTacToe.clipData.clipGroups[row,col],TicTacToe.clipData.dummyBytes));
         g.DrawImage(this.x9,new Point(0,0));
         System.Threading.Thread.Sleep(30);
         g.Clip.Dispose();
         g.Dispose();
         this.trigger.Enabled=true;
      }


      private void casep6()
      {
         this.trigger.Enabled=false;
         Graphics g = Graphics.FromImage(this.BackgroundImage);
         g.Clip = new Region(new GraphicsPath(TicTacToe.clipData.clipGroups[row,col],TicTacToe.clipData.dummyBytes));
         g.DrawImage(this.o9,new Point(0,0));
         System.Threading.Thread.Sleep(30);
         g.Clip.Dispose();
         g.Dispose();
         this.trigger.Enabled=true;
      }



      private void casep7()
      {
         if(this.ArrayWin(1,this.board,3)>0&&this.meFirst || this.ArrayWin(2,this.board,3)>0&&(!this.meFirst))
            MessageBox.Show("You have won", "End of Game", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
         else
            MessageBox.Show("You have lost", "End of Game", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }




      private void switchCase()
      {
         // state -2 [just after shutting down application]
         // state -1 [just before shutting down] application ends
         // state 0 [very first initialization] switches to state 2
         // state 1 [while restarting game] switches to state 2
         // state 2 [just after starting up, while menu] loads menu choices into appropriate variables, switches to state 3
         // state 3 [while playing, X's turn, before picking move] switch to state 4
         // state 4 [transition state, X's turn, X being placed on board] switches to state 5 or 7
         // state 5 [while playing, O's turn, before picking move] switch to state 6
         // state 6 [transition state, O's turn, O being placed on board] switch to state 3 or 7
         // state 7 [end of game, pop up box describing who won/lost & click to go back to menu] switches to state 0

         // if start game button is pressed while state is >= 2 then call state 1's restart function, reload menu choices into appropriate variables [function from state 2], and immediately switch to state 3 [same as switch states 1=>2=>3, except you are not waiting for the client to click start, it matters because if the computer goes first then he will immediately go instead of after pressing the start button

         // if application is closing [e.g. pressing x button in non-client area] then call state -1's clean up function and let application terminate [place call to clean up function in application's termination function]

         switch(state)
         {
            case -1:this.casen1();this.state=-2;break; // termination
            case 0:this.case0();this.state=2;break;    // creation
            case 1:this.casep1();this.state=2;break;   // restart
            case 2:this.casep2();break;                // menu [here don't switch state until click]
            case 3:
               if(this.casep3())
                  this.state=4;
               break;   // game; X's turn [here don't switch state until click if human turn]
            case 4:this.casep4();break;                // transition; X's turn; no user interaction processed during this state
            case 5:
               if(this.casep5())
                  this.state=6;
               break;   // game; O's turn [here don't switch state until click if human turn]
            case 6:this.casep6();break;                // transition; O's turn; no user interaction processed during this state
            case 7:this.casep7();break;                // end of game [here don't switch state until click]
         }
      }

      private void TicTacToe_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
      {
         this.mouse.X = e.X;
         this.mouse.Y = e.Y;
         this.switchCase();
      }

      private void ButtonStart_Click(object sender, System.EventArgs e)
      {
         if(this.state == 2)
         {
            this.switchCase();
            this.state = 3;
            
            if(!this.meFirst)
            {
               this.trigger.Elapsed += new System.Timers.ElapsedEventHandler(this.TicTacToe_Start_x);
               this.trigger.Interval = 30;
               this.trigger.Enabled = true;
            }
         }
         else if(this.state > 2)
         {
            this.casep1();
            this.casep2();
            this.state = 3;

            if(!this.meFirst)
            {
               this.trigger.Elapsed += new System.Timers.ElapsedEventHandler(this.TicTacToe_Start_x);
               this.trigger.Interval = 30;
               this.trigger.Enabled = true;
            }
         }
      }
   }
}
