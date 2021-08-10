import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:rgb_led_tube_app/expansion_panel.dart';

void main() {
  runApp(rgb_led_app());
}

class rgb_led_app extends StatelessWidget {
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
          drawer: Drawer(
            child: ListView(
              padding: const EdgeInsets.all(8.0),
              children: <Widget>[
                DrawerHeader(
                  child: const Text(
                    'Options',
                    style: const TextStyle(
                      color: Colors.white,
                      fontSize: 24,
                    ),
                  ),
                ),
                ListTile(
                  leading: const Icon(Icons.bluetooth),
                  title: const Text("Connect BT-Deveice"),
                  onTap: () {},
                )
              ],
            ),
          ),
          body: ExpansionPanelHolder()),
    );
  }
}
