import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class half_one_color extends StatefulWidget {
  const half_one_color({Key? key}) : super(key: key);

  @override
  _half_one_color_state createState() => _half_one_color_state();
}

class _half_one_color_state extends State<half_one_color> {
  final GlobalKey<FormState> formKey = GlobalKey();
  String hue_one = "";
  String hue_two = "";
  String sat_one = "";
  String sat_two = "";
  String val_one = "";
  String val_two = "";
  bool isChecked = false;
  String drop_down_value_one = "Red";
  String drop_down_value_two = "Blue";

  void save() {
    int int_hue_one = 0;
    int int_sat_one = 0;
    int int_val_one = 0;
    int int_hue_two = 0;
    int int_sat_two = 0;
    int int_val_two = 0;
    // build method in root class
    if (!isChecked) {
      if (hue_one.length > 0) {
        int_hue_one = int.parse(hue_one);
      }
      if (sat_one.length > 0) {
        int_sat_one = int.parse(sat_one);
      }
      if (val_one.length > 0) {
        int_val_one = int.parse(val_one);
      }
      if (hue_two.length > 0) {
        int_hue_two = int.parse(hue_two);
      }
      if (sat_two.length > 0) {
        int_sat_two = int.parse(sat_two);
      }
      if (val_two.length > 0) {
        int_val_two = int.parse(val_two);
      }
    } else {
      print(drop_down_value_one);
      print(drop_down_value_two);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      child: Form(
        key: formKey,
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            Row(
              children: <Widget>[
                Expanded(
                  flex: 1,
                  child: SizedBox(
                    child: Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: TextFormField(
                        keyboardType: TextInputType.number,
                        inputFormatters: <TextInputFormatter>[
                          FilteringTextInputFormatter.digitsOnly,
                          LengthLimitingTextInputFormatter(3),
                        ],
                        decoration: const InputDecoration(
                            labelText: "Hue 1", helperText: "0-255"),
                        onChanged: (String txt) => hue_one = txt,
                        onFieldSubmitted: (String txt) => save(),
                      ),
                    ),
                  ),
                ),
                Expanded(
                  flex: 1,
                  child: SizedBox(
                    child: Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: TextFormField(
                        keyboardType: TextInputType.number,
                        inputFormatters: <TextInputFormatter>[
                          FilteringTextInputFormatter.digitsOnly,
                          LengthLimitingTextInputFormatter(3),
                        ],
                        decoration: const InputDecoration(
                            labelText: "Sat 1", helperText: "0-255"),
                        onChanged: (String txt) => sat_one = txt,
                        onFieldSubmitted: (String txt) => save(),
                      ),
                    ),
                  ),
                ),
                Expanded(
                  flex: 1,
                  child: SizedBox(
                    child: Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: TextFormField(
                        keyboardType: TextInputType.number,
                        inputFormatters: <TextInputFormatter>[
                          FilteringTextInputFormatter.digitsOnly,
                          LengthLimitingTextInputFormatter(3),
                        ],
                        decoration: const InputDecoration(
                            labelText: "Val 1", helperText: "0-255"),
                        onChanged: (String txt) => val_one = txt,
                        onFieldSubmitted: (String txt) => save(),
                      ),
                    ),
                  ),
                ),
              ],
            ),
            Row(
              children: <Widget>[
                Expanded(
                  flex: 1,
                  child: SizedBox(
                    child: Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: TextFormField(
                        keyboardType: TextInputType.number,
                        inputFormatters: <TextInputFormatter>[
                          FilteringTextInputFormatter.digitsOnly,
                          LengthLimitingTextInputFormatter(3),
                        ],
                        decoration: const InputDecoration(
                            labelText: "Hue 2", helperText: "0-255"),
                        onChanged: (String txt) => hue_two = txt,
                        onFieldSubmitted: (String txt) => save(),
                      ),
                    ),
                  ),
                ),
                Expanded(
                  flex: 1,
                  child: SizedBox(
                    child: Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: TextFormField(
                        keyboardType: TextInputType.number,
                        inputFormatters: <TextInputFormatter>[
                          FilteringTextInputFormatter.digitsOnly,
                          LengthLimitingTextInputFormatter(3),
                        ],
                        decoration: const InputDecoration(
                            labelText: "Sat 2", helperText: "0-255"),
                        onChanged: (String txt) => sat_two = txt,
                        onFieldSubmitted: (String txt) => save(),
                      ),
                    ),
                  ),
                ),
                Expanded(
                  flex: 1,
                  child: SizedBox(
                    child: Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: TextFormField(
                        keyboardType: TextInputType.number,
                        inputFormatters: <TextInputFormatter>[
                          FilteringTextInputFormatter.digitsOnly,
                          LengthLimitingTextInputFormatter(3),
                        ],
                        decoration: const InputDecoration(
                            labelText: "Val 2", helperText: "0-255"),
                        onChanged: (String txt) => val_two = txt,
                        onFieldSubmitted: (String txt) => save(),
                      ),
                    ),
                  ),
                ),
              ],
            ),
            Row(
              mainAxisSize: MainAxisSize.min,
              children: <Widget>[
                Expanded(
                  flex: 1,
                  child: SwitchListTile(
                    title: const Text("Predefined Colors"),
                    secondary: const Icon(Icons.color_lens),
                    activeColor: Colors.deepOrange,
                    value: isChecked,
                    onChanged: (bool? value) {
                      setState(() {
                        isChecked = value!;
                      });
                    },
                  ),
                ),
              ],
            ),
            Row(
              children: [
                Expanded(
                  flex: 1,
                  child: Padding(
                    padding: EdgeInsets.all(8.0),
                    child: const Text(
                      "First Color:",
                      style: const TextStyle(
                        fontSize: 16,
                      ),
                      textAlign: TextAlign.center,
                    ),
                  ),
                ),
                Expanded(
                  flex: 3,
                  child: Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: DropdownButton<String>(
                      value: drop_down_value_one,
                      icon: const Icon(
                        Icons.arrow_drop_down,
                        color: Colors.deepOrange,
                      ),
                      style: const TextStyle(color: Colors.white, fontSize: 16),
                      underline: Container(
                        height: 1,
                        color: Colors.deepOrangeAccent,
                      ),
                      onChanged: (String? newValue) {
                        setState(
                          () {
                            drop_down_value_one = newValue!;
                          },
                        );
                      },
                      items: <String>['Red', 'Green', 'Blue', 'White']
                          .map<DropdownMenuItem<String>>(
                        (String value) {
                          return DropdownMenuItem<String>(
                            value: value,
                            child: Text(value),
                          );
                        },
                      ).toList(),
                    ),
                  ),
                ),
              ],
            ),
            Row(
              children: [
                Expanded(
                  flex: 1,
                  child: Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: const Text(
                      "Seccond Color:",
                      style: TextStyle(
                        fontSize: 16,
                      ),
                      textAlign: TextAlign.center,
                    ),
                  ),
                ),
                Expanded(
                  flex: 3,
                  child: Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: DropdownButton<String>(
                      value: drop_down_value_two,
                      icon: const Icon(
                        Icons.arrow_drop_down,
                        color: Colors.deepOrange,
                      ),
                      style: const TextStyle(color: Colors.white, fontSize: 16),
                      underline: Container(
                        height: 1,
                        color: Colors.deepOrangeAccent,
                      ),
                      onChanged: (String? newValue) {
                        setState(
                          () {
                            drop_down_value_two = newValue!;
                          },
                        );
                      },
                      items: <String>['Red', 'Green', 'Blue', 'White']
                          .map<DropdownMenuItem<String>>(
                        (String value) {
                          return DropdownMenuItem<String>(
                            value: value,
                            child: Text(value),
                          );
                        },
                      ).toList(),
                    ),
                  ),
                ),
              ],
            ),
            Padding(
              padding: const EdgeInsets.only(bottom: 16.0, top: 8.0),
              child: ElevatedButton(
                onPressed: save,
                child: Icon(Icons.send),
              ),
            )
          ],
        ),
      ),
      padding: const EdgeInsets.all(8.0),
    );
  }
}
