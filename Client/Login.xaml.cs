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

public class Response
{
    public int status { get; set; }
}
public class LoginMsg
{
    public string username { get; set; }
    public string password { get; set; }
}

namespace Client
{
    /// <summary>
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Window
    {
        Dictionary<string, string> _loginData = new Dictionary<string, string>();
        Socket _socket;
        public Login()
        {
            InitializeComponent();
            IPAddress ipa = IPAddress.Parse("127.0.0.1");
            IPEndPoint ipe = new IPEndPoint(ipa, 2022);
            _socket = new Socket(ipe.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            _socket.Connect(ipe);
            
        }

        private void Login_Click(object sender, RoutedEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(name.Text) && !string.IsNullOrWhiteSpace(pass.Text))
            {
                var loginjson = new LoginMsg
                {
                    username = name.Text,
                    password = pass.Text,
                };
                string jsonStr = JsonSerializer.Serialize(loginjson);
                string res = Helper.sendRecieve(jsonStr, 1, _socket);
                Response jsonRes = JsonSerializer.Deserialize<Response>(res)!;

                if (jsonRes.status == 1)
                {   
                    Main wnd = new(_socket);
                    Close();
                    wnd.ShowDialog();
                    return;
                }
            }
            MessageBox.Show("username or password incorect!", "Login Failed", MessageBoxButton.OK, MessageBoxImage.Error);
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void Singup_Click(object sender, RoutedEventArgs e)
        {
            Signup wnd = new Signup(_socket);
            Close();
            wnd.ShowDialog();
        }

    }
    class Helper
    {
        public static string sendRecieve(string jsonStr, int code, Socket _socket)
        {
            string loginStr = code.ToString() + jsonStr.Length.ToString().PadLeft(4, '0') + jsonStr;
            _socket.Send(Encoding.ASCII.GetBytes(loginStr));

            byte[] recv = new byte[1024];
            _socket.Receive(recv);
            string res = Encoding.ASCII.GetString(recv);
            res = res.Substring(5, res.Length - 5);
            int msgLen = Int32.Parse(Encoding.ASCII.GetString(recv).Substring(1, 4));

            return res.Substring(0, msgLen);
        }
    }
}

