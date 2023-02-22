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

struct HighScoreResponse
{
    public int status { get; set; }
    public string[][] statistics { get; set; }
}

namespace Client
{
    /// <summary>
    /// Interaction logic for HighScore.xaml
    /// </summary>
    public partial class HighScore : Window
    {
        Socket _socket;
        public HighScore(Socket soc)
        {
            InitializeComponent();
            _socket = soc;
            string res = Helper.sendRecieve("{}", 6, _socket);
            HighScoreResponse jsonRes = JsonSerializer.Deserialize<HighScoreResponse>(res)!;

            foreach (string[] player in jsonRes.statistics)
            {
                TextBlock tb = new TextBlock();
                tb.Text += player[0];
                tb.Text += " <-> ";
                tb.Text += player[1];
                tb.TextAlignment = TextAlignment.Center;
                tb.FontSize = 20;
                Players.Children.Add(tb);
            }
        }

        private void Menu_Click(object sender, RoutedEventArgs e)
        {
            Main wnd = new Main(_socket);
            Close();
            wnd.ShowDialog();
        }
    }

}
