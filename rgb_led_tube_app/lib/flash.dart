import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class flash extends StatefulWidget {
  const flash({Key? key}) : super(key: key);

  @override
  _flash_state createState() => _flash_state();
}

class _flash_state extends State<flash> {
  final GlobalKey<FormState> formKey = GlobalKey();
  String hue = "";
  String sat = "";
  String val = "";
  String shift = "";
  bool isChecked = false;
  double _currentSliderValue = 50;
  String dropdownValue = "Red";

  void save() {
    int int_hue = 0;
    int int_sat = 0;
    int int_val = 0;
    double delay = _currentSliderValue;
    // build method in root class
    if (!isChecked) {
      if (hue.length > 0) {
        int_hue = int.parse(hue);
      }
      if (sat.length > 0) {
        int_sat = int.parse(sat);
      }
      if (val.length > 0) {
        int_val = int.parse(val);
      }
      print(int_hue);
      print(int_sat);
      print(int_val);
      print(delay);
    } else {
      print(dropdownValue);
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
                            labelText: "Hue", helperText: "0-255"),
                        onChanged: (String txt) => hue = txt,
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
                            labelText: "Sat", helperText: "0-255"),
                        onChanged: (String txt) => sat = txt,
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
                            labelText: "Val", helperText: "0-255"),
                        onChanged: (String txt) => val = txt,
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
                    child: Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: const Text(
                        "Delay:",
                        style: const TextStyle(
                          fontSize: 16,
                          color: Colors.white60,
                        ),
                        textAlign: TextAlign.center,
                      ),
                    )),
                Expanded(
                  flex: 4,
                  child: Slider(
                    value: _currentSliderValue,
                    min: 1,
                    max: 255,
                    divisions: 255,
                    label: _currentSliderValue.round().toString(),
                    onChanged: (double value) {
                      setState(
                        () {
                          _currentSliderValue = value;
                        },
                      );
                    },
                  ),
                )
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
                Expanded(
                  flex: 1,
                  child: Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: DropdownButton<String>(
                      value: dropdownValue,
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
                            dropdownValue = newValue!;
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
