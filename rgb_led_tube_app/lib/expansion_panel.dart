/// Flutter code sample for ExpansionPanelList

// Here is a simple example of how to implement ExpansionPanelList.

import 'package:flutter/material.dart';
import 'package:rgb_led_tube_app/all_one_color.dart';
import 'package:rgb_led_tube_app/breathe.dart';

class Item {
  Item({
    required this.id,
    required this.expandedValue,
    required this.headerValue,
  });

  int id;
  Widget expandedValue;
  String headerValue;
}

/// This is the stateful widget that the main application instantiates.
class ExpansionPanelHolder extends StatefulWidget {
  const ExpansionPanelHolder({Key? key}) : super(key: key);

  @override
  State<ExpansionPanelHolder> createState() => _ExpansionPanelHolderState();
}

/// This is the private State class that goes with ExpansionPanelHolder.
class _ExpansionPanelHolderState extends State<ExpansionPanelHolder> {
  final List<Item> _data = [
    Item(id: 0, expandedValue: all_one_color(), headerValue: "ALL ONE COLOR"),
    Item(id: 1, expandedValue: breathe(), headerValue: "BREATHE"),
  ];

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      child: Container(
        child: _buildPanel(),
      ),
    );
  }

  Widget _buildPanel() {
    return ExpansionPanelList.radio(
      animationDuration: Duration(milliseconds: 400),
      initialOpenPanelValue: 1,
      children: _data.map<ExpansionPanelRadio>((Item item) {
        return ExpansionPanelRadio(
            canTapOnHeader: true,
            value: item.id,
            headerBuilder: (BuildContext context, bool isExpanded) {
              return ListTile(
                title: Text(
                  item.headerValue,
                  style: TextStyle(
                    fontSize: 20,
                    letterSpacing: 4.0,
                    wordSpacing: 4.0,
                  ),
                ),
              );
            },
            body: item.expandedValue);
      }).toList(),
    );
  }
}
