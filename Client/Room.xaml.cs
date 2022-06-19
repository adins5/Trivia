using System;
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

public struct RoomStateResponse {
    public int status { get; set; }
    public bool hasGameBegun { get; set; }
    public string[] players { get; set; }
    public int questionCount { get; set; }
    public int answerTimeOut { get; set; }
    public bool gameOver { get; set; }
}

namespace Client
{
    /// <summary>
    /// Interaction logic for room.xaml
    /// </summary>
    public partial class Room : Window
    {
        Socket _socket;
        RoomStateResponse jsonRes;
        public Room(Socket soc, string name)
        {
            InitializeComponent();
            _socket = soc;
            string res = Helper.sendRecieve("{}", 12, _socket);
            jsonRes = JsonSerializer.Deserialize<RoomStateResponse>(res)!;

            Title.Text += ' ' + name;
            AdminName.Text += jsonRes.players[0];
            QuestionCount.Text += jsonRes.questionCount;
            AnswerTimeout.Text += jsonRes.answerTimeOut;

            Helper.updatePlayerList(PlayerList, jsonRes.players);

            Thread thread = new Thread(refreshLoop);
            thread.Start();

        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            string res = Helper.sendRecieve("{}", 13, _socket);
            Response response = JsonSerializer.Deserialize<Response>(res)!;
            if (response.status != 0)
            {
                MessageBox.Show("success");
            }
            Main wnd = new Main(_socket);
            Close();
            wnd.ShowDialog();
        }

        private void refreshLoop()
        {
            while (true)
            {
                string res = Helper.sendRecieve("{}", 12, _socket);
                jsonRes = JsonSerializer.Deserialize<RoomStateResponse>(res)!;
                if (jsonRes.gameOver)
                {
                    Helper.sendRecieve("{}", 13, _socket);
                    MessageBox.Show("room was closed");
                    Main wnd = new Main(_socket);
                    Close();
                    wnd.ShowDialog();
                }
                Helper.updatePlayerList(PlayerList, jsonRes.players);
                Thread.Sleep(3000);
            }
        }
    }
}
