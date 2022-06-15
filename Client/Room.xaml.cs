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

struct RoomStateResponse {
    public int status { get; set; }
    public bool hasGameBegun { get; set; }
    public string[] players { get; set; }
    public int questionCount { get; set; }
    public int answerTimeOut { get; set; }
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
        public Room(Socket soc)
        {
            InitializeComponent();
            _socket = soc;
            string res = Helper.sendRecieve("{}", 12, _socket);
            jsonRes = JsonSerializer.Deserialize<RoomStateResponse>(res)!;

            AdminName.Text += jsonRes.players[0];

            for (int i = 1; i < jsonRes.players.Length; i++)
            {
                TextBlock tb = new TextBlock();
                tb.Text = jsonRes.players[i];
                PlayerList.Items.Add(tb);
            }
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            string res = Helper.sendRecieve("{}", 13, _socket);
            Main wnd = new Main(_socket);
            Close();
            wnd.ShowDialog();
        }
    }
}
