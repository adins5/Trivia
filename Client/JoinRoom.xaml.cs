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

struct JoinRoomRequest
{
    public int RoomId;
}

namespace Client
{
    public partial class JoinRoom : Window
    {
        Socket _socket;
        public JoinRoom(Socket soc)
    {
        InitializeComponent();
        _socket = soc;
    }

        private void Create_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomRequest request = new JoinRoomRequest
            {
                RoomId = Int32.Parse(roomNum.Text)
            };

            string jsonStr = JsonSerializer.Serialize(request);
            string res = Helper.sendRecieve(jsonStr, 8, _socket);
            Response jsonRes = JsonSerializer.Deserialize<Response>(res)!;
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
