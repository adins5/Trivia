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

struct RoomData
{
    public int id { get; set; }
    public string name { get; set; }
    public int maxPlayers { get; set; }
    public int numOfQuestionsInGame { get; set; }
    public int timePerQuestion { get; set; }
    public int isActive { get; set; }
}
public class RetRooms
{
    public int status { get; set; }
    private List<RoomData> rooms { get; set; }

    public string getids()
    {
        string ids = "";
        foreach (RoomData room in rooms)
        {
            ids += (char)room.id + "\n";
        }
        return ids;
    }
}

namespace Client
{
    public partial class JoinRoom : Window
    {
        Socket _socket;
        String roomIds = "";
        public JoinRoom(Socket soc)
        {
            InitializeComponent();
            _socket = soc;
            string res = Helper.sendRecieve("{}", 4, _socket);
            RetRooms jsonRes = JsonSerializer.Deserialize<RetRooms>(res)!;
            
            roomNums.Text = roomIds;
        }
        
        private void Join_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomRequest request = new JoinRoomRequest
            {
                RoomId = Int32.Parse(Id.Text)
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
