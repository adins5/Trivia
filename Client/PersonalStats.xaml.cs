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
    struct PersonalStatsResponse
    {
        public int status { get; set; }
        public List<string> statistics { get; set; }
    }
        /// <summary>
        /// Interaction logic for PersonalStats.xaml
        /// </summary>
        public partial class PersonalStats : Window
    {
        Socket _socket;

        public PersonalStats(Socket soc)
        {
            InitializeComponent();
            _socket = soc;
            string res = Helper.sendRecieve("{}", 7, _socket);
            PersonalStatsResponse jsonRes = JsonSerializer.Deserialize<PersonalStatsResponse>(res)!;
            Games.Text = "number of games:" + jsonRes.statistics[0];
            Correct.Text = "number of correct answers: " + jsonRes.statistics[1];
            Incorrect.Text = "number of incorrect answers: " + jsonRes.statistics[2];
            AvTime.Text = "average answer time: " + jsonRes.statistics[3];
        }

        private void Menu_Click(object sender, RoutedEventArgs e)
        {
            Main wnd = new Main(_socket);
            Close();
            wnd.ShowDialog();
        }
    }
}
