import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class color_fade extends StatefulWidget {
  const color_fade({Key? key}) : super(key: key);

  @override
  _color_fade_state createState() => _color_fade_state();
}

class _color_fade_state extends State<color_fade> {
  final GlobalKey<FormState> formKey = GlobalKey();
  String shift = "";
  String lower_limit = "";
  String upper_limit = "";
  bool isChecked = false;
  double _currentSliderValue = 50;

  void save() {
    int int_shift = 0;
    int int_lower_limit = 0;
    int int_upper_limit = 255;
    double delay = _currentSliderValue;
    // build method in root class

    if (shift.length > 0) {
      int_shift = int.parse(shift);
    }
    if (lower_limit.length > 0) {
      int_lower_limit = int.parse(lower_limit);
    }
    if (upper_limit.length > 0) {
      int_upper_limit = int.parse(upper_limit);
    }
    print(int_shift);
    print(int_lower_limit);
    print(int_upper_limit);
    print(delay);
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
              children: [
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
                            labelText: "Shift", helperText: "0-255"),
                        onChanged: (String txt) => shift = txt,
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
                            labelText: "Lower Limit", helperText: "0-255"),
                        onChanged: (String txt) => lower_limit = txt,
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
                            labelText: "Upper Limit", helperText: "0-255"),
                        onChanged: (String txt) => upper_limit = txt,
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
                      padding: EdgeInsets.all(8.0),
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
