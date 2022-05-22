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
        public Signup()
        {
            InitializeComponent();
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

                string res = "";

                if (res != null)
                {
                    Main wnd = new();
                    Close();
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
