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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Window
    {
        Socket _socket;
        public Statistics(Socket soc)
        {
            InitializeComponent();
            _socket = soc;
        }


        private void P_Click(object sender, RoutedEventArgs e)
        {
            PersonalStats wnd = new PersonalStats(_socket);
            Close();
            wnd.ShowDialog();
        }

        private void H_Click(object sender, RoutedEventArgs e)
        {
            HighScore wnd = new HighScore(_socket);
            Close();
            wnd.ShowDialog();
        }
    }
}
