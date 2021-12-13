import 'package:flutter/material.dart';

class option_panel extends StatefulWidget {
  const option_panel({Key? key}) : super(key: key);

  @override
  _option_panel_state createState() => _option_panel_state();
}

class _option_panel_state extends State<option_panel> {
  final GlobalKey<FormState> formKey = GlobalKey();
  String rx_deveices = "0";

  void save() {}

  @override
  Widget build(BuildContext context) {
    return Card(
      elevation: 12.0,
      child: Column(
        mainAxisSize: MainAxisSize.min,
        children: <Widget>[
          Padding(
            padding: EdgeInsets.only(
              top: 16.0,
              left: 8.0,
              right: 8.0,
              bottom: 8.0,
            ),
            child: Text(
              "SETTINGS",
              style: const TextStyle(
                fontSize: 20,
                letterSpacing: 4.0,
                wordSpacing: 4.0,
              ),
            ),
          ),
          Padding(
            padding: EdgeInsets.only(
              left: 8.0,
              right: 8.0,
            ),
            child: Divider(
              color: Colors.white,
              thickness: 1.0,
            ),
          ),
          Row(
            children: <Widget>[
              Padding(
                padding: EdgeInsets.only(
                  left: 8.0,
                  right: 8.0,
                  top: 16.0,
                ),
                child: Text(
                  "NUMBER RX-DEVEICES",
                  style: const TextStyle(
                    fontSize: 15,
                    letterSpacing: 4.0,
                    wordSpacing: 4.0,
                  ),
                ),
              ),
            ],
          ),
          Row(
            children: <Widget>[
              SizedBox(
                width: 180,
                child: Padding(
                  padding: const EdgeInsets.all(8.0),
                  child: TextFormField(
                    keyboardType: TextInputType.number,
                    decoration: const InputDecoration(
                      helperText: "0-32",
                    ),
                    onChanged: (String txt) => rx_deveices = txt,
                    onFieldSubmitted: (String txt) => save(),
                  ),
                ),
              ),
              Padding(
                padding: const EdgeInsets.all(8.0),
                child: ElevatedButton(
                  onPressed: save,
                  child: const Icon(Icons.save_sharp),
                ),
              ),
            ],
          )
        ],
      ),
    );
  }
}
