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

struct JoinRoomRequest
{
    public int RoomId;
}

public struct RoomData
{
    public int id { get; set; }
    public string name { get; set; }
    public int maxPlayers { get; set; }
    public int questionCount { get; set; }
    public int timePerQuestion { get; set; }
    public int isActive { get; set; }
    public bool gameover { get; set; }
}
public class RetRooms
{
    public int status { get; set; }
    public List<RoomData> rooms { get; set; }
    public List<string> getNames()
    {
        List<string> names = new List<string>();
        if (rooms == null)
            return names;
        foreach (RoomData room in rooms)
        {
            names.Add(room.name);
        }
        return names;
    }
    public int getIdForRoom(string name)
    {
        foreach (RoomData room in rooms)
        {
            if (room.name == name)
                return room.id; 
        }
        return -1;
    }
}

namespace Client
{
    public partial class JoinRoom : Window
    {
        Socket _socket;
        RetRooms jsonRes;
        bool finish; 
        string roomName;
        public JoinRoom(Socket soc)
        {
            InitializeComponent();
            _socket = soc;
            //finish = true;
            string res = Helper.sendRecieve("{}", 4, _socket);
            jsonRes = JsonSerializer.Deserialize<RetRooms>(res)!;

            updateRooms(jsonRes.getNames());

            Thread thread = new Thread(RoomLoop);
            thread.Start();
        }

        ~JoinRoom()
        {
            finish = false;
        }

        private void Join_Click(object sender, RoutedEventArgs e)
        {
            string roomName = RoomList.SelectedValue as string;
            if (roomName == null)
                return;
            JoinRoomRequest request = new JoinRoomRequest
            {
                RoomId = jsonRes.getIdForRoom(roomName)
            };

            string jsonStr = JsonSerializer.Serialize(request);
            string res = Helper.sendRecieve(jsonStr, 8, _socket);

            Response response = JsonSerializer.Deserialize<Response>(res)!;
            if (response.status != 0)
            {
                MessageBox.Show("joining room");
            }

            Room wnd = new Room(_socket, roomName);
            Close();
            wnd.ShowDialog();
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            Main wnd = new Main(_socket);
            Close();
            wnd.ShowDialog();
        }

        private void updateRooms(List<string> names)
        {
            foreach (string name in names)
            {
                TextBlock tb = new TextBlock();
                tb.Text = name;

                RoomList.Items.Add(tb);
            }
        }

        private void RoomLoop()
        {
            while (this.finish)
            {
                string res = Helper.sendRecieve("{}", 4, _socket);
                RetRooms jsonRes = JsonSerializer.Deserialize<RetRooms>(res)!;
                updateRooms(jsonRes.getNames());
                Thread.Sleep(3000);
            }
        }
    }
}
