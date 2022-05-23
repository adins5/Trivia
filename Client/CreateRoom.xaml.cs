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

struct CreateRoomRequest
{
    public string roomName { get; set; }
    public int maxUsers { get; set; }
    public int questionCount { get; set; }
    public int answerTimeout { get; set; }
};

namespace Client
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        Socket _socket;
        public CreateRoom(Socket soc)
        {
            InitializeComponent();
            _socket = soc;
        }

        private void Create_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomRequest request = new CreateRoomRequest
            {
                roomName = name.Text,
                maxUsers = Int32.Parse(numPlayers.Text),
                questionCount = Int32.Parse(numQuestions.Text),
                answerTimeout = Int32.Parse(time.Text)
            };

            string jsonStr = JsonSerializer.Serialize(request);
            string res = Helper.sendRecieve(jsonStr, 9, _socket);
            Response jsonRes = JsonSerializer.Deserialize<Response>(res)!;

        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
