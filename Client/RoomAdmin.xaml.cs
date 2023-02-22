﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;


using System.Net.Sockets;
using System.Net;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.IO;
using System.Threading;

namespace Client
{
    /// <summary>
    /// Interaction logic for RoomAdmin.xaml
    /// </summary>
    public partial class RoomAdmin : Window
    {
        Socket _socket;
        RoomStateResponse jsonRes;
        bool finish;
        public RoomAdmin(Socket soc, string name, int maxUsers, int questionCount, int answerTimeOut)
        {
            InitializeComponent();
            _socket = soc;

            string res = Helper.sendRecieve("{}", 12, _socket);
            jsonRes = JsonSerializer.Deserialize<RoomStateResponse>(res)!;

            Title.Text += ' ' + name;
            MaxUsers.Text += maxUsers;
            QuestionCount.Text += questionCount;
            AnswerTimeout.Text += answerTimeOut;
            finish = false;

            Helper.updatePlayerList(PlayerList, jsonRes.players);

            Thread thread = new Thread(RefreshLoop);

            thread.Start();
        }

        ~RoomAdmin()
        {
            finish = false;
        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {
            string res = Helper.sendRecieve("{}", 11, _socket);
            Response response = JsonSerializer.Deserialize<Response>(res)!; 
            if (response.status != 0)
            {
                MessageBox.Show("game started"); 
            }
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            string res = Helper.sendRecieve("{}", 10, _socket);
            Response response = JsonSerializer.Deserialize<Response>(res)!;
            if (response.status != 0)
            {
                MessageBox.Show("room closed");
            }
            Main wnd = new Main(_socket);
            Close();
            wnd.ShowDialog();

        }
        private void RefreshLoop()
        {
            while (this.finish)
            {
                string res = Helper.sendRecieve("{}", 12, _socket);
                jsonRes = JsonSerializer.Deserialize<RoomStateResponse>(res)!;
                
                Helper.updatePlayerList(PlayerList, jsonRes.players);
           
                Thread.Sleep(3000);
            }
        }
    }
}
