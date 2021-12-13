import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:rgb_led_tube_app/bluetooth/BluetoothDeviceListEntry.dart';
import 'package:rgb_led_tube_app/bluetooth/discovery_page.dart';
import 'package:rgb_led_tube_app/expansion_panel.dart';
import 'package:rgb_led_tube_app/option_panel.dart';

void main() {
  runApp(rgb_led_app());
}

class rgb_led_app extends StatefulWidget {
  const rgb_led_app({Key? key}) : super(key: key);

  @override
  _rgb_led_app_state createState() => _rgb_led_app_state();
}

class _rgb_led_app_state extends State<rgb_led_app> {
  int selected_index = 2;
  static const List<Widget> _widgetOptions = <Widget>[
    ExpansionPanelHolder(),
    DiscoveryPage(),
    option_panel(),
  ];
  void _onItemTapped(int index) {
    setState(
      () {
        selected_index = index;
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "RGB LED TUBES",
      theme: ThemeData(
        brightness: Brightness.dark,
        primarySwatch: Colors.deepOrange,
      ),
      home: Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text(
            "RGB LED TUBES",
            style: const TextStyle(
              fontSize: 30,
              letterSpacing: 5.0,
            ),
          ),
        ),
        body: Padding(
          padding: EdgeInsets.all(8.0),
          child: _widgetOptions.elementAt(selected_index),
        ),
        bottomNavigationBar: BottomNavigationBar(
          items: <BottomNavigationBarItem>[
            BottomNavigationBarItem(
              icon: Icon(Icons.home),
              label: "Home",
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.bluetooth),
              label: "Bluetooth",
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.settings),
              label: "Settings",
            ),
          ],
          currentIndex: selected_index,
          selectedItemColor: Colors.deepOrange,
          onTap: _onItemTapped,
          elevation: 16.0,
          selectedFontSize: 15,
          unselectedFontSize: 15,
        ),
      ),
    );
  }
}
