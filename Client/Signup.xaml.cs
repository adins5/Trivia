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

public class SignupMsg
{
    public string username { get; set; }
    public string password { get; set; }
    public string email { get; set; }
}


namespace Client
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Window
    {
        Socket _socket;
        public Signup(Socket soc)
        {
            InitializeComponent();
            _socket = soc;        
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void Signup_Click(object sender, RoutedEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(name.Text) && !string.IsNullOrWhiteSpace(pass.Text) && !string.IsNullOrWhiteSpace(email.Text))
            {
                var signupjson = new SignupMsg
                {
                    username = name.Text,
                    password = pass.Text,
                    email = email.Text
                };
                string jsonStr = JsonSerializer.Serialize(signupjson);
                string signupStr = '2' + jsonStr.Length.ToString().PadLeft(4, '0') + jsonStr;
                _socket.Send(Encoding.ASCII.GetBytes(signupStr));

                byte[] recv = new byte[1024];
                _socket.ReceiveTimeout = 10000;
                _socket.Receive(recv);
                string res = Encoding.ASCII.GetString(recv);
                res = res.Substring(5, res.Length - 5);
                int msgLen = Int32.Parse(Encoding.ASCII.GetString(recv).Substring(1, 4));
                Response jsonRes = JsonSerializer.Deserialize<Response>(res.Substring(0, msgLen))!;

                if (jsonRes.status == 1)
                {
                    Main wnd = new();
                    Close();
                    MessageBox.Show("New acount created!", "Signup Succesfull", MessageBoxButton.OK, MessageBoxImage.Information);
                    wnd.ShowDialog();
                    return;
                }
            }
            MessageBox.Show("invalid paremeters!", "Signup Failed", MessageBoxButton.OK, MessageBoxImage.Error);
        }

        private void Login_Click(object sender, RoutedEventArgs e)
        {
            Login wnd = new();
            Close();
            wnd.ShowDialog();
        }

    }
}
