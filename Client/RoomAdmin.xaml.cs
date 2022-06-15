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

namespace Client
{
    /// <summary>
    /// Interaction logic for RoomAdmin.xaml
    /// </summary>
    public partial class RoomAdmin : Window
    {
        Socket _socket;
        public RoomAdmin(Socket soc, string name, int maxUsers, int questionCount, int answerTimeOut)
        {
            InitializeComponent();
            _socket = soc;

            string res = Helper.sendRecieve("{}", 12, _socket);
            RoomStateResponse jsonRes = JsonSerializer.Deserialize<RoomStateResponse>(res)!;

            Title.Text += name;
            MaxUsers.Text += maxUsers;
            QuestionCount.Text += questionCount;
            AnswerTimeout.Text += answerTimeOut;
        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {
            string res = Helper.sendRecieve("{}", 11, _socket);
            Response response = JsonSerializer.Deserialize<Response>(res)!; 
            if (response.status != 0)
            {
                MessageBox.Show("success"); 
            }
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            string res = Helper.sendRecieve("{}", 10, _socket);
            Response response = JsonSerializer.Deserialize<Response>(res)!;
            if (response.status != 0)
            {
                MessageBox.Show("success");
            }
            Main wnd = new Main(_socket);
            Close();
            wnd.ShowDialog();

        }
    }
}
