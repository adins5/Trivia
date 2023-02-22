﻿using System;
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

namespace Client
{
    /// <summary>
    /// Interaction logic for Main.xaml
    /// </summary>
    public partial class Main : Window
    {
        Socket _socket;
        public Main(Socket soc)
        {
            InitializeComponent();
            _socket = soc;
        }

        private void createRoom_Click(object sender, RoutedEventArgs e)
        {
            CreateRoom wnd = new(_socket);
            Close();
            wnd.ShowDialog();
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            JoinRoom wnd = new(_socket);
            Close();
            wnd.ShowDialog();
        }

        private void Statistics_Click(object sender, RoutedEventArgs e)
        {
            Statistics wnd = new(_socket);
            Close();
            wnd.ShowDialog();
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
